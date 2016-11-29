////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LINEARKEYFRAME_H__
#define __GUI_LINEARKEYFRAME_H__


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
template<class T> const NsChar* LinearKeyFrameIdOf();
//@}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Animates from the T value of the previous key frame to its own Value using linear 
/// interpolation. Existing types are:
///
/// LinearDoubleKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.lineardoublekeyframe.aspx
///
///
/// LinearInt16KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.linearint16keyframe.aspx
///
///
/// LinearInt32KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.linearint32keyframe.aspx
///
///
/// LinearColorKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.linearcolorkeyframe.aspx
///
///
/// LinearPointKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.linearpointkeyframe.aspx
///
///
/// LinearRectKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.linearrectkeyframe.aspx
///
///
/// LinearSizeKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.linearsizekeyframe.aspx
///
///
/// LinearThicknessKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.linearthicknesskeyframe.aspx
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class LinearKeyFrame: public KeyFrame<T>
{
public:
    LinearKeyFrame();
    ~LinearKeyFrame();

protected:
    /// From KeyFrame
    //@{
    T InterpolateValueCore(typename Core::Param<T>::Type baseValue, 
        NsFloat32 keyFrameProgress);
    //@}

    NS_DECLARE_REFLECTION(LinearKeyFrame, KeyFrame<T>)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef LinearKeyFrame<NsFloat32> LinearDoubleKeyFrame;
typedef LinearKeyFrame<NsInt16> LinearInt16KeyFrame;
typedef LinearKeyFrame<NsInt32> LinearInt32KeyFrame;
//typedef LinearKeyFrame<NsInt64> LinearInt64KeyFrame; Need a ParameterType-like method for Reflected types
typedef LinearKeyFrame<Noesis::Drawing::Color> LinearColorKeyFrame;
typedef LinearKeyFrame<Noesis::Drawing::Point> LinearPointKeyFrame;
typedef LinearKeyFrame<Noesis::Drawing::Rect> LinearRectKeyFrame;
typedef LinearKeyFrame<Noesis::Drawing::Size> LinearSizeKeyFrame;
typedef LinearKeyFrame<Noesis::Drawing::Thickness> LinearThicknessKeyFrame;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> inline const NsChar* LinearKeyFrameIdOf<DoubleKeyFrame>() 
{ return "LinearDoubleKeyFrame"; }
template<> inline const NsChar* LinearKeyFrameIdOf<Int16KeyFrame>() 
{ return "LinearInt16KeyFrame"; }
template<> inline const NsChar* LinearKeyFrameIdOf<Int32KeyFrame>() 
{ return "LinearInt32KeyFrame"; }
//template<> inline const NsChar* LinearKeyFrameIdOf<Int64KeyFrame>() { return "LinearInt64KeyFrame"; }
template<> inline const NsChar* LinearKeyFrameIdOf<ColorKeyFrame>() 
{ return "LinearColorKeyFrame"; }
template<> inline const NsChar* LinearKeyFrameIdOf<PointKeyFrame>() 
{ return "LinearPointKeyFrame"; }
template<> inline const NsChar* LinearKeyFrameIdOf<RectKeyFrame>() 
{ return "LinearRectKeyFrame"; }
template<> inline const NsChar* LinearKeyFrameIdOf<SizeKeyFrame>() 
{ return "LinearSizeKeyFrame"; }
template<> inline const NsChar* LinearKeyFrameIdOf<ThicknessKeyFrame>() 
{ return "LinearThicknessKeyFrame"; }

#ifndef SWIG

/// Explicit template instantiations
//@{
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<NsFloat32>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<NsInt16>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<NsInt32>;
//NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<NsInt64>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<Noesis::Drawing::Color>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<Noesis::Drawing::Point>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<Noesis::Drawing::Rect>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<Noesis::Drawing::Size>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API LinearKeyFrame<Noesis::Drawing::Thickness>;
//@}

#endif // SWIG

}
}


#endif
