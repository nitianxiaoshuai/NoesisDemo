////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RENDER_D3D11RENDERDEVICE_H__
#define __RENDER_D3D11RENDERDEVICE_H__


#include <NsRender/RenderDevice.h>
#include <NsCore/PtrForward.h>

#include "ShadersD3D11.h"

#ifdef NS_PLATFORM_XBOX_ONE
    #include <d3d11_x.h>
#else
    #include <d3d11_1.h>
#endif


namespace Noesis
{
namespace Render
{

struct MSAA
{
    enum Enum
    {
        x1,
        x2,
        x4,
        x8,
        x16,

        Count
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// D3D11RenderDevice
////////////////////////////////////////////////////////////////////////////////////////////////////
class D3D11RenderDevice: public RenderDevice
{
public:
    D3D11RenderDevice(ID3D11DeviceContext* context, NsBool sRGB = false);
    ~D3D11RenderDevice();

    // Creates a Noesis texture from a D3D11 texture
    static Ptr<Texture> WrapTexture(ID3D11ShaderResourceView* view, NsSize width, NsSize height,
        NsSize levels, TextureFormat::Enum format, NsBool isInverted);

private:
    /// From RenderDevice
    //@{
    const DeviceCaps& GetCaps() const;
    Ptr<RenderTarget> CreateRenderTarget(const NsChar* label, NsSize width, NsSize height,
        NsSize sampleCount);
    Ptr<RenderTarget> CloneRenderTarget(const NsChar* label, RenderTarget* surface);
    Ptr<Texture> CreateTexture(const NsChar* label, NsSize width, NsSize height, NsSize numLevels,
        TextureFormat::Enum format);
    void UpdateTexture(Texture* texture, NsSize level, NsSize x, NsSize y, NsSize width,
        NsSize height, const void* data);
    void BeginRender(NsBool offscreen);
    void SetRenderTarget(RenderTarget* surface);
    void BeginTile(const Tile& tile);
    void EndTile();
    void ResolveRenderTarget(RenderTarget* surface, const Tile* tiles, NsSize numTiles);
    void EndRender();
    void* MapVertices(NsSize bytes);
    void UnmapVertices();
    void* MapIndices(NsSize bytes);
    void UnmapIndices();
    void DrawBatch(const Batch& batch);
    //@}

private:
    struct DynamicBuffer;
    void CreateDynamicBuffer(DynamicBuffer& buffer, NsSize size, D3D11_BIND_FLAG f);
    void CreateBuffers();
    void CreateInputLayouts();
    void CreateStateObjects();
    void CreateShaders();
    Ptr<RenderTarget> CreateRenderTarget(const NsChar* label, NsSize width, NsSize height,
        MSAA::Enum msaa, ID3D11Texture2D* colorAA, ID3D11Texture2D* stencil);

    void DumpInfo() const;
    void CheckMultisample();
    void FillCaps(NsBool sRGB);

    void* MapDynamicBuffer(DynamicBuffer& buffer, NsSize size) const;
    void UnmapDynamicBuffer(DynamicBuffer& buffer) const;

    void InvalidateStateCache();

    void SetInputLayout(ID3D11InputLayout* layout);
    void SetVertexShader(ID3D11VertexShader* shader);
    void SetPixelShader(ID3D11PixelShader* shader);
    void SetRasterizerState(ID3D11RasterizerState* state);
    void SetBlendState(ID3D11BlendState* state);
    void SetDepthStencilState(ID3D11DepthStencilState* state, UINT stencilRef);
    void SetSampler(UINT slot, ID3D11SamplerState* sampler);
    void SetTexture(UINT slot, ID3D11ShaderResourceView* texture);
    void ClearRenderTarget();
    void ClearTextures();

    void SetShaders(const Batch& batch);
    void SetLayout(const Batch& batch);
    void SetBuffers(const Batch& batch);
    void SetRenderState(const Batch& batch);
    void SetTextures(const Batch& batch);

private:
    ID3D11Device* mDevice;
    ID3D11DeviceContext* mContext;
    ID3DUserDefinedAnnotation* mGroupMarker;

    DXGI_SAMPLE_DESC mSampleDescs[MSAA::Count];
    DeviceCaps mCaps;

    struct DynamicBuffer
    {
        NsSize size;
        NsSize pos;
        NsSize drawPos;
        ID3D11Buffer* buffer;
    };

    DynamicBuffer mVertices;
    DynamicBuffer mIndices;
    ID3D11Buffer* mConstants;

    ID3D11InputLayout* mResolveLayout;

    struct VertexFormat
    {
        ID3D11InputLayout* layout;
        NsSize stride;
    };

    VertexFormat mVertexFormats[16];

    ID3D11VertexShader* mVertexShaders[D3D11::NumVertexShaders];
    ID3D11PixelShader* mPixelShaders[D3D11::NumFragmentShaders];
    ID3D11VertexShader* mQuadVS;
    ID3D11PixelShader* mClearPS;
    ID3D11PixelShader* mResolvePS[MSAA::Count - 1];

    ID3D11RasterizerState* mRasterizerStates[4];
    ID3D11BlendState* mBlendStates[4];
    ID3D11DepthStencilState* mDepthStencilStates[5];
    ID3D11SamplerState* mSamplerStates[256];

    RenderTarget* mBoundRenderTarget;

    struct TextureSlot
    {
        enum Enum
        {
            Pattern,
            Ramps,
            Image,
            Glyphs,

            Count
        };
    };

    //Cached state
    //@{
    ID3D11InputLayout* mLayout;
    ID3D11VertexShader* mVertexShader;
    ID3D11PixelShader* mPixelShader;
    ID3D11RasterizerState* mRasterizerState;
    ID3D11BlendState* mBlendState;
    ID3D11DepthStencilState* mDepthStencilState;
    UINT mStencilRef;
    ID3D11ShaderResourceView* mTextures[TextureSlot::Count];
    ID3D11SamplerState* mSamplers[TextureSlot::Count];
    //@}
};

}
}

#endif
