////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRANSLATETRANSFORM_H__
#define __GUI_TRANSLATETRANSFORM_H__


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
/// Translates (moves) an object in the 2D coordinate system.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.translatetransform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TranslateTransform: public Transform, public IRenderProxyCreator
{
public:
    TranslateTransform();
    TranslateTransform(NsFloat32 x, NsFloat32 y);
    ~TranslateTransform();

    /// Gets or sets the x-axis displacement
    //@{
    NsFloat32 GetX() const;
    void SetX(NsFloat32 x);
    //@}
    
    /// Gets or sets the y-axis displacement
    //@{
    NsFloat32 GetY() const;
    void SetY(NsFloat32 y);
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
    static const DependencyProperty* XProperty;
    static const DependencyProperty* YProperty;
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
        UpdateFlags_X,
        UpdateFlags_Y
    };

    NS_DECLARE_REFLECTION(TranslateTransform, Transform)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
