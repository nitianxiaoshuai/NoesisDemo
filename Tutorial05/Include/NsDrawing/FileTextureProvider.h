////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_FILETEXTUREPROVIDER_H__
#define __DRAWING_FILETEXTUREPROVIDER_H__


#include <Noesis.h>
#include <NsDrawing/TextureProvider.h>
#include <NsDrawing/TextureProviderApi.h>


NS_CFORWARD(Core, Stream)


namespace Noesis
{
namespace Drawing
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275 4251)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for texture providers. Inheritors must implement OpenStream() funtion.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_DRAWING_TEXTUREPROVIDER_API FileTextureProvider: public TextureProvider
{
public:
    FileTextureProvider();

protected:
    virtual Ptr<Core::Stream> OpenStream(const NsChar* filename) const = 0;

private:
    /// From TextureProvider
    //@{
    TextureInfo GetTextureInfo(const NsChar* filename);
    Ptr<Render::Texture> LoadTexture(const NsChar* filename, Render::RenderDevice* device);
    //@}

private:
    NsByte mGammaTable[256];
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
