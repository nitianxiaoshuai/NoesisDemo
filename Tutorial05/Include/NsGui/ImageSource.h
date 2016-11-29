////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IMAGESOURCE_H__
#define __GUI_IMAGESOURCE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an image object that has width and height. This is an abstract class.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.imagesource.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ImageSource: public Animatable
{
public:
    /// Constructor
    ImageSource();

    /// Destructor
    virtual ~ImageSource() = 0;

    /// Gets the width of the image in measure units (96ths of an inch)
    /// \prop
    NsFloat32 GetWidth() const;

    /// Gets the height of the image in measure units (96ths of an inch)
    /// \prop
    NsFloat32 GetHeight() const;

protected:
    static NsFloat32 PixelToDeviceIndependentUnits(NsSize pixels, NsFloat32 dpi);

    /// Implemented by inheritors
    //@{
    virtual NsFloat32 GetWidthCore() const = 0;
    virtual NsFloat32 GetHeightCore() const = 0;
    //@}

    NS_DECLARE_REFLECTION(ImageSource, Animatable)
};

}
}


#endif
