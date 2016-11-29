////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_QUINTICEASE_H__
#define __GUI_QUINTICEASE_H__


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
/// decelerates using the formula f(t) = t5.
/// 
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.quinticease.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API QuinticEase: public EasingFunctionBase
{
public:
    QuinticEase();

protected:
    /// From EasingFunctionBase
    //@{
    NsFloat32 EaseInCore(NsFloat32 normalizedTime);
    //@}
    
    NS_DECLARE_REFLECTION(QuinticEase, EasingFunctionBase)
};

}
}

#endif
