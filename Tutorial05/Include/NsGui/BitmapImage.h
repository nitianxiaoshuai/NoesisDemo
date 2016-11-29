////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BITMAPIMAGE_H__
#define __GUI_BITMAPIMAGE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/BitmapSource.h>
#include <NsGui/IRenderProxyCreator.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/String.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a BitmapSource created from an image file located at the specifed URI.
///
/// https://msdn.microsoft.com/en-us/library/system.windows.media.imaging.bitmapimage.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BitmapImage: public BitmapSource, public IRenderProxyCreator
{
public:
    BitmapImage();
    BitmapImage(const NsChar* uriSource);
    ~BitmapImage();

    /// Gets or sets the image URI source
    //@{
    const NsChar* GetUriSource() const;
    void SetUriSource(const NsChar* uriSource);
    //@}

private:
    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UnregisterRenderer(ViewId viewId);
    //@}

    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const;
    void CloneCommonCore(const Freezable* source);
    //@}

    /// From BitmapSource
    //@{
    NsFloat32 GetDpiXCore() const;
    NsFloat32 GetDpiYCore() const;
    NsInt32 GetPixelWidthCore() const;
    NsInt32 GetPixelHeightCore() const;
    //@}

    void EnsureImageInfo() const;
    void ResetImageInfo();

private:
    friend class BitmapImageTest;

    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Source
    };

    NsString mUriSource;
    mutable NsFloat32 mDpiX;
    mutable NsFloat32 mDpiY;
    mutable NsInt32 mPixelWidth;
    mutable NsInt32 mPixelHeight;

    NS_DECLARE_REFLECTION(BitmapImage, BitmapSource)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
