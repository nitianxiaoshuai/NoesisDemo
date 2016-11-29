////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TEXTURESOURCE_H__
#define __GUI_TEXTURESOURCE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ImageSource.h>
#include <NsGui/IRenderProxyCreator.h>
#include <NsCore/ReflectionDeclare.h>


NS_CFORWARD(Render, Texture)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines an image source constructed from a texture.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TextureSource: public ImageSource, public IRenderProxyCreator
{
public:
    /// Constructor
    TextureSource();
    TextureSource(Render::Texture* texture);

    /// Destructor
    ~TextureSource();

    /// Gets or sets texture
    //@{
    Render::Texture* GetTexture() const;
    void SetTexture(Render::Texture* texture);
    //@}

    /// Gets the width of the texture in pixels
    /// \prop
    NsInt32 GetPixelWidth() const;

    /// Gets the height of the texture in pixels
    /// \prop
    NsInt32 GetPixelHeight() const;

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UnregisterRenderer(ViewId viewId);
    //@}

protected:
    /// From Freezable
    //@{
    void CloneCommonCore(const Freezable* source);
    //@}

    /// From ImageSource
    //@{
    NsFloat32 GetWidthCore() const;
    NsFloat32 GetHeightCore() const;
    //@}

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Texture
    };

    Ptr<Render::Texture> mTexture;

    NS_DECLARE_REFLECTION(TextureSource, ImageSource)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
