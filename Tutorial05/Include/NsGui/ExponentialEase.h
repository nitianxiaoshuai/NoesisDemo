////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_EXPONENTIALEASE_H__
#define __GUI_EXPONENTIALEASE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/EasingFunctionBase.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an easing function that creates an animation that accelerates and/or decelerates 
/// using an exponential formula.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.exponentialease.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API ExponentialEase: public EasingFunctionBase
{
public:
    ExponentialEase();
    
    /// Gets or sets the exponent used to determine the interpolation of the animation.
    //@{
    NsFloat32 GetExponent() const;
    void SetExponent(NsFloat32 exponent);
    //@}
    
public:
    static const DependencyProperty* ExponentProperty;

protected:
    /// From EasingFunctionBase
    //@{
    NsFloat32 EaseInCore(NsFloat32 normalizedTime);
    //@}
    
    NS_DECLARE_REFLECTION(ExponentialEase, EasingFunctionBase)
};

}
}

#endif
