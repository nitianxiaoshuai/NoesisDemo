////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRADIENTSTOPCOLLECTION_H__
#define __GUI_GRADIENTSTOPCOLLECTION_H__


#include <Noesis.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/GradientStop.h>
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
/// Represents a collection of GradientStop objects that can be individually accessed by index.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API GradientStopCollection: public FreezableCollection, public IRenderProxyCreator
{
public:
    /// Constructor
    GradientStopCollection();

    /// Destructor
    ~GradientStopCollection();

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UnregisterRenderer(ViewId viewId);
    //@}

protected:
    /// From FreezableCollection
    //@{
    void CheckItem(Core::BaseComponent* item) const;
    void OnItemAdded(Core::BaseComponent* item, NsSize index);
    void OnItemRemoved(Core::BaseComponent* item, NsSize index);
    //@}

private:
    void RegisterChild(Core::BaseComponent* item);
    void UnregisterChild(Core::BaseComponent* item);
    void OnChildChanged(Freezable* obj, FreezableEventReason reason);

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Stops
    };

    NS_DECLARE_REFLECTION(GradientStopCollection, FreezableCollection)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
