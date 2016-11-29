////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "D3D11RenderDevice.h"

#include <NsRender/RenderTarget.h>
#include <NsRender/Texture.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/Ptr.h>
#include <NsCore/UTF8.h>
#include <NsCore/Algorithm.h>

#define SHADER_IMPLEMENTATION
#include "ShadersD3D11.h"

using namespace Noesis;
using namespace Noesis::Core;
using namespace Noesis::Render;


#ifndef DYNAMIC_VB_SIZE
    #define DYNAMIC_VB_SIZE 512 * 1024
#endif

#ifndef DYNAMIC_IB_SIZE
    #define DYNAMIC_IB_SIZE 128 * 1024
#endif

#ifndef USE_FLOAT16
    #define USE_FLOAT16 1
#endif

#define DX_RELEASE(o) \
    if (o != 0) \
    { \
        o->Release(); \
    }

#define DX_DESTROY(o) \
    if (o != 0) \
    { \
        ULONG refs = o->Release(); \
        NS_ASSERT(refs == 0); \
    }

#if NS_INSTRUMENTED_ENABLED
    #define DX_BEGIN_EVENT(n) if (mGroupMarker != 0) { mGroupMarker->BeginEvent(n); }
    #define DX_END_EVENT() if (mGroupMarker != 0) { mGroupMarker->EndEvent(); }
#else
    #define DX_BEGIN_EVENT(n) NS_NOOP
    #define DX_END_EVENT() NS_NOOP
#endif

