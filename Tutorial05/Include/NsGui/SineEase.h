////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SINEEASE_H__
#define __GUI_SINEEASE_H__


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
/// decelerates using a sine formula
///
/// file:///W:/NoesisGUI-0.9.7.3917/NoesisGUI/Doc/Gui.Animation._SineEase.html
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API SineEase: public EasingFunctionBase
{
public:
    SineEase();

protected:
    /// From EasingFunctionBase
    //@{
    NsFloat32 EaseInCore(NsFloat32 normalizedTime);
    //@}
    
    NS_DECLARE_REFLECTION(SineEase, EasingFunctionBase)
};

}
}

#endif
