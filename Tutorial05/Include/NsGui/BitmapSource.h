////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BITMAPSOURCE_H__
#define __GUI_BITMAPSOURCE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ImageSource.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a single, constant set of pixels at a certain size and resolution. This is an
/// abstract class.
///
/// https://msdn.microsoft.com/en-us/library/system.windows.media.imaging.bitmapsource.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BitmapSource: public ImageSource
{
public:
    BitmapSource();
    virtual ~BitmapSource() = 0;

    /// Creates a new BitmapSource from an array of pixels that are stored in memory
    /// \remarks Only BGRA32 pixels buffer are supported right now
    static Ptr<BitmapSource> Create(NsInt32 pixelWidth, NsInt32 pixelHeight, NsFloat32 dpiX,
        NsFloat32 dpiY, const NsByte* buffer, NsInt32 bufferSize, NsInt32 stride);

    /// Horizontal DPI of the bitmap
    /// \prop
    NsFloat32 GetDpiX() const;

    /// Vertical DPI of the bitmap
    /// \prop
    NsFloat32 GetDpiY() const;

    /// Width, in pixels, of the bitmap
    /// \prop
    NsInt32 GetPixelWidth() const;

    /// Height, in pixels, of the bitmap
    /// \prop
    NsInt32 GetPixelHeight() const;

protected:
    /// From ImageSource
    //@{
    NsFloat32 GetWidthCore() const;
    NsFloat32 GetHeightCore() const;
    //@}

    /// Implemented by inheritors
    //@{
    virtual NsFloat32 GetDpiXCore() const = 0;
    virtual NsFloat32 GetDpiYCore() const = 0;

    virtual NsInt32 GetPixelWidthCore() const = 0;
    virtual NsInt32 GetPixelHeightCore() const = 0;
    //@}

    NS_DECLARE_REFLECTION(BitmapSource, ImageSource)
};

}
}


#endif
