////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ROTATETRANSFORM_H__
#define __GUI_ROTATETRANSFORM_H__


#include <Noesis.h>
#include <NsGui/Transform.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Rotates an object clockwise about a specified point in 2D coordinate system.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.rotatetransform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RotateTransform: public Transform, public IRenderProxyCreator
{
public:
    RotateTransform();
    RotateTransform(NsFloat32 angle);
    ~RotateTransform();

    /// Gets or sets the angle, in degrees, of clockwise rotation
    //@{
    NsFloat32 GetAngle() const;
    void SetAngle(NsFloat32 angle);
    //@}
    
    /// Gets or sets the x-coordinate of the rotation center point
    //@{
    NsFloat32 GetCenterX() const;
    void SetCenterX(NsFloat32 centerX);
    //@}
    
    /// Gets or sets the y-coordinate of the rotation center point
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
    static const DependencyProperty* AngleProperty;
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
        UpdateFlags_Angle,
        UpdateFlags_CenterX,
        UpdateFlags_CenterY
    };

    NS_DECLARE_REFLECTION(RotateTransform, Transform)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
