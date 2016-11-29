////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INOTIFYDICTIONARYCHANGED_H__
#define __GUI_INOTIFYDICTIONARYCHANGED_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/Interface.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
class BaseComponent;
template<class T> class Delegate;
}
namespace Gui
{
NS_INTERFACE IResourceKey;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum NotifyDictionaryChangedAction
{
    /// One item was added to the collection. 
    NotifyDictionaryChangedAction_Add,
    /// One item was removed from the collection. 
    NotifyDictionaryChangedAction_Remove,
    /// One item was replaced in the collection. 
    NotifyDictionaryChangedAction_Replace, 
    /// The content of the collection changed dramatically. 
    NotifyDictionaryChangedAction_Reset,
    NotifyDictionaryChangedAction_PreReset
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Args passed on dictionary changed event notification.
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

struct NS_GUI_CORE_API NotifyDictionaryChangedEventArgs
{
public:
    NotifyDictionaryChangedAction action;
    const IResourceKey* key;
    const Core::BaseComponent* oldValue;
    const Core::BaseComponent* newValue;

    /// Constructor
    NotifyDictionaryChangedEventArgs(NotifyDictionaryChangedAction act, const IResourceKey* k,
        const Core::BaseComponent* oldVal, const Core::BaseComponent* newVal);
    
private:
    NS_DECLARE_REFLECTION(NotifyDictionaryChangedEventArgs, Core::NoParent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Core::Delegate<void (Core::BaseComponent*, const NotifyDictionaryChangedEventArgs&)>
    NotifyDictionaryChangedEventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Notifies listeners of dynamic changes, such as when items get added and removed or the whole
/// dictionary is refreshed.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE INotifyDictionaryChanged: public Core::Interface
{
    virtual NotifyDictionaryChangedEventHandler& DictionaryChanged() = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(INotifyDictionaryChanged, Core::Interface)
};

}
}


#endif
