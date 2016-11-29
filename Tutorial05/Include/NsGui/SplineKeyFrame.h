////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SPLINEKEYFRAME_H__
#define __GUI_SPLINEKEYFRAME_H__


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
class KeySpline;
template<class T> const NsChar* SplineKeyFrameIdOf();
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Animates from the value of the previous key frame to its own value using splined interpolation.
///
/// SplineDoubleKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.splinedoublekeyframe.aspx
///
///
/// SplineInt16KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.splineint16keyframe.aspx
///
///
/// SplineInt32KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.splineint32keyframe.aspx
///
///
/// SplineColorKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.splinecolorkeyframe.aspx
///
///
/// SplinePointKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.splinepointkeyframe.aspx
///
///
/// SplineRectKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.splinerectkeyframe.aspx
///
///
/// SplineSizeKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.splinesizekeyframe.aspx
///
///
/// SplineThicknessKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.splinethicknesskeyframe.aspx
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class SplineKeyFrame: public KeyFrame<T>
{
public:
    SplineKeyFrame();
    ~SplineKeyFrame();
    
    /// Gets or sets the two control points that define animation progress for this key frame
    //@{
    KeySpline* GetKeySpline() const;
    void SetKeySpline(KeySpline* spline);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* KeySplineProperty;
    //@}
    
protected:
    /// From KeyFrame
    //@{
    T InterpolateValueCore(typename Core::Param<T>::Type baseValue, 
        NsFloat32 keyFrameProgress);
    //@}
    
    NS_DECLARE_REFLECTION(SplineKeyFrame, KeyFrame<T>)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef SplineKeyFrame<NsFloat32> SplineDoubleKeyFrame;
typedef SplineKeyFrame<NsInt16> SplineInt16KeyFrame;
typedef SplineKeyFrame<NsInt32> SplineInt32KeyFrame;
//typedef SplineKeyFrame<NsInt64> SplineInt64KeyFrame; Need a ParameterType-like method for Reflected types
typedef SplineKeyFrame<Noesis::Drawing::Color> SplineColorKeyFrame;
typedef SplineKeyFrame<Noesis::Drawing::Point> SplinePointKeyFrame;
typedef SplineKeyFrame<Noesis::Drawing::Rect> SplineRectKeyFrame;
typedef SplineKeyFrame<Noesis::Drawing::Size> SplineSizeKeyFrame;
typedef SplineKeyFrame<Noesis::Drawing::Thickness> SplineThicknessKeyFrame;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
inline const NsChar* SplineKeyFrameIdOf<DoubleKeyFrame>() { return "SplineDoubleKeyFrame"; }
template<>
inline const NsChar* SplineKeyFrameIdOf<Int16KeyFrame>() { return "SplineInt16KeyFrame"; }
template<>
inline const NsChar* SplineKeyFrameIdOf<Int32KeyFrame>() { return "SplineInt32KeyFrame"; }
//template<>
//inline const NsChar* SplineKeyFrameIdOf<Int64KeyFrame>() { return "SplineInt64KeyFrame"; }
template<>
inline const NsChar* SplineKeyFrameIdOf<ColorKeyFrame>() { return "SplineColorKeyFrame"; }
template<>
inline const NsChar* SplineKeyFrameIdOf<PointKeyFrame>() { return "SplinePointKeyFrame"; }
template<>
inline const NsChar* SplineKeyFrameIdOf<RectKeyFrame>() { return "SplineRectKeyFrame"; }
template<>
inline const NsChar* SplineKeyFrameIdOf<SizeKeyFrame>() { return "SplineSizeKeyFrame"; }
template<>
inline const NsChar* SplineKeyFrameIdOf<ThicknessKeyFrame>() { return "SplineThicknessKeyFrame"; }

#ifndef SWIG

/// Explicit template instantiations
//@{
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<NsFloat32>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<NsInt16>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<NsInt32>;
//NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<NsInt64>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<Noesis::Drawing::Color>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<Noesis::Drawing::Point>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<Noesis::Drawing::Rect>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<Noesis::Drawing::Size>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API SplineKeyFrame<Noesis::Drawing::Thickness>;
//@}

#endif // SWIG

}
}


#endif
