////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MATRIXTRANSFORM_H__
#define __GUI_MATRIXTRANSFORM_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Transform.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{

// Forward declarations
//@{
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
/// Creates an arbitrary affine matrix transformation that is used to manipulate
/// objects or coordinate systems in a 2-D plane.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.matrixtransform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API MatrixTransform: public Transform, public IRenderProxyCreator
{
public:
    MatrixTransform();
    MatrixTransform(const Math::Transform2f& matrix);
    ~MatrixTransform();

    /// Parses a string value to create an instance of a MatrixTransform
    static Ptr<MatrixTransform> Parse(const NsChar* str);
    static NsBool TryParse(const NsChar* str, Ptr<BaseComponent>& result);

    /// Gets or sets matrix
    //@{
    const Math::Transform2f& GetMatrix() const;
    void SetMatrix(const Math::Transform2f& matrix);
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
    static const DependencyProperty* MatrixProperty;
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
        UpdateFlags_Matrix
    };

    NS_DECLARE_REFLECTION(MatrixTransform, Transform)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
