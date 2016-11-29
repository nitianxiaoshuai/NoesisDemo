////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_KEYFRAME_H__
#define __GUI_KEYFRAME_H__


#include <Noesis.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/Freezable.h>
#include <NsGui/IUITreeNode.h>
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
class KeyTime;
template<class T> const NsChar* KeyFrameIdOf();
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Abstract class that, when implemented, defines an animation segment with its own target value
/// and interpolation method for an AnimationUsingKeyFrames.
///
/// BooleanKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.booleankeyframe.aspx
///
///
/// DoubleKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.doublekeyframe.aspx
///
///
/// Int16KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.int16keyframe.aspx
///
///
/// Int32KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.int32keyframe.aspx
///
///
/// ColorKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.colorkeyframe.aspx
///
///
/// PointKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.pointkeyframe.aspx
///
///
/// RectKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.rectkeyframe.aspx
///
///
/// SizeKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.sizekeyframe.aspx
///
///
/// ThicknessKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.thicknesskeyframe.aspx
///
///
/// ObjectKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.objectkeyframe.aspx
///
///
/// StringKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.stringkeyframe.aspx
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class KeyFrame: public Freezable, public IUITreeNode
{
public:
    KeyFrame();
    ~KeyFrame();

    /// Gets or sets the time at which the key frame's target KeyFrame::Value should be reached
    //@{
    const KeyTime& GetKeyTime() const;
    void SetKeyTime(const KeyTime& time);
    //@}

    // Property Type  | ValueType
    // -----------------------------------------
    // Ptr<T>           T*
    // NsString         const NsChar*
    // T                T (basic types) or T&
    typedef typename Noesis::Gui::SetValueType<T>::Type ValueType;

    /// Gets or sets the key frame's target value.
    //@{
    ValueType GetValue() const;
    void SetValue(ValueType value);
    //@}

    // Property Type | ParamType
    // --------------------------------
    // Ptr<T>          const Ptr<T>&
    // Color           const Color&
    // NsString        const NsString&
    // T               T (basic types)
    typedef typename Noesis::Core::Param<T>::Type ParamType;

    /// Interpolates the base value by the specified progress to reach this KeyFrame value
    Ptr<Core::BaseComponent> InterpolateValue(ParamType baseValue, NsFloat32 keyFrameProgress);
    
    /// Helper methods to be used from AnimationUsingKeyFrames (could be eliminated if the later
    /// class uses another template argument with the type of the value)
    //@{
    static Ptr<Core::BaseComponent> BoxValue(ParamType value);
    static T UnboxValue(Core::BaseComponent* value);

    /// Calculates the distance between 2 values
    static NsFloat32 Len(ParamType a, ParamType b);
    //@}

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* KeyTimeProperty;
    static const DependencyProperty* ValueProperty;
    //@}

protected:
    virtual T InterpolateValueCore(ParamType baseValue, NsFloat32 keyFrameProgress) = 0;

    /// From DependencyObject
    //@{
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue);
    //@}

private:
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(KeyFrame, Freezable)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef KeyFrame<NsBool> BooleanKeyFrame;
typedef KeyFrame<NsFloat32> DoubleKeyFrame;
typedef KeyFrame<NsInt16> Int16KeyFrame;
typedef KeyFrame<NsInt32> Int32KeyFrame;
//typedef KeyFrame<NsInt64> Int64KeyFrame; Need a ParameterType-like method for Reflected types
typedef KeyFrame<Noesis::Drawing::Color> ColorKeyFrame;
typedef KeyFrame<Noesis::Drawing::Point> PointKeyFrame;
typedef KeyFrame<Noesis::Drawing::Rect> RectKeyFrame;
typedef KeyFrame<Noesis::Drawing::Size> SizeKeyFrame;
typedef KeyFrame<Noesis::Drawing::Thickness> ThicknessKeyFrame;
typedef KeyFrame<Ptr<Noesis::Core::BaseComponent> > ObjectKeyFrame;
typedef KeyFrame<NsString> StringKeyFrame;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> inline const NsChar* KeyFrameIdOf<BooleanKeyFrame>() { return "BooleanKeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<DoubleKeyFrame>() { return "DoubleKeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<Int16KeyFrame>() { return "Int16KeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<Int32KeyFrame>() { return "Int32KeyFrame"; }
//template<> inline const NsChar* KeyFrameIdOf<Int64KeyFrame>() { return "Int64KeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<ColorKeyFrame>() { return "ColorKeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<PointKeyFrame>() { return "PointKeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<RectKeyFrame>() { return "RectKeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<SizeKeyFrame>() { return "SizeKeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<ThicknessKeyFrame>() { return "ThicknessKeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<ObjectKeyFrame>() { return "ObjectKeyFrame"; }
template<> inline const NsChar* KeyFrameIdOf<StringKeyFrame>() { return "StringKeyFrame"; }

#ifndef SWIG

/// Explicit template instantiations
//@{
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<NsBool>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<NsFloat32>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<NsInt16>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<NsInt32>;
//NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<NsInt64>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<Noesis::Drawing::Color>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<Noesis::Drawing::Point>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<Noesis::Drawing::Rect>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<Noesis::Drawing::Size>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<Noesis::Drawing::Thickness>;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<Ptr<Noesis::Core::BaseComponent> >;
NS_EXTERN_TEMPLATE class NS_GUI_ANIMATION_API KeyFrame<NsString>;
//@}

#endif // SWIG

}
}


#endif
