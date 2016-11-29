////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_EASINGFUNCTIONBASE_H__
#define __GUI_EASINGFUNCTIONBASE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/Freezable.h>
#include <NsGui/IEasingFunction.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

/// Specifies how the animation associated with an easing function interpolates.
enum EasingMode
{
    /// Interpolation follows 100% interpolation minus the output of the formula associated with 
    /// the easing function
    EasingMode_EaseOut,
    /// Interpolation follows the mathematical formula associated with the easing function
    EasingMode_EaseIn,
    /// Interpolation uses EaseIn for the first half of the animation and EaseOut for the second 
    /// half
    EasingMode_EaseInOut
};

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides the base class for all the easing functions. You can create your
/// own custom easing functions by inheriting from this class.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingfunctionbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API EasingFunctionBase: public Freezable, public IEasingFunction
{
public:
    EasingFunctionBase();
    virtual ~EasingFunctionBase() = 0;

    /// Gets or sets a value that specifies how the animation interpolates
    //@{
    EasingMode GetEasingMode() const;
    void SetEasingMode(EasingMode mode);
    //@}

    /// From IEasingFunction
    //@{
    NsFloat32 Ease(NsFloat32 normalizedTime);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* EasingModeProperty;
    //@}
    
protected:
    /// Provides the logic portion of the easing function that you can override to produce the 
    /// EaseIn mode of the custom easing function
    virtual NsFloat32 EaseInCore(NsFloat32 normalizedTime) = 0;

    NS_DECLARE_REFLECTION(EasingFunctionBase, Freezable)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

NS_DECLARE_ENUM(NS_GUI_ANIMATION_API, Noesis::Gui::EasingMode)

#endif