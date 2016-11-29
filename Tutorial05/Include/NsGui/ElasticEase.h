////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ELASTICEASE_H__
#define __GUI_ELASTICEASE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/EasingFunctionBase.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an easing function that creates an animation that resembles a spring 
/// oscillating back and forth until it comes to rest
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.elasticease.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API ElasticEase: public EasingFunctionBase
{
public:
    ElasticEase();

    /// Gets or sets the number of times the target slides back and forth over the animation 
    /// destination
    //@{
    NsInt32 GetOscillations() const;
    void SetOscillations(NsInt32 oscillations);
    //@}
    
    /// Gets or sets the stiffness of the spring. The smaller the Springiness value is, the stiffer 
    /// the spring and the faster the elasticity decreases in intensity over each oscillation
    //@{
    NsFloat32 GetSpringiness() const;
    void SetSpringiness(NsFloat32 value);
    //@}
    
public:
    static const DependencyProperty* OscillationsProperty;
    static const DependencyProperty* SpringinessProperty;

protected:
    /// From EasingFunctionBase
    //@{
    NsFloat32 EaseInCore(NsFloat32 normalizedTime);
    //@}
    
    NS_DECLARE_REFLECTION(ElasticEase, EasingFunctionBase)
};

}
}

#endif