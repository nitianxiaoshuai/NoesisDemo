////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MATRIX3DPROJECTION_H__
#define __GUI_MATRIX3DPROJECTION_H__


#include <Noesis.h>
#include <NsGui/Projection.h>
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
/// Applies a 3D Matrix to an object.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.matrix3dprojection.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Matrix3DProjection: public Projection, public IRenderProxyCreator
{
public:
    /// Constructor
    Matrix3DProjection();

    /// Destructor
    ~Matrix3DProjection();

    /// Gets or sets the Matrix3D  that is used for the projection that is applied to the object
    //@{
    const Math::Matrix4f& GetProjectionMatrix() const;
    void SetProjectionMatrix(const Math::Matrix4f& matrix);
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
    static const DependencyProperty* ProjectionMatrixProperty;
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
        UpdateFlags_ProjectionMatrix
    };

    NS_DECLARE_REFLECTION(Matrix3DProjection, Projection)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
