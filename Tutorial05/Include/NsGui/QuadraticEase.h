////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_QUADRATICEASE_H__
#define __GUI_QUADRATICEASE_H__


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
/// decelerates using the formula f(t) = t2
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.quadraticease.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API QuadraticEase: public EasingFunctionBase
{
public:
    QuadraticEase();
    
protected:
    /// From EasingFunctionBase
    //@{
    NsFloat32 EaseInCore(NsFloat32 normalizedTime);
    //@}
    
    NS_DECLARE_REFLECTION(QuadraticEase, EasingFunctionBase)
};

}
}

#endif
