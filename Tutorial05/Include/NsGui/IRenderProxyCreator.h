////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IRENDERPROXYCREATOR_H__
#define __GUI_IRENDERPROXYCREATOR_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsCore/Ptr.h>
#include <NsGui/CoreApi.h>


#include <NsCore/Map.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
class BaseComponent;
}
namespace Gui
{
class RenderTreeUpdater;
typedef void* ViewId;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IRenderProxyCreator. Creates the proxy used in render thread.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IRenderProxyCreator: public Core::Interface
{
    /// Creates the corresponding render proxy for this object
    virtual void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex) = 0;

    /// Updates the corresponding render proxy for this object
    virtual void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex) = 0;

    /// Unregisters the specified view
    virtual void UnregisterRenderer(ViewId viewId) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IRenderProxyCreator, Core::Interface)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Manages dirty flags of a render proxy creator object
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RenderProxyCreatorFlags
{
public:
    /// Indicates if the specified flag is set for the view
    NsBool Check(NsUInt32 flag, ViewId viewId);

    /// Modifies a flag of the creator for the specified view
    //@{
    void Set(NsUInt32 flag, ViewId viewId);
    void Clear(NsUInt32 flag, ViewId viewId);
    //@}

    /// Modifies a flag of the creator for all the registered views
    //@{
    void Set(NsUInt32 flag);
    void Clear(NsUInt32 flag);
    //@}

    /// Registers the resource in a view
    void RegisterView(ViewId viewId);

    /// Unregisters the resource from the specified view
    void UnregisterRenderer(ViewId viewId);

    /// Notifies all registered views that resource was destroyed
    void NotifyDestroyed(Core::BaseComponent* resource);

private:
    typedef NsMap<ViewId, NsUInt32> Flags;
    Flags mFlags;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
