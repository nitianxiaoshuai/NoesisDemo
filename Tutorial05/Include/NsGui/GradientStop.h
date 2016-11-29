////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRADIENTSTOP_H__
#define __GUI_GRADIENTSTOP_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsDrawing/Color.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes the location and color of a transition point in a gradient. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.gradientstop.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API GradientStop: public Animatable
{
public:
    /// Constructor
    GradientStop();

    /// Gets or sets the color of the gradient stop
    //@{
    const Drawing::Color& GetColor() const;
    void SetColor(const Drawing::Color& color);
    //@}

    /// Gets or sets the location of the gradient stop within the gradient vector
    //@{
    NsFloat32 GetOffset() const;
    void SetOffset(NsFloat32 offset);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ColorProperty;
    static const DependencyProperty* OffsetProperty;
    //@}

    NS_DECLARE_REFLECTION(GradientStop, Animatable)
};

}
}

#endif
