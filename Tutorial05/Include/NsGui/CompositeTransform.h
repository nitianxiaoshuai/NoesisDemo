////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMPOSITETRANSFORM_H__
#define __GUI_COMPOSITETRANSFORM_H__


#include <Noesis.h>
#include <NsGui/Transform.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Gui
{
class DependencyProperty;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// This class lets you apply multiple different transforms to an object. The transformations run
/// in the following order:  scale -> skew -> rotate -> translate.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.compositetransform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API CompositeTransform: public Transform, public IRenderProxyCreator
{
public:
    CompositeTransform();
    ~CompositeTransform();

    /// Gets or sets the x-coordinate of the center point for all transforms
    //@{
    NsFloat32 GetCenterX() const;
    void SetCenterX(NsFloat32 centerX);
    //@}

    /// Gets or sets the y-coordinate of the center point for all transforms
    //@{
    NsFloat32 GetCenterY() const;
    void SetCenterY(NsFloat32 centerY);
    //@}

    /// Gets or sets the angle, in degrees, of clockwise rotation
    //@{
    NsFloat32 GetRotation() const;
    void SetRotation(NsFloat32 angle);
    //@}

    /// Gets or sets the x-axis scale factor. You can use this property to stretch or shrink an
    /// object horizontally
    //@{
    NsFloat32 GetScaleX() const;
    void SetScaleX(NsFloat32 scaleX);
    //@}

    /// Gets or sets the y-axis scale factor. You can use this property to stretch or shrink an
    /// object vertically
    //@{
    NsFloat32 GetScaleY() const;
    void SetScaleY(NsFloat32 scaleY);
    //@}

    /// Gets or sets the x-axis skew angle, which is measured in degrees counterclockwise from the
    /// y-axis
    //@{
    NsFloat32 GetSkewX() const;
    void SetSkewX(NsFloat32 angleX);
    //@}

    /// Gets or sets the y-axis skew angle, which is measured in degrees counterclockwise from the
    /// x-axis
    //@{
    NsFloat32 GetSkewY() const;
    void SetSkewY(NsFloat32 angleY);
    //@}

    /// Gets or sets the distance to translate along the x-axis
    //@{
    NsFloat32 GetTranslateX() const;
    void SetTranslateX(NsFloat32 x);
    //@}

    /// Gets or sets the distance to translate along the y-axis
    //@{
    NsFloat32 GetTranslateY() const;
    void SetTranslateY(NsFloat32 y);
    //@}

    /// From Transform
    //@{
    Math::Transform2f GetTransform() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UnregisterRenderer(ViewId viewId);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* CenterXProperty;
    static const DependencyProperty* CenterYProperty;
    static const DependencyProperty* RotationProperty;
    static const DependencyProperty* ScaleXProperty;
    static const DependencyProperty* ScaleYProperty;
    static const DependencyProperty* SkewXProperty;
    static const DependencyProperty* SkewYProperty;
    static const DependencyProperty* TranslateXProperty;
    static const DependencyProperty* TranslateYProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& e);
    //@}

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_CenterX,
        UpdateFlags_CenterY,
        UpdateFlags_Rotation,
        UpdateFlags_ScaleX,
        UpdateFlags_ScaleY,
        UpdateFlags_SkewX,
        UpdateFlags_SkewY,
        UpdateFlags_TranslateX,
        UpdateFlags_TranslateY
    };

    NS_DECLARE_REFLECTION(CompositeTransform, Transform)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
