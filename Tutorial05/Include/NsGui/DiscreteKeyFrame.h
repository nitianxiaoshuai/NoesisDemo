////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DISCRETEKEYFRAME_H__
#define __GUI_DISCRETEKEYFRAME_H__


#include <Noesis.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/KeyFrame.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
template<class T> const NsChar* DiscreteKeyFrameIdOf();
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Animates from the T value of the previous key frame to its own Value using discrete 
/// interpolation. Existing types are:
///
/// DiscreteBooleanKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discretebooleankeyframe.aspx
///
///
/// DiscreteDoubleKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discretedoublekeyframe.aspx
///
///
/// DiscreteInt16KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discreteint16keyframe.aspx
///
///
/// DiscreteInt32KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discreteint32keyframe.aspx
///
///
/// DiscreteColorKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discretecolorkeyframe.aspx
///
///
/// DiscretePointKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discretepointkeyframe.aspx
///
///
/// DiscreteRectKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discreterectkeyframe.aspx
///
///
/// DiscreteSizeKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discretesizekeyframe.aspx
///
///
/// DiscreteThicknessKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discretethicknesskeyframe.aspx
///
///
/// DiscreteObjectKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discreteobjectkeyframe.aspx
///
///
/// DiscreteStringKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discretestringkeyframe.aspx
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class DiscreteKeyFrame: public KeyFrame<T>
{
public:
    DiscreteKeyFrame();
    ~DiscreteKeyFrame();

protected:
    /// From KeyFrame
    //@{
    T InterpolateValueCore(typename Core::Param<T>::Type baseValue, 
        NsFloat32 keyFrameProgress);
    //@}
    
    NS_DECLARE_REFLECTION(DiscreteKeyFrame, KeyFrame<T>)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef DiscreteKeyFrame<NsBool> DiscreteBooleanKeyFrame;
typedef DiscreteKeyFrame<NsFloat32> DiscreteDoubleKeyFrame;
typedef DiscreteKeyFrame<NsInt16> DiscreteInt16KeyFrame;
typedef DiscreteKeyFrame<NsInt32> DiscreteInt32KeyFrame;
//typedef DiscreteKeyFrame<NsInt64> DiscreteInt64KeyFrame; Need a ParameterType-like method for Reflected types
typedef DiscreteKeyFrame<Noesis::Drawing::Color> DiscreteColorKeyFrame;
typedef DiscreteKeyFrame<Noesis::Drawing::Point> DiscretePointKeyFrame;
typedef DiscreteKeyFrame<Noesis::Drawing::Rect> DiscreteRectKeyFrame;
typedef DiscreteKeyFrame<Noesis::Drawing::Size> DiscreteSizeKeyFrame;
typedef DiscreteKeyFrame<Noesis::Drawing::Thickness> DiscreteThicknessKeyFrame;
typedef DiscreteKeyFrame<Ptr<Noesis::Core::BaseComponent> > DiscreteObjectKeyFrame;
typedef DiscreteKeyFrame<NsString> DiscreteStringKeyFrame;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> inline const NsChar* DiscreteKeyFrameIdOf<BooleanKeyFrame>() 
{ return "DiscreteBooleanKeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<DoubleKeyFrame>() 
{ return "DiscreteDoubleKeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<Int16KeyFrame>() 
{ return "DiscreteInt16KeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<Int32KeyFrame>() 
{ return "DiscreteInt32KeyFrame"; }
//template<> inline const NsChar* DiscreteKeyFrameIdOf<Int64KeyFrame>() 
//{ return "DiscreteInt64KeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<ColorKeyFrame>() 
{ return "DiscreteColorKeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<PointKeyFrame>() 
{ return "DiscretePointKeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<RectKeyFrame>() 
{ return "DiscreteRectKeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<SizeKeyFrame>() 
{ return "DiscreteSizeKeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<ThicknessKeyFrame>() 
{ return "DiscreteThicknessKeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<ObjectKeyFrame>() 
{ return "DiscreteObjectKeyFrame"; }
template<> inline const NsChar* DiscreteKeyFrameIdOf<StringKeyFrame>() 
{ return "DiscreteStringKeyFrame"; }

#ifndef SWIG

/// Explicit template instantiations
//@{
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<NsBool>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<NsFloat32>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<NsInt16>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<NsInt32>;
//NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<NsInt64>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<Noesis::Drawing::Color>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<Noesis::Drawing::Point>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<Noesis::Drawing::Rect>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<Noesis::Drawing::Size>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<Noesis::Drawing::Thickness>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<Ptr<Noesis::Core::BaseComponent> >;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API DiscreteKeyFrame<NsString>;
//@}

#endif // SWIG

}
}


#endif
