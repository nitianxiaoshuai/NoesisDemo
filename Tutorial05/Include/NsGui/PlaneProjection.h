////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PLANEPROJECTION_H__
#define __GUI_PLANEPROJECTION_H__


#include <Noesis.h>
#include <NsGui/Projection.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a perspective transform (a 3D-like effect) on an object.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.planeprojection.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API PlaneProjection: public Projection, public IRenderProxyCreator
{
public:
    /// Constructor
    PlaneProjection();

    /// Destructor
    ~PlaneProjection();

    static Math::Matrix4f ConstructProjectionMatrix(
        const Drawing::Size& surface, const Drawing::Size& size,
        NsFloat32 centerX, NsFloat32 centerY, NsFloat32 centerZ,
        NsFloat32 globalOffX, NsFloat32 globalOffY, NsFloat32 globalOffZ,
        NsFloat32 localOffX, NsFloat32 localOffY, NsFloat32 localOffZ,
        NsFloat32 rotX, NsFloat32 rotY, NsFloat32 rotZ);

    /// Gets or sets the x-coordinate of the center of rotation of the object you rotate
    //@{
    NsFloat32 GetCenterOfRotationX() const;
    void SetCenterOfRotationX(NsFloat32 centerX);
    //@}

    /// Gets or sets the y-coordinate of the center of rotation of the object you rotate
    //@{
    NsFloat32 GetCenterOfRotationY() const;
    void SetCenterOfRotationY(NsFloat32 centerY);
    //@}

    /// Gets or sets the z-coordinate of the center of rotation of the object you rotate
    //@{
    NsFloat32 GetCenterOfRotationZ() const;
    void SetCenterOfRotationZ(NsFloat32 centerZ);
    //@}

    /// Gets or sets the distance the object is translated along the x-axis of the screen
    //@{
    NsFloat32 GetGlobalOffsetX() const;
    void SetGlobalOffsetX(NsFloat32 offsetX);
    //@}

    /// Gets or sets the distance the object is translated along the y-axis of the screen
    //@{
    NsFloat32 GetGlobalOffsetY() const;
    void SetGlobalOffsetY(NsFloat32 offsetY);
    //@}

    /// Gets or sets the distance the object is translated along the z-axis of the screen
    //@{
    NsFloat32 GetGlobalOffsetZ() const;
    void SetGlobalOffsetZ(NsFloat32 offsetZ);
    //@}

    /// Gets or sets the distance the object is translated along the x-axis of the plane of the
    /// object
    //@{
    NsFloat32 GetLocalOffsetX() const;
    void SetLocalOffsetX(NsFloat32 offsetX);
    //@}

    /// Gets or sets the distance the object is translated along the y-axis of the plane of the
    /// object
    NsFloat32 GetLocalOffsetY() const;
    void SetLocalOffsetY(NsFloat32 offsetY);
    //@}

    /// Gets or sets the distance the object is translated along the z-axis of the plane of the
    /// object
    //@{
    NsFloat32 GetLocalOffsetZ() const;
    void SetLocalOffsetZ(NsFloat32 offsetZ);
    //@}

    /// Gets the projection matrix on the PlaneProjection
    const Math::Matrix4f& GetProjectionMatrix() const;

    /// Gets or sets the number of degrees to rotate the object around the x-axis of rotation
    //@{
    NsFloat32 GetRotationX() const;
    void SetRotationX(NsFloat32 rotationX);
    //@}

    /// Gets or sets the number of degrees to rotate the object around the y-axis of rotation
    //@{
    NsFloat32 GetRotationY() const;
    void SetRotationY(NsFloat32 rotationY);
    //@}

    /// Gets or sets the number of degrees to rotate the object around the z-axis of rotation
    //@{
    NsFloat32 GetRotationZ() const;
    void SetRotationZ(NsFloat32 rotationZ);
    //@}

    /// From Projection
    //@{
    NsBool IsIdentity() const;
    Math::Matrix4f GetProjection(const Drawing::Size& surface, const Drawing::Size& size) const;
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
    static const DependencyProperty* CenterOfRotationXProperty;
    static const DependencyProperty* CenterOfRotationYProperty;
    static const DependencyProperty* CenterOfRotationZProperty;
    static const DependencyProperty* GlobalOffsetXProperty;
    static const DependencyProperty* GlobalOffsetYProperty;
    static const DependencyProperty* GlobalOffsetZProperty;
    static const DependencyProperty* LocalOffsetXProperty;
    static const DependencyProperty* LocalOffsetYProperty;
    static const DependencyProperty* LocalOffsetZProperty;
    static const DependencyProperty* ProjectionMatrixProperty;
    static const DependencyProperty* RotationXProperty;
    static const DependencyProperty* RotationYProperty;
    static const DependencyProperty* RotationZProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    void UpdateMatrix();
    Math::Matrix4f ConstructMatrix(
        NsFloat32 cX, NsFloat32 cY, NsFloat32 cZ,
        NsFloat32 gX, NsFloat32 gY, NsFloat32 gZ,
        NsFloat32 lX, NsFloat32 lY, NsFloat32 lZ,
        NsFloat32 rX, NsFloat32 rY, NsFloat32 rZ) const;

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_CenterOfRotationX,
        UpdateFlags_CenterOfRotationY,
        UpdateFlags_CenterOfRotationZ,
        UpdateFlags_GlobalOffsetX,
        UpdateFlags_GlobalOffsetY,
        UpdateFlags_GlobalOffsetZ,
        UpdateFlags_LocalOffsetX,
        UpdateFlags_LocalOffsetY,
        UpdateFlags_LocalOffsetZ,
        UpdateFlags_RotationX,
        UpdateFlags_RotationY,
        UpdateFlags_RotationZ
    };

    NS_DECLARE_REFLECTION(PlaneProjection, Projection)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
