////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1476]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ANIMATION_H__
#define __GUI_ANIMATION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/BaseAnimation.h>
#include <NsGui/AnimationApi.h>
#include <NsDrawing/Color.h>
#include <NsDrawing/Point.h>
#include <NsDrawing/Rect.h>
#include <NsDrawing/Size.h>
#include <NsDrawing/Thickness.h>


namespace Noesis
{
// Forward declarations
//@{
namespace Core
{
template<class T> class Nullable;
}
//@}
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Animates the value of a T property between two 'target values' using linear interpolation (it
/// can be modulated by the easing function specified in the base class) over a specified Duration.
/// See `SingleTimelines <Gui.Animation.SingleTimelines.html>`_ for an explanation of target values.
/// Existing types are:
///
/// DoubleAnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.doubleanimation.aspx
///
///
/// Int16AnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.int16animation.aspx
///
///
/// Int32AnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.int32animation.aspx
///
///
/// Int64AnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.int64animation.aspx
///
///
/// ColorAnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.coloranimation.aspx
///
///
/// PointAnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.pointanimation.aspx
///
///
/// RectAnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.rectanimation.aspx
///
///
/// SizeAnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.sizeanimation.aspx
///
///
/// ThicknessAnimationUsingKeyFrames:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.thicknessanimation.aspx
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class Animation: public BaseAnimation
{
public:
    Animation();
    ~Animation();

    /// Gets or sets the total amount by which the animation changes its starting value
    //@{
    const Core::Nullable<T>& GetBy() const;
    void SetBy(const Core::Nullable<T>& by);
    //@}

    /// Gets or sets the animation's starting value
    //@{
    const Core::Nullable<T>& GetFrom() const;
    void SetFrom(const Core::Nullable<T>& from);
    //@}

    /// Gets or sets the animation's ending value
    //@{
    const Core::Nullable<T>& GetTo() const;
    void SetTo(const Core::Nullable<T>& to);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ByProperty;
    static const DependencyProperty* FromProperty;
    static const DependencyProperty* ToProperty;
    //@}

private:
    void ValidateAnimationType();

    T GetEffectiveFrom(NsBool isAdditive, typename Core::Param<T>::Type origin) const;
    T GetEffectiveTo(NsBool isAdditive, typename Core::Param<T>::Type origin) const;

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Freezable
    //@{
    void CloneCommonCore(const Freezable* source);
    //@}

    /// From AnimationTimeline
    //@{
    Ptr<BaseComponent> GetAnimatedValue(BaseComponent* defaultOrigin, 
        BaseComponent* defaultDestination, AnimationClock* clock);
    Ptr<AnimationTimeline> CreateTransitionFrom() const;
    Ptr<AnimationTimeline> CreateTransitionTo() const;
    //@}

private:
    enum AnimationType
    {
        AnimationType_Unknown,
        AnimationType_FromTo,
        AnimationType_FromBy,
        AnimationType_From,
        AnimationType_To,
        AnimationType_By,
        AnimationType_Reset
    };

    AnimationType mAnimationType;

    NS_DECLARE_REFLECTION(Animation, BaseAnimation)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTE: Animation<NsFloat32> is named as DoubleAnimation to be compatible with Blend types
typedef Animation<NsFloat32> DoubleAnimation;
typedef Animation<NsInt16> Int16Animation;
typedef Animation<NsInt32> Int32Animation;
//typedef Animation<NsInt64> Int64Animation;
typedef Animation<Noesis::Drawing::Color> ColorAnimation;
typedef Animation<Noesis::Drawing::Point> PointAnimation;
typedef Animation<Noesis::Drawing::Rect> RectAnimation;
typedef Animation<Noesis::Drawing::Size> SizeAnimation;
typedef Animation<Noesis::Drawing::Thickness> ThicknessAnimation;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> const NsChar* AnimationIdOf();
template<> inline const NsChar* AnimationIdOf<DoubleAnimation>() { return "DoubleAnimation";}
template<> inline const NsChar* AnimationIdOf<Int16Animation>() { return "Int16Animation";}
template<> inline const NsChar* AnimationIdOf<Int32Animation>() { return "Int32Animation";}
//template<> inline const NsChar* AnimationIdOf<Int64Animation>() { return "Int64Animation";}
template<> inline const NsChar* AnimationIdOf<ColorAnimation>() { return "ColorAnimation";}
template<> inline const NsChar* AnimationIdOf<PointAnimation>() { return "PointAnimation";}
template<> inline const NsChar* AnimationIdOf<RectAnimation>() { return "RectAnimation";}
template<> inline const NsChar* AnimationIdOf<SizeAnimation>() { return "SizeAnimation";}
template<> inline const NsChar* AnimationIdOf<ThicknessAnimation>() { return "ThicknessAnimation";}

#ifndef SWIG 

/// Explicit template instantiations
//@{
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<NsFloat32>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<NsInt16>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<NsInt32>;
//NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<NsInt64>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<Noesis::Drawing::Color>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<Noesis::Drawing::Point>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<Noesis::Drawing::Rect>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<Noesis::Drawing::Size>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API Animation<Noesis::Drawing::Thickness>;
//@}

#endif // SWIG

}
}


#endif
