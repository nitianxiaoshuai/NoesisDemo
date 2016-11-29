////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BOUNCEEASE_H__
#define __GUI_BOUNCEEASE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/EasingFunctionBase.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an easing function that creates an animated bouncing effect.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.bounceease.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API BounceEase: public EasingFunctionBase
{
public:
    BounceEase();

    /// Gets or sets the number of bounces. 
    //@{
    NsInt32 GetBounces() const;
    void SetBounces(NsInt32 bounces);
    //@}
    
    /// Gets or sets a value that specifies how bouncy the bounce animation is. Low values of this 
    /// property result in bounces with little lose of height between bounces (more bouncy) while 
    /// high values result in dampened bounces (less bouncy). 
    //@{
    NsFloat32 GetBounciness() const;
    void SetBounciness(NsFloat32 bounciness);
    //@}
    
public:
    static const DependencyProperty* BouncesProperty;
    static const DependencyProperty* BouncinessProperty;

protected:
    /// From EasingFunctionBase
    //@{
    NsFloat32 EaseInCore(NsFloat32 normalizedTime);
    //@}
    
    NS_DECLARE_REFLECTION(BounceEase, EasingFunctionBase)
};

}
}

#endif
