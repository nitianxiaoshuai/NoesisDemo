////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DASHSTYLE_H__
#define __GUI_DASHSTYLE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
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
/// Represents the sequence of dashes and gaps that will be applied by a Pen.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.dashstyle.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DashStyle: public Animatable, public IRenderProxyCreator
{
public:
    DashStyle();
    ~DashStyle();

    /// Gets or sets the collection of dashes and gaps in this DashStyle
    //@{
    const NsChar* GetDashes() const;
    void SetDashes(const NsChar* dashes);
    //@}

    /// Gets or sets how far in the dash sequence the stroke will start
    //@{
    NsFloat32 GetOffset() const;
    void SetOffset(NsFloat32 offset);
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
    static const DependencyProperty* DashesProperty;
    static const DependencyProperty* OffsetProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Dashes,
        UpdateFlags_Offset
    };

    NS_DECLARE_REFLECTION(DashStyle, Animatable)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
