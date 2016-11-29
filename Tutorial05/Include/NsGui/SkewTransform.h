////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SKEWTRANSFORM_H__
#define __GUI_SKEWTRANSFORM_H__


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
/// Represents a 2-D skew. It is useful for creating the illusion of 3-dimensional
/// depth in a 2D object.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.skewtransform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SkewTransform: public Transform, public IRenderProxyCreator
{
public:
    SkewTransform();
    SkewTransform(NsFloat32 angleX, NsFloat32 angleY);
    ~SkewTransform();

    /// Gets or sets the x-axis skew angle, which is measured in degrees counterclockwise from
    /// the y-axis
    //@{
    NsFloat32 GetAngleX() const;
    void SetAngleX(NsFloat32 angleX);
    //@}

    /// Gets or sets the y-axis skew angle, which is measured in degrees counterclockwise from
    /// the x-axis
    //@{
    NsFloat32 GetAngleY() const;
    void SetAngleY(NsFloat32 angleY);
    //@}

    ///Gets or sets the x-coordinate of the transform center
    //@{
    NsFloat32 GetCenterX() const;
    void SetCenterX(NsFloat32 centerX);
    //@}

    /// Gets or sets the y-coordinate of the transform center
    //@{
    NsFloat32 GetCenterY() const;
    void SetCenterY(NsFloat32 centerY);
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
    static const DependencyProperty* AngleXProperty;
    static const DependencyProperty* AngleYProperty;
    static const DependencyProperty* CenterXProperty;
    static const DependencyProperty* CenterYProperty;
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
        UpdateFlags_AngleX,
        UpdateFlags_AngleY,
        UpdateFlags_CenterX,
        UpdateFlags_CenterY
    };

    NS_DECLARE_REFLECTION(SkewTransform, Transform)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
