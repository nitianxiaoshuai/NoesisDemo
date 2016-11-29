////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_POWEREASE_H__
#define __GUI_POWEREASE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/EasingFunctionBase.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an easing function that creates an animation that accelerates and/or 
/// decelerates using the formula f(t) = tp where p is equal to the Power property.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.powerease.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API PowerEase: public EasingFunctionBase
{
public:
    PowerEase();
    
    /// Gets or sets the exponential power of the animation interpolation. For example, a value of 7
    /// will create an animation interpolation curve that follows the formula f(t) = t7.
    //@{
    NsFloat32 GetPower() const;
    void SetPower(NsFloat32 power);
    //@}
    
public:
    static const DependencyProperty* PowerProperty;

protected:
    /// From EasingFunctionBase
    //@{
    NsFloat32 EaseInCore(NsFloat32 normalizedTime);
    //@}
    
    NS_DECLARE_REFLECTION(PowerEase, EasingFunctionBase)
};

}
}

#endif
