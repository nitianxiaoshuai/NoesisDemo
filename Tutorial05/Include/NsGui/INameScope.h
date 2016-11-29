////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INAMESCOPE_H__
#define __GUI_INAMESCOPE_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsCore/DelegateForward.h>
#include <NsCore/BaseComponent.h>
#include <NsGui/INameScopeTypes.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// INameScope. Defines how names of elements should be accessed within a particular scope, and how
/// to enforce uniqueness of names within that scope.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE INameScope: public Core::Interface
{
    /// Returns an object that has the provided identifying name
    virtual Core::BaseComponent* FindName(const NsChar* name) const = 0;

    /// Registers the provided name into the current namescope
    virtual void RegisterName(const NsChar* name, Core::BaseComponent* object) = 0;

    /// Unregisters the provided name from the current namescope
    virtual void UnregisterName(const NsChar* name) = 0;

    /// Updates previously registered item with new one. This is usefull to refresh Binginds when
    /// freezables are cloned
    virtual void UpdateName(const NsChar* name, Core::BaseComponent* object) = 0;

    /// Delegate to be notified about events
    typedef Noesis::Core::Delegate<void (INameScope*, const NameScopeChangedArgs&)> ChangedDelegate;
    virtual ChangedDelegate& NameScopeChanged() = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(INameScope, Core::Interface)
};

}
}

#endif
