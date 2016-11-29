////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SCALETRANSFORM_H__
#define __GUI_SCALETRANSFORM_H__


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
namespace Math
{
template<class T> class Transform2;
typedef Noesis::Math::Transform2<NsFloat32> Transform2f;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Scales an object in the 2D coordinate system.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.scaletransform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ScaleTransform: public Transform, public IRenderProxyCreator
{
public:
    ScaleTransform();
    ScaleTransform(NsFloat32 scaleX, NsFloat32 scaleY);
    ~ScaleTransform();

    /// Gets or sets the x-axis scale factor
    //@{
    NsFloat32 GetScaleX() const;
    void SetScaleX(NsFloat32 scaleX);
    //@}
    
    /// Gets or sets the y-axis scale factor
    //@{
    NsFloat32 GetScaleY() const;
    void SetScaleY(NsFloat32 scaleY);
    //@}
    
    /// Gets or sets the x-coordinate of the scale center point
    //@{
    NsFloat32 GetCenterX() const;
    void SetCenterX(NsFloat32 centerX);
    //@}
    
    /// Gets or sets the y-coordinate of the scale center point
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
    static const DependencyProperty* CenterXProperty;
    static const DependencyProperty* CenterYProperty;
    static const DependencyProperty* ScaleXProperty;
    static const DependencyProperty* ScaleYProperty;
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
        UpdateFlags_ScaleX,
        UpdateFlags_ScaleY
    };

    NS_DECLARE_REFLECTION(ScaleTransform, Transform)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