#define V(exp) \
    NS_MACRO_BLOCK_BEGIN \
        HRESULT hr_ = (exp); \
        if (FAILED(hr_)) \
        { \
            NS_ERROR("%s[0x%08x]", #exp, hr_); \
        } \
    NS_MACRO_BLOCK_END

#ifdef NS_DEBUG_CFG
    #define VD(exp) V(exp)
#else
    #define VD(exp) exp
#endif

#define NS_LOG_RENDER(...) NS_LOG(LogSeverity_Info, "Render", __VA_ARGS__)

namespace
{

#include "QuadVS.h"
#include "Resolve2PS.h"
#include "Resolve4PS.h"
#include "Resolve8PS.h"
#include "Resolve16PS.h"
#include "ClearPS.h"

struct ConstantBuffer
{
    float rgba[4];
    float radialGrad[8];
    float projectionMtx[16];
    float opacity;
};

#if NS_INSTRUMENTED_ENABLED
const GUID WKPDID_D3DDebugObjectName =
{
    0x429b8c22, 0x9188, 0x4b0c, { 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00 }
};

void SetDebugObjectName(ID3D11DeviceChild* resource, _Printf_format_string_ const NsChar* str, ...)
{
    NsChar name[128];

    va_list args;
    va_start(args, str);
    String::FormatBufferVA(name, sizeof(name), str, args);
    va_end(args);

    resource->SetPrivateData(WKPDID_D3DDebugObjectName, String::Length(name), name);
}

#define DX_NAME(resource, ...) SetDebugObjectName(resource, __VA_ARGS__)

#else
#define DX_NAME(resource, ...) NS_NOOP
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
class D3D11Texture: public Texture
{
public:
    D3D11Texture(ID3D11Texture2D* texture_, ID3D11ShaderResourceView* view_, NsSize width_,
        NsSize height_, NsSize levels_, TextureFormat::Enum format_): texture(texture_),
        view(view_), width(width_), height(height_), levels(levels_), format(format_),
        isInverted(false) {}

    D3D11Texture(ID3D11ShaderResourceView* view_, NsSize width_, NsSize height_, NsSize levels_,
        TextureFormat::Enum format_, NsBool isInverted_) : texture(0), view(view_), width(width_),
        height(height_), levels(levels_), format(format_), isInverted(isInverted_) {}

    ~D3D11Texture()
    {
        // We don't have ownership of textures created by WrapTexture()
        if (texture!= 0)
        {
            DX_DESTROY(view);
            DX_DESTROY(texture);
        }
    }

    NsSize GetWidth() const { return width; }
    NsSize GetHeight() const { return height; }
    TextureFormat::Enum GetFormat() const { return format; };
    NsBool HasMipMaps() const { return levels > 0; }
    NsBool IsInverted() const { return isInverted; }

    const NsSize width;
    const NsSize height;
    const NsSize levels;
    const TextureFormat::Enum format;
    const NsBool isInverted;

    ID3D11Texture2D* texture;
    ID3D11ShaderResourceView* view;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class D3D11RenderTarget: public RenderTarget
{
public:
    D3D11RenderTarget(NsSize width_, NsSize height_, MSAA::Enum msaa_): width(width_),
        height(height_), msaa(msaa_), textureRTV(0), color(0), colorRTV(0), colorSRV(0),
        stencil(0), stencilDSV(0) {}

    ~D3D11RenderTarget()
    {
        DX_DESTROY(textureRTV);

        DX_RELEASE(color);
        DX_DESTROY(colorRTV);
        DX_DESTROY(colorSRV);

        DX_RELEASE(stencil);
        DX_DESTROY(stencilDSV);

        texture.Reset();
    }

    Texture* GetTexture() { return texture.GetPtr(); }

    const NsSize width;
    const NsSize height;
    const MSAA::Enum msaa;

    Ptr<D3D11Texture> texture;
    ID3D11RenderTargetView* textureRTV;

    ID3D11Texture2D* color;
    ID3D11RenderTargetView* colorRTV;
    ID3D11ShaderResourceView* colorSRV;

    ID3D11Texture2D* stencil;
    ID3D11DepthStencilView* stencilDSV;
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
D3D11RenderDevice::D3D11RenderDevice(ID3D11DeviceContext* context, NsBool sRGB): mContext(context),
    mBoundRenderTarget(0)
{
    mContext->GetDevice(&mDevice);
    mContext->QueryInterface(__uuidof(ID3DUserDefinedAnnotation), (void**)&mGroupMarker);

    DumpInfo();
    FillCaps(sRGB);

    CreateBuffers();
    CreateInputLayouts();
    CreateStateObjects();
    CreateShaders();

    InvalidateStateCache();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
D3D11RenderDevice::~D3D11RenderDevice()
{
    for (NsSize i = 0; i < NS_COUNTOF(mRasterizerStates); i++)
    {
        DX_RELEASE(mRasterizerStates[i]);
    }

    for (NsSize i = 0; i < NS_COUNTOF(mBlendStates); i++)
    {
        DX_RELEASE(mBlendStates[i]);
    }

    for (NsSize i = 0; i < NS_COUNTOF(mDepthStencilStates); i++)
    {
        DX_RELEASE(mDepthStencilStates[i]);
    }

    for (NsSize i = 0; i < NS_COUNTOF(mSamplerStates); i++)
    {
        DX_RELEASE(mSamplerStates[i]);
    }

    for (NsSize i = 0; i < NS_COUNTOF(mVertexFormats); i++)
    {
        DX_DESTROY(mVertexFormats[i].layout);
    }

    for (NsSize i = 0; i < NS_COUNTOF(mVertexShaders); i++)
    {
        DX_DESTROY(mVertexShaders[i]);
    }

    for (NsSize i = 0; i < NS_COUNTOF(mPixelShaders); i++)
    {
        DX_DESTROY(mPixelShaders[i]);
    }

    for (NsSize i = 0; i < NS_COUNTOF(mResolvePS); i++)
    {
        DX_DESTROY(mResolvePS[i]);
    }

    DX_DESTROY(mQuadVS);
    DX_DESTROY(mClearPS);

    DX_DESTROY(mVertices.buffer);
    DX_DESTROY(mIndices.buffer);
    DX_DESTROY(mConstants);

    DX_RELEASE(mGroupMarker);
    DX_RELEASE(mDevice);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Texture> D3D11RenderDevice::WrapTexture(ID3D11ShaderResourceView* view, NsSize width,
    NsSize height, NsSize levels, TextureFormat::Enum format, NsBool isInverted)
{
    return *new D3D11Texture(view, width, height, levels, format, isInverted);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DeviceCaps& D3D11RenderDevice::GetCaps() const
{
    return mCaps;
}

namespace
{

////////////////////////////////////////////////////////////////////////////////////////////////////
MSAA::Enum ToMSAA(NsSize sampleCount)
{
    NsSize samples = nstl::max_alt(1U, nstl::min_alt(sampleCount, 16U));

    MSAA::Enum mssa = MSAA::x1;
    while (samples >>= 1)
    {
        mssa = (MSAA::Enum)((NsSize)mssa + 1);
    }

    return mssa;
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<RenderTarget> D3D11RenderDevice::CreateRenderTarget(const NsChar* label, NsSize width,
    NsSize height, NsSize sampleCount)
{
    MSAA::Enum msaa = ToMSAA(mSampleDescs[(NsSize)ToMSAA(sampleCount)].Count);

    D3D11_TEXTURE2D_DESC desc;
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.SampleDesc = mSampleDescs[(NsSize)msaa];
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    ID3D11Texture2D* colorAA = 0;

    if (msaa != MSAA::x1)
    {
        if (mCaps.linearRendering)
        {
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        }
        else
        {
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        }

        desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

        V(mDevice->CreateTexture2D(&desc, 0, &colorAA));
        DX_NAME(colorAA, "%s", label);
    }

    ID3D11Texture2D* stencil;
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

#ifdef NS_PLATFORM_XBOX_ONE
    desc.Format = DXGI_FORMAT_D16_UNORM_S8_UINT;
#else
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
#endif

    V(mDevice->CreateTexture2D(&desc, 0, &stencil));
    DX_NAME(stencil, "%s_Stencil", label);

    return CreateRenderTarget(label, width, height, msaa, colorAA, stencil);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<RenderTarget> D3D11RenderDevice::CloneRenderTarget(const NsChar* label, RenderTarget* surface_)
{
    D3D11RenderTarget* surface = (D3D11RenderTarget*)surface_;

    ID3D11Texture2D* colorAA = 0;
    if (surface->msaa != MSAA::x1)
    {
        colorAA = surface->color;
        colorAA->AddRef();
    }

    ID3D11Texture2D* stencil = surface->stencil;
    stencil->AddRef();

    NsSize width = surface->width;
    NsSize height = surface->height;
    return CreateRenderTarget(label, width, height, surface->msaa, colorAA, stencil);
}

namespace
{

////////////////////////////////////////////////////////////////////////////////////////////////////
DXGI_FORMAT ToD3D(TextureFormat::Enum format, NsBool linearRendering)
{
    switch (format)
    {
        case TextureFormat::BGRA8:
        {
            return linearRendering ? DXGI_FORMAT_B8G8R8A8_UNORM_SRGB : DXGI_FORMAT_B8G8R8A8_UNORM;
        }
        case TextureFormat::BGRX8:
        {
            return linearRendering ? DXGI_FORMAT_B8G8R8X8_UNORM_SRGB : DXGI_FORMAT_B8G8R8X8_UNORM;
        }
        case TextureFormat::R8:
        {
            return DXGI_FORMAT_R8_UNORM;
        }
        default: NS_ASSERT_UNREACHABLE;
    }
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Texture> D3D11RenderDevice::CreateTexture(const NsChar* label, NsSize width, NsSize height,
    NsSize numLevels, TextureFormat::Enum format)
{
    NS_UNUSED(label);

    // TODO: Improve RenderDevice API to support D3D11_USAGE_IMMUTABLE
    D3D11_TEXTURE2D_DESC desc;
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = numLevels;
    desc.ArraySize = 1;
    desc.Format = ToD3D(format, mCaps.linearRendering);
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    NS_LOG_RENDER("Texture '%s' %d x %d x %d (0x%x)", label, width, height, numLevels, desc.Format);

    ID3D11Texture2D* texture;
    V(mDevice->CreateTexture2D(&desc, 0, &texture));
    DX_NAME(texture, label);

    ID3D11ShaderResourceView* view;
    V(mDevice->CreateShaderResourceView(texture, 0, &view));
    DX_NAME(view, "%s_SRV", label);

    return *new D3D11Texture(texture, view, width, height, numLevels, format);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::UpdateTexture(Texture* texture_, NsSize level, NsSize x, NsSize y,
    NsSize width, NsSize height, const void* data)
{
    NS_ASSERT(level == 0);
    D3D11Texture* texture = (D3D11Texture*)texture_;

    D3D11_BOX box;
    box.left = x; 
    box.top = y;
    box.front = 0;
    box.right = x + width;
    box.bottom = y + height;
    box.back = 1;

    NS_ASSERT(texture->texture != 0);
    UINT pitch = texture->format == TextureFormat::R8 ? width : width * 4;
    mContext->UpdateSubresource(texture->texture, 0, &box, data, pitch, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::BeginRender(NsBool offscreen)
{
    NS_UNUSED(offscreen);
    DX_BEGIN_EVENT(offscreen ? L"Noesis.Offscreen": L"Noesis");
    InvalidateStateCache();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetRenderTarget(RenderTarget* surface_)
{
    DX_BEGIN_EVENT(L"SetRenderTarget");

    ClearTextures();
    D3D11RenderTarget* surface = (D3D11RenderTarget*)surface_;
    mContext->OMSetRenderTargets(1, &surface->colorRTV, surface->stencilDSV);

    D3D11_VIEWPORT viewport;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    viewport.Width = (FLOAT)surface->width;
    viewport.Height = (FLOAT)surface->height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    mContext->RSSetViewports(1, &viewport);

    mBoundRenderTarget = surface_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::BeginTile(const Tile& tile)
{
    DX_BEGIN_EVENT(L"Tile");

    UINT numViewports = 1;
    D3D11_VIEWPORT viewport;
    mContext->RSGetViewports(&numViewports, &viewport);

    NsUInt32 x = (NsUInt32)viewport.TopLeftX + tile.x;
    NsUInt32 y = (NsUInt32)viewport.TopLeftY + (NsUInt32)viewport.Height - (tile.y + tile.height);

    D3D11_RECT rect;
    rect.left = x;
    rect.top = y;
    rect.right = x + tile.width;
    rect.bottom = y + tile.height;
    mContext->RSSetScissorRects(1, &rect);

    ClearRenderTarget();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::EndTile()
{
    DX_END_EVENT();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::ResolveRenderTarget(RenderTarget* surface_, const Tile* tiles, NsSize size)
{
    D3D11RenderTarget* surface = (D3D11RenderTarget*)surface_;

    if (surface->msaa != MSAA::x1)
    {
        DX_BEGIN_EVENT(L"Resolve");

        SetInputLayout(0);
        SetVertexShader(mQuadVS);
        NS_ASSERT(surface->msaa - 1 < NS_COUNTOF(mResolvePS));
        SetPixelShader(mResolvePS[surface->msaa - 1]);

        SetRasterizerState(mRasterizerStates[2]);
        SetBlendState(mBlendStates[2]);
        SetDepthStencilState(mDepthStencilStates[0], 0);

        ClearTextures();
        mContext->OMSetRenderTargets(1, &surface->textureRTV, 0);
        SetTexture(0, surface->colorSRV);

        for (NsSize i = 0; i < size; i++)
        {
            const Tile& tile = tiles[i];

            D3D11_RECT rect;
            rect.left = tile.x;
            rect.top = surface->height - (tile.y + tile.height);
            rect.right = tile.x + tile.width;
            rect.bottom = surface->height - tile.y;
            mContext->RSSetScissorRects(1, &rect);

            mContext->Draw(3, 0);
        }

        DX_END_EVENT();
    }

    DX_END_EVENT();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::EndRender()
{
    DX_END_EVENT();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* D3D11RenderDevice::MapVertices(NsSize bytes)
{
    return MapDynamicBuffer(mVertices, bytes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::UnmapVertices()
{
    UnmapDynamicBuffer(mVertices);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* D3D11RenderDevice::MapIndices(NsSize bytes)
{
    return MapDynamicBuffer(mIndices, bytes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::UnmapIndices()
{
    UnmapDynamicBuffer(mIndices);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::DrawBatch(const Batch& batch)
{
    NS_ASSERT(batch.shader.v < NS_COUNTOF(ProgramDescs));
    NS_ASSERT(ProgramDescs[batch.shader.v].vertexIdx < NS_COUNTOF(mVertexShaders));
    NS_ASSERT(ProgramDescs[batch.shader.v].fragmentIdx < NS_COUNTOF(mPixelShaders));
    NS_ASSERT(ProgramDescs[batch.shader.v].format < NS_COUNTOF(mVertexFormats));

    SetShaders(batch);
    SetLayout(batch);
    SetBuffers(batch);
    SetRenderState(batch);
    SetTextures(batch);

    mContext->DrawIndexed(batch.numIndices, batch.startIndex + mIndices.drawPos / 2, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::CreateDynamicBuffer(DynamicBuffer& buffer, NsSize size, D3D11_BIND_FLAG f)
{
    D3D11_BUFFER_DESC desc;
    desc.ByteWidth = size;
    desc.BindFlags = f;
    desc.MiscFlags = 0;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.StructureByteStride = 0;
    V(mDevice->CreateBuffer(&desc, 0, &buffer.buffer));

    buffer.pos = 0;
    buffer.drawPos = 0;
    buffer.size = size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::CreateBuffers()
{
    CreateDynamicBuffer(mVertices, DYNAMIC_VB_SIZE, D3D11_BIND_VERTEX_BUFFER);
    DX_NAME(mVertices.buffer, "Noesis::Vertices");

    CreateDynamicBuffer(mIndices, DYNAMIC_IB_SIZE, D3D11_BIND_INDEX_BUFFER);
    DX_NAME(mIndices.buffer, "Noesis::Indices");

    D3D11_BUFFER_DESC desc;
    desc.ByteWidth = (sizeof(ConstantBuffer) + 0xF) & ~0xF;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.MiscFlags = 0;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.StructureByteStride = 0;
    V(mDevice->CreateBuffer(&desc, 0, &mConstants));
    DX_NAME(mConstants, "Noesis::Constants");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::CreateInputLayouts()
{
    memset(mVertexFormats, 0, sizeof(mVertexFormats));

    for (NsSize i = 0; i < D3D11::NumPrograms; i++)
    {
        const ProgramDesc& program = ProgramDescs[i];
        NS_ASSERT(program.format < NS_COUNTOF(mVertexFormats));
        VertexFormat& format = mVertexFormats[program.format];

        if (format.layout == 0 && program.vertexIdx != -1)
        {
            D3D11_INPUT_ELEMENT_DESC descs[5];
            memset(descs, 0, sizeof(descs));

            NsSize element = 0;

            descs[element].SemanticIndex = 0;
            descs[element].InputSlot = 0;
            descs[element].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
            descs[element].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            descs[element].InstanceDataStepRate = 0;
            descs[element].SemanticName = "POSITION";
            descs[element].Format = DXGI_FORMAT_R32G32_FLOAT;
            format.stride += 8;
            element++;

            if (program.format & VFColor)
            {
                descs[element].SemanticIndex = 0;
                descs[element].InputSlot = 0;
                descs[element].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
                descs[element].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
                descs[element].InstanceDataStepRate = 0;
                descs[element].SemanticName = "COLOR";
                descs[element].Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                format.stride += 4;
                element++;
            }

            NsBool useHalf = mCaps.halfFloatUV;
            DXGI_FORMAT uvFormat = useHalf? DXGI_FORMAT_R16G16_FLOAT : DXGI_FORMAT_R32G32_FLOAT;
            NsSize uvSize = useHalf? 4 : 8;

            if (program.format & VFTex0)
            {
                descs[element].SemanticIndex = 0;
                descs[element].InputSlot = 0;
                descs[element].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
                descs[element].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
                descs[element].InstanceDataStepRate = 0;
                descs[element].SemanticName = "TEXCOORD";
                descs[element].Format = uvFormat;
                format.stride += uvSize;
                element++;
            }

            if (program.format & VFTex1)
            {
                descs[element].SemanticIndex = 1;
                descs[element].InputSlot = 0;
                descs[element].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
                descs[element].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
                descs[element].InstanceDataStepRate = 0;
                descs[element].SemanticName = "TEXCOORD";
                descs[element].Format = uvFormat;
                format.stride += uvSize;
                element++;
            }

            if (program.format & VFCoverage)
            {
                descs[element].SemanticIndex = 2;
                descs[element].InputSlot = 0;
                descs[element].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
                descs[element].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
                descs[element].InstanceDataStepRate = 0;
                descs[element].SemanticName = "TEXCOORD";
                descs[element].Format = DXGI_FORMAT_R32_FLOAT;
                format.stride += 4;
                element++;
            }

            const Bytecode& shader = D3D11::VertexShaders[program.vertexIdx];
            V(mDevice->CreateInputLayout(descs, element, shader.code, shader.size, &format.layout));
            DX_NAME(format.layout, "Noesis::Pos%s%s%s%s", (program.format & VFColor)? "_Color" : "",
                (program.format & VFTex0)? "_Tex0" : "", (program.format & VFTex1)? "_Tex1" : "",
                (program.format & VFCoverage)? "_Coverage" : "");
        }
    }
}

namespace
{

////////////////////////////////////////////////////////////////////////////////////////////////////
D3D11_FILTER ToD3D(MinFilter::Enum minFilter, MagFilter::Enum magFilter)
{
    // TODO: Nearest and Linear must disable mipmapping by setting MaxLOD to 0

    if (magFilter == MagFilter::Nearest)
    {
        switch (minFilter)
        {
            case MinFilter::Nearest:
            {
                return D3D11_FILTER_MIN_MAG_MIP_POINT; //* 
            }
            case MinFilter::Linear:
            {
                return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT; //*
            }
            case MinFilter::NearestNearest:
            {
                return D3D11_FILTER_MIN_MAG_MIP_POINT;
            }
            case MinFilter::LinearNearest:
            {
                return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
            }
            case MinFilter::NearestLinear:
            {
                return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
            }
            case MinFilter::LinearLinear:
            {
                return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
            }
            default:
            {
                NS_ASSERT_UNREACHABLE;
            }
        }
    }
    else if (magFilter == MagFilter::Linear)
    {
       switch (minFilter)
        {
            case MinFilter::Nearest:
            {
                return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT; // *
            }
            case MinFilter::Linear:
            {
                return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT; // *
            }
            case MinFilter::NearestNearest:
            {
                return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
            }
            case MinFilter::LinearNearest:
            {
                return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
            }
            case MinFilter::NearestLinear:
            {
                return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
            }
            case MinFilter::LinearLinear:
            {
                return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            }
            default:
            {
                NS_ASSERT_UNREACHABLE;
            }
        }
    }

    NS_ASSERT_UNREACHABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
D3D11_TEXTURE_ADDRESS_MODE ToD3D(WrapMode::Enum mode, D3D_FEATURE_LEVEL featureLevel)
{
    switch (mode)
    {
        case WrapMode::Repeat:
        {
            return D3D11_TEXTURE_ADDRESS_WRAP;
        }
        case WrapMode::Mirror:
        {
            return D3D11_TEXTURE_ADDRESS_MIRROR;
        }
        case WrapMode::Clamp:
        {
            return D3D11_TEXTURE_ADDRESS_CLAMP;
        }
        case WrapMode::Border:
        {
            NsBool hasBorder = featureLevel >= D3D_FEATURE_LEVEL_9_3;
            return hasBorder? D3D11_TEXTURE_ADDRESS_BORDER : D3D11_TEXTURE_ADDRESS_CLAMP;
        }
        default:
        {
            NS_ASSERT_UNREACHABLE;
        }
    }
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::CreateStateObjects()
{
    // Rasterized states
    {
        D3D11_RASTERIZER_DESC desc;
        desc.CullMode = D3D11_CULL_NONE;
        desc.FrontCounterClockwise = false;
        desc.DepthBias = 0;
        desc.DepthBiasClamp = 0.0f;
        desc.SlopeScaledDepthBias = 0.0f;
        desc.DepthClipEnable = true;
        desc.MultisampleEnable = true;
        desc.AntialiasedLineEnable = false;

        desc.FillMode = D3D11_FILL_SOLID;
        desc.ScissorEnable = false;
        V(mDevice->CreateRasterizerState(&desc, &mRasterizerStates[0]));

        desc.FillMode = D3D11_FILL_WIREFRAME;
        desc.ScissorEnable = false;
        V(mDevice->CreateRasterizerState(&desc, &mRasterizerStates[1]));

        desc.FillMode = D3D11_FILL_SOLID;
        desc.ScissorEnable = true;
        V(mDevice->CreateRasterizerState(&desc, &mRasterizerStates[2]));

        desc.FillMode = D3D11_FILL_WIREFRAME;
        desc.ScissorEnable = true;
        V(mDevice->CreateRasterizerState(&desc, &mRasterizerStates[3]));
    }

    // Blend states
    {
        D3D11_BLEND_DESC desc;
        desc.AlphaToCoverageEnable = false;
        desc.IndependentBlendEnable = false;
        desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
        desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
        desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

        desc.RenderTarget[0].BlendEnable = false;
        desc.RenderTarget[0].RenderTargetWriteMask = 0;
        V(mDevice->CreateBlendState(&desc, &mBlendStates[0]));

        desc.RenderTarget[0].BlendEnable = true;
        desc.RenderTarget[0].RenderTargetWriteMask = 0;
        V(mDevice->CreateBlendState(&desc, &mBlendStates[1]));

        desc.RenderTarget[0].BlendEnable = false;
        desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        V(mDevice->CreateBlendState(&desc, &mBlendStates[2]));

        desc.RenderTarget[0].BlendEnable = true;
        desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        V(mDevice->CreateBlendState(&desc, &mBlendStates[3]));
    }

    // Depth states
    {
        D3D11_DEPTH_STENCIL_DESC desc;
        desc.DepthEnable = false;
        desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
        desc.DepthFunc = D3D11_COMPARISON_NEVER;
        desc.StencilReadMask = 0xff;
        desc.StencilWriteMask = 0xff;
        desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
        desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        desc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;
        desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

        // Disabled
        desc.StencilEnable = false;
        desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        V(mDevice->CreateDepthStencilState(&desc, &mDepthStencilStates[0]));

        // Equal_Keep
        desc.StencilEnable = true;
        desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        V(mDevice->CreateDepthStencilState(&desc, &mDepthStencilStates[1]));

        // Equal_Incr
        desc.StencilEnable = true;
        desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
        desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
        V(mDevice->CreateDepthStencilState(&desc, &mDepthStencilStates[2]));

        // Equal_Decr
        desc.StencilEnable = true;
        desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_DECR;
        desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_DECR;
        V(mDevice->CreateDepthStencilState(&desc, &mDepthStencilStates[3]));

        // Zero
        desc.StencilEnable = true;
        desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_ZERO;
        desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_ZERO;
        V(mDevice->CreateDepthStencilState(&desc, &mDepthStencilStates[4]));
    }

    // Sampler states
    {
        memset(mSamplerStates, 0, sizeof(mSamplerStates));

        D3D11_SAMPLER_DESC desc;
        desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        desc.MipLODBias = 0.0f;
        desc.MaxAnisotropy = 1;
        desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        desc.BorderColor[0] = 0.0f;
        desc.BorderColor[1] = 0.0f;
        desc.BorderColor[2] = 0.0f;
        desc.BorderColor[3] = 0.0f;
        desc.MinLOD = -D3D11_FLOAT32_MAX;
        desc.MaxLOD = D3D11_FLOAT32_MAX;

        D3D_FEATURE_LEVEL featureLevel = mDevice->GetFeatureLevel();

        for (NsUInt8 mag = MagFilter::Nearest; mag < MagFilter::Count; mag++)
        {
            for (NsUInt8 min = MinFilter::Nearest; min < MinFilter::Count; min++)
            {
                for (NsUInt8 v = WrapMode::Repeat; v < WrapMode::Count; v++)
                {
                    for (NsUInt8 u = WrapMode::Repeat; u < WrapMode::Count; u++)
                    {
                        desc.Filter = ToD3D(MinFilter::Enum(min), MagFilter::Enum(mag));
                        desc.AddressU = ToD3D(WrapMode::Enum(u), featureLevel);
                        desc.AddressV = ToD3D(WrapMode::Enum(v), featureLevel);

                        SamplerState s = {u, v, min, mag};
                        V(mDevice->CreateSamplerState(&desc, &mSamplerStates[s.v]));
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::CreateShaders()
{
    for (NsSize i = 0; i < D3D11::NumVertexShaders; i++)
    {
        const Bytecode& bytecode = D3D11::VertexShaders[i];
        V(mDevice->CreateVertexShader(bytecode.code, bytecode.size, 0, &mVertexShaders[i]));
        DX_NAME(mVertexShaders[i], "Noesis::VS_%d", i);
    }

    for (NsSize i = 0; i < D3D11::NumFragmentShaders; i++)
    {
        const Bytecode& bytecode = D3D11::FragmentShaders[i];
        V(mDevice->CreatePixelShader(bytecode.code, bytecode.size, 0, &mPixelShaders[i]));
        DX_NAME(mPixelShaders[i], "Noesis::PS_#%d", i);
    }

    V(mDevice->CreateVertexShader(Quad_VS, NS_COUNTOF(Quad_VS), 0, &mQuadVS));
    DX_NAME(mQuadVS, "Noesis::Quad_VS");

    V(mDevice->CreatePixelShader(Resolve2_PS, NS_COUNTOF(Resolve2_PS), 0, &mResolvePS[0]));
    DX_NAME(mResolvePS[0], "Noesis::Resolve2_PS");

    V(mDevice->CreatePixelShader(Resolve4_PS, NS_COUNTOF(Resolve4_PS), 0, &mResolvePS[1]));
    DX_NAME(mResolvePS[1], "Noesis::Resolve4_PS");

    V(mDevice->CreatePixelShader(Resolve8_PS, NS_COUNTOF(Resolve8_PS), 0, &mResolvePS[2]));
    DX_NAME(mResolvePS[2], "Noesis::Resolve8_PS");

    V(mDevice->CreatePixelShader(Resolve16_PS, NS_COUNTOF(Resolve16_PS), 0, &mResolvePS[3]));
    DX_NAME(mResolvePS[3], "Noesis::Resolve16_PS");

    V(mDevice->CreatePixelShader(Clear_PS, NS_COUNTOF(Clear_PS), 0, &mClearPS));
    DX_NAME(mClearPS, "Noesis::Clear_PS");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<RenderTarget> D3D11RenderDevice::CreateRenderTarget(const NsChar* label, NsSize width,
    NsSize height, MSAA::Enum msaa, ID3D11Texture2D* colorAA, ID3D11Texture2D* stencil)
{
    NS_UNUSED(label);

    Ptr<D3D11RenderTarget> surface = *new D3D11RenderTarget(width, height, msaa);

    NS_LOG_RENDER("RenderTarget '%s' %d x %d %dx", label, width, height, 1 << msaa);
    NsBool sRGB = mCaps.linearRendering;

    // Texture
    D3D11_TEXTURE2D_DESC desc;
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = sRGB ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    ID3D11Texture2D* colorTex;
    V(mDevice->CreateTexture2D(&desc, 0, &colorTex));
    DX_NAME(colorTex, "%s_TEX", label);

    ID3D11ShaderResourceView* viewTex;
    V(mDevice->CreateShaderResourceView(colorTex, 0, &viewTex));
    DX_NAME(viewTex, "%s_TEX_SRV", label);

    surface->texture = *new D3D11Texture(colorTex, viewTex, width, height, 1, TextureFormat::BGRA8);

    V(mDevice->CreateRenderTargetView(colorTex, 0, &surface->textureRTV));
    DX_NAME(surface->textureRTV, "%s_TEX_RTV", label);

    // Color
    if (colorAA != 0)
    {
        NS_ASSERT(msaa != MSAA::x1);
        surface->color = colorAA;
    }
    else
    {
        NS_ASSERT(msaa == MSAA::x1);
        surface->color = colorTex;
        surface->color->AddRef();
    }

    V(mDevice->CreateRenderTargetView(surface->color, 0, &surface->colorRTV));
    DX_NAME(surface->colorRTV, "%s_RTV", label);

    V(mDevice->CreateShaderResourceView(surface->color, 0, &surface->colorSRV));
    DX_NAME(surface->colorSRV, "%s_SRV", label);

    // Stencil
    surface->stencil = stencil;

    V(mDevice->CreateDepthStencilView(surface->stencil, 0, &surface->stencilDSV));
    DX_NAME(surface->stencilDSV, "%s_DSV", label);

    return surface;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::DumpInfo() const
{
#if NS_LOGGER_ENABLED
    NS_INFO("Feature Level: %d_%d", (mDevice->GetFeatureLevel() >> 12) & 0xf,
        (mDevice->GetFeatureLevel() >> 8) & 0xf);

#ifndef NS_PLATFORM_XBOX_ONE
    IDXGIDevice* dxgiDevice;
    V(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

    IDXGIAdapter* dxgiAdapter;
    V(dxgiDevice->GetAdapter(&dxgiAdapter));

    DXGI_ADAPTER_DESC desc;
    V(dxgiAdapter->GetDesc(&desc));

    NsChar description[128];
    NsSize numChars = UTF8::UTF16To8((NsUInt16*)desc.Description, description, 128);
    NS_ASSERT(numChars <= 128);

    NS_INFO("Adapter: %s", description);

    DX_RELEASE(dxgiAdapter);
    DX_RELEASE(dxgiDevice);
#else
    NS_INFO("Adapter: Xbox One");
#endif

#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::CheckMultisample()
{
    NS_ASSERT(mDevice != 0);

    UINT counts[MSAA::Count] = {1, 2, 4, 8, 16};

    for (NsSize i = 0, last = 0; i < NS_COUNTOF(counts); i++)
    {
        DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
        UINT count = counts[i];
        UINT quality = 0;

        HRESULT hr = mDevice->CheckMultisampleQualityLevels(format, count, &quality);

        if (SUCCEEDED(hr) && quality > 0)
        {
            mSampleDescs[i].Count = count;
            mSampleDescs[i].Quality = 0;
            last = i;
        }
        else
        {
            mSampleDescs[i] = mSampleDescs[last];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::FillCaps(NsBool sRGB)
{
    CheckMultisample();

    memset(&mCaps, 0, sizeof(DeviceCaps));

#if USE_FLOAT16
#ifdef NS_PLATFORM_XBOX_ONE
    mCaps.halfFloatUV = true;
#else
    UINT formatSupport;
    HRESULT hr = mDevice->CheckFormatSupport(DXGI_FORMAT_R16G16_FLOAT, &formatSupport);
    NsBool hasf16_2 = SUCCEEDED(hr) && (formatSupport & D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER) > 0;
    mCaps.halfFloatUV = hasf16_2;
#endif
#else
    mCaps.halfFloatUV = false;
#endif

    mCaps.centerPixelOffset = 0.0f;
    mCaps.dynamicVerticesSize = DYNAMIC_VB_SIZE;
    mCaps.dynamicIndicesSize = DYNAMIC_IB_SIZE;

    mCaps.linearRendering = sRGB;
    mCaps.maxSamples = mSampleDescs[NS_COUNTOF(mSampleDescs) - 1].Count;

    mCaps.supportedTextureFormats[TextureFormat::BGRA8] = true;
    mCaps.supportedTextureFormats[TextureFormat::BGRX8] = true;
    mCaps.supportedTextureFormats[TextureFormat::R8] = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* D3D11RenderDevice::MapDynamicBuffer(DynamicBuffer& buffer, NsSize size) const
{
    NS_ASSERT(size <= buffer.size);

    D3D11_MAP type;

    if (size <= buffer.size - buffer.pos)
    {
        type = D3D11_MAP_WRITE_NO_OVERWRITE;
    }
    else
    {
        type = D3D11_MAP_WRITE_DISCARD;
        buffer.pos = 0;
    }

    buffer.drawPos = buffer.pos;
    buffer.pos += size;

    D3D11_MAPPED_SUBRESOURCE mapped;
    VD(mContext->Map(buffer.buffer, 0, type, 0, &mapped));
    return (NsByte*)mapped.pData + buffer.drawPos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::UnmapDynamicBuffer(DynamicBuffer& buffer) const
{
    mContext->Unmap(buffer.buffer, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::InvalidateStateCache()
{
    mContext->IASetIndexBuffer(mIndices.buffer, DXGI_FORMAT_R16_UINT, 0);
    mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    mContext->VSSetConstantBuffers(0, 1, &mConstants);
    mContext->PSSetConstantBuffers(0, 1, &mConstants);
    mContext->HSSetShader(0, 0, 0);
    mContext->DSSetShader(0, 0, 0);
    mContext->GSSetShader(0, 0, 0);
    mContext->CSSetShader(0, 0, 0);
    mContext->SetPredication(0, 0);

    mLayout = 0;
    mVertexShader = 0;
    mPixelShader = 0;
    mRasterizerState = 0;
    mBlendState = 0;
    mDepthStencilState = 0;
    mStencilRef = 0;
    memset(mTextures, 0, sizeof(mTextures));
    memset(mSamplers, 0, sizeof(mSamplers));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetInputLayout(ID3D11InputLayout* layout)
{
    if (layout != mLayout)
    {
        mContext->IASetInputLayout(layout);
        mLayout = layout;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetVertexShader(ID3D11VertexShader* shader)
{
    if (shader != mVertexShader)
    {
        mContext->VSSetShader(shader, 0, 0);
        mVertexShader = shader;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetPixelShader(ID3D11PixelShader* shader)
{
    if (shader != mPixelShader)
    {
        mContext->PSSetShader(shader, 0, 0);
        mPixelShader = shader;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetRasterizerState(ID3D11RasterizerState* state)
{
    if (state != mRasterizerState)
    {
        mContext->RSSetState(state);
        mRasterizerState = state;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetBlendState(ID3D11BlendState* state)
{
    if (state != mBlendState)
    {
        mContext->OMSetBlendState(state, 0, 0xffffffff);
        mBlendState = state;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetDepthStencilState(ID3D11DepthStencilState* state, UINT stencilRef)
{
    if (state != mDepthStencilState || stencilRef != mStencilRef)
    {
        mContext->OMSetDepthStencilState(state, stencilRef);
        mDepthStencilState = state;
        mStencilRef = stencilRef;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetTexture(UINT slot, ID3D11ShaderResourceView* texture)
{
    NS_ASSERT(slot < NS_COUNTOF(mTextures));
    if (texture != mTextures[slot])
    {
        mContext->PSSetShaderResources(slot, 1, &texture);
        mTextures[slot] = texture;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::ClearRenderTarget()
{
    DX_BEGIN_EVENT(L"Clear");

    SetInputLayout(0);
    SetVertexShader(mQuadVS);
    SetPixelShader(mClearPS);

    SetRasterizerState(mRasterizerStates[2]);
    SetBlendState(mBlendStates[2]);
    SetDepthStencilState(mDepthStencilStates[4], 0);

    mContext->Draw(3, 0);

    DX_END_EVENT();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::ClearTextures()
{
    memset(mTextures, 0, sizeof(mTextures));
    mContext->PSSetShaderResources(0, NS_COUNTOF(mTextures), mTextures);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetSampler(UINT slot, ID3D11SamplerState* sampler)
{
    NS_ASSERT(slot < NS_COUNTOF(mSamplers));
    if (sampler != mSamplers[slot])
    {
        mContext->PSSetSamplers(slot, 1, &sampler);
        mSamplers[slot] = sampler;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetShaders(const Batch& batch)
{
    const ProgramDesc& program = ProgramDescs[batch.shader.v];
    SetVertexShader(mVertexShaders[program.vertexIdx]);
    SetPixelShader(mPixelShaders[program.fragmentIdx]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetLayout(const Batch& batch)
{
    const ProgramDesc& program = ProgramDescs[batch.shader.v];
    SetInputLayout(mVertexFormats[program.format].layout);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetBuffers(const Batch& batch)
{
    // Vertices
    UINT stride = mVertexFormats[ProgramDescs[batch.shader.v].format].stride;
    UINT offset = mVertices.drawPos + batch.vertexOffset;
    mContext->IASetVertexBuffers(0, 1, &mVertices.buffer, &stride, &offset);

    // Constants
    D3D11_MAPPED_SUBRESOURCE mapped;
    mContext->Map(mConstants, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

    ConstantBuffer* b = (ConstantBuffer*)mapped.pData;
    memcpy(b->rgba, batch.rgba, sizeof(b->rgba));
    memcpy(b->radialGrad, batch.radialGrad, sizeof(b->radialGrad));
    memcpy(b->projectionMtx, batch.projMtx, sizeof(b->projectionMtx));
    b->opacity = batch.opacity;

    mContext->Unmap(mConstants, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetRenderState(const Batch& batch)
{
    RenderState renderState = batch.renderState;

    NsSize rasterizerIdx = renderState.f.wireframe | (renderState.f.scissorEnable << 1);
    ID3D11RasterizerState* rasterizer = mRasterizerStates[rasterizerIdx];
    SetRasterizerState(rasterizer);

    NsSize blendIdx = renderState.f.blendMode | (renderState.f.colorEnable << 1);
    ID3D11BlendState* blend = mBlendStates[blendIdx];
    SetBlendState(blend);

    NsSize depthIdx = renderState.f.stencilMode;
    ID3D11DepthStencilState* depth = mDepthStencilStates[depthIdx];
    SetDepthStencilState(depth, batch.stencilRef);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void D3D11RenderDevice::SetTextures(const Batch& batch)
{
    if (batch.pattern != 0)
    {
        D3D11Texture* t = (D3D11Texture*)batch.pattern;
        SetTexture(TextureSlot::Pattern, t->view);
        SetSampler(TextureSlot::Pattern, mSamplerStates[batch.patternSampler.v]);
    }

    if (batch.ramps != 0)
    {
        D3D11Texture* t = (D3D11Texture*)batch.ramps;
        SetTexture(TextureSlot::Ramps, t->view);
        SetSampler(TextureSlot::Ramps, mSamplerStates[batch.rampsSampler.v]);
    }

    if (batch.image != 0)
    {
        D3D11Texture* t = (D3D11Texture*)batch.image;
        SetTexture(TextureSlot::Image, t->view);
        SetSampler(TextureSlot::Image, mSamplerStates[batch.imageSampler.v]);
    }

    if (batch.glyphs != 0)
    {
        D3D11Texture* t = (D3D11Texture*)batch.glyphs;
        SetTexture(TextureSlot::Glyphs, t->view);
        SetSampler(TextureSlot::Glyphs, mSamplerStates[batch.glyphsSampler.v]);
    }
}
