////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BACKEASE_H__
#define __GUI_BACKEASE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/EasingFunctionBase.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an easing function that retracts the motion of an animation slightly 
/// before it begins to animate in the path indicated.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.backease.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API BackEase: public EasingFunctionBase
{
public:
    BackEase();

    /// Gets or sets the amplitude of retraction associated with a BackEase animation.
    //@{
    NsFloat32 GetAmplitude() const;
    void SetAmplitude(NsFloat32 amplitude);
    //@}
    
    
public:
    static const DependencyProperty* AmplitudeProperty;

protected:
    /// From EasingFunctionBase
    //@{
    NsFloat32 EaseInCore(NsFloat32 normalizedTime);
    //@}
    
    NS_DECLARE_REFLECTION(BackEase, EasingFunctionBase)
};

}
}

#endif
