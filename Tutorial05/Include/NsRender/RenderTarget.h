////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RENDER_RENDERTARGET_H__
#define __RENDER_RENDERTARGET_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsRender/RenderDeviceApi.h>


NS_CFORWARD(Render, Texture)


namespace Noesis
{
namespace Render
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// 2D texture that can be used as render target
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_RENDER_RENDERDEVICE_API RenderTarget: public Core::BaseComponent
{
public:
    /// Returns the resolve texture
    virtual Texture* GetTexture() = 0;

    NS_DECLARE_REFLECTION(RenderTarget, BaseComponent)
};

}
}


#endif
