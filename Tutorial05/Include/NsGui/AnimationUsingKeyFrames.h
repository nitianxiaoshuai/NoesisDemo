////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ANIMATIONUSINGKEYFRAMES_H__
#define __GUI_ANIMATIONUSINGKEYFRAMES_H__


#include <Noesis.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/AnimationTimeline.h>
#include <NsGui/Duration.h>
#include <NsDrawing/Color.h>
#include <NsDrawing/Point.h>
#include <NsDrawing/Rect.h>
#include <NsDrawing/Size.h>
#include <NsDrawing/Thickness.h>
#include <NsCore/String.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
template<class T> class KeyFrame;
template<class T> class TypedFreezableCollection;
template<class T> const NsChar* AnimationUsingKeyFramesIdOf();
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Animates the value of a T property along a set of KeyFrames.
/// Existing types are:
///
/// *BooleanAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.booleananimationusingkeyframes.aspx
///
///
/// *DoubleAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.doubleanimationusingkeyframes.aspx
///
///
/// *Int16AnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.int16animationusingkeyframes.aspx
///
///
/// *Int32AnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.int32animationusingkeyframes.aspx
///
///
/// *ColorAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.coloranimationusingkeyframes.aspx
///
///
/// *PointAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.pointanimationusingkeyframes.aspx
///
///
/// *RectAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.rectanimationusingkeyframes.aspx
///
///
/// *SizeAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.sizeanimationusingkeyframes.aspx
///
///
/// *ThicknessAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.thicknessanimationusingkeyframes.aspx
///
///
/// *ObjectAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.objectanimationusingkeyframes.aspx
///
///
/// *StringAnimationUsingKeyFrames*:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.stringanimationusingkeyframes.aspx
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class AnimationUsingKeyFrames: public AnimationTimeline
{
public:
    AnimationUsingKeyFrames();
    ~AnimationUsingKeyFrames();
    
    /// Gets the collection of KeyFrame objects that define the animation
    //@{
    TypedFreezableCollection<KeyFrame<T> >* GetKeyFrames() const;
    //@}
    
    /// From AnimationTimeline
    //@{
    Ptr<BaseComponent> GetAnimatedValue(BaseComponent* defaultOrigin, 
        BaseComponent* defaultDestination, AnimationClock* clock);
    //@}
    
private:
    void EnsureKeyFrames() const;
    
    void OrderFrames(Clock* clock);
    NsInt FindPrevFrame(NsSize current, NsBool checkUniforms) const;
    NsInt FindNextFrame(NsSize current, NsBool checkUniforms) const;

    /// From DependencyObject
    //@{
    void OnInit();
    //@}

    /// From Timeline
    //@{
    Duration GetNaturalDuration(Clock* clock) const;
    Duration GetEffectiveDuration() const;
    //@}
    
    /// From AnimationTimeline
    //@{
    Ptr<AnimationTimeline> CreateTransitionFrom() const;
    Ptr<AnimationTimeline> CreateTransitionTo() const;
    //@}
    
    /// From Freezable
    //@{
    void CloneCommonCore(const Freezable* source);
    //@}

private:
    mutable Ptr<TypedFreezableCollection<KeyFrame<T> > > mKeyFrames;
    
    NsVector<Core::nstl::pair<Ptr<KeyFrame<T> >, NsFloat64> > mOrderedFrames;
    mutable Duration mNaturalDuration;

    NS_DECLARE_REFLECTION(AnimationUsingKeyFrames, AnimationTimeline)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef AnimationUsingKeyFrames<NsBool> BooleanAnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<NsFloat32> DoubleAnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<NsInt16> Int16AnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<NsInt32> Int32AnimationUsingKeyFrames;
//typedef AnimationUsingKeyFrames<Int64> Int64AnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<Noesis::Drawing::Color> ColorAnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<Noesis::Drawing::Point> PointAnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<Noesis::Drawing::Rect> RectAnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<Noesis::Drawing::Size> SizeAnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<Noesis::Drawing::Thickness> ThicknessAnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<Ptr<Noesis::Core::BaseComponent> > ObjectAnimationUsingKeyFrames;
typedef AnimationUsingKeyFrames<NsString> StringAnimationUsingKeyFrames;

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef TypedFreezableCollection<KeyFrame<NsBool> > BooleanKeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<NsFloat32> > DoubleKeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<NsInt16> > Int16KeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<NsInt32> > Int32KeyFrameCollection;
//typedef TypedFreezableCollection<KeyFrame<NsInt64> > Int64KeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<Noesis::Drawing::Color> > ColorKeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<Noesis::Drawing::Point> > PointKeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<Noesis::Drawing::Rect> > RectKeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<Noesis::Drawing::Size> > SizeKeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<Noesis::Drawing::Thickness> > ThicknessKeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<Ptr<Noesis::Core::BaseComponent> > > ObjectKeyFrameCollection;
typedef TypedFreezableCollection<KeyFrame<NsString> > StringKeyFrameCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<BooleanAnimationUsingKeyFrames>() 
{ return "BooleanAnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<DoubleAnimationUsingKeyFrames>() 
{ return "DoubleAnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<Int16AnimationUsingKeyFrames>() 
{ return "Int16AnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<Int32AnimationUsingKeyFrames>() 
{ return "Int32AnimationUsingKeyFrames"; }
//template<> inline const NsChar* AnimationUsingKeyFramesIdOf<Int64AnimationUsingKeyFrames>() 
//{ return "Int64AnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<ColorAnimationUsingKeyFrames>() 
{ return "ColorAnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<PointAnimationUsingKeyFrames>() 
{ return "PointAnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<RectAnimationUsingKeyFrames>() 
{ return "RectAnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<SizeAnimationUsingKeyFrames>() 
{ return "SizeAnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<ThicknessAnimationUsingKeyFrames>() 
{ return "ThicknessAnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<ObjectAnimationUsingKeyFrames>() 
{ return "ObjectAnimationUsingKeyFrames"; }
template<> inline const NsChar* AnimationUsingKeyFramesIdOf<StringAnimationUsingKeyFrames>() 
{ return "StringAnimationUsingKeyFrames"; }

#ifndef SWIG 

/// Explicit template instantiations
//@{
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<NsBool>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<NsFloat32>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<NsInt16>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<NsInt32>;
//NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<NsInt64>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<Noesis::Drawing::Color>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<Noesis::Drawing::Point>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<Noesis::Drawing::Rect>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<Noesis::Drawing::Size>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<Noesis::Drawing::Thickness>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<Ptr<Noesis::Core::BaseComponent> >;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API AnimationUsingKeyFrames<NsString>;
//@}

#endif // SWIG

}
}


#endif
