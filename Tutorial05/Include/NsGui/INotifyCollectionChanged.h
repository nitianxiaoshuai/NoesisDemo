////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASECOLLECTION_H__
#define __GUI_BASECOLLECTION_H__


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
//@}

namespace Gui
{

enum NotifyCollectionChangedAction
{
    /// One item was added to the collection
    NotifyCollectionChangedAction_Add,
    /// One item was removed from the collection
    NotifyCollectionChangedAction_Remove,
    /// One item was replaced in the collection
    NotifyCollectionChangedAction_Replace,
    // One items was moved within the collection
    NotifyCollectionChangedAction_Move,
    /// The content of the collection changed dramatically
    NotifyCollectionChangedAction_Reset,
    NotifyCollectionChangedAction_PreReset
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Args passed on collection changed event notification.
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

struct NS_GUI_CORE_API NotifyCollectionChangedEventArgs
{
public:
    NotifyCollectionChangedAction action;
    NsSize oldIndex;
    NsSize newIndex;
    Core::BaseComponent* oldValue;
    Core::BaseComponent* newValue;

    /// Constructor
    NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction a,
        NsSize oldIdx, NsSize newIdx, Core::BaseComponent* oldVal, Core::BaseComponent* newVal);

private:
    NS_DECLARE_REFLECTION(NotifyCollectionChangedEventArgs, Core::NoParent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Core::Delegate<void (Core::BaseComponent*, const NotifyCollectionChangedEventArgs&)>
    NotifyCollectionChangedEventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Notifies listeners of dynamic changes, such as when items get added and removed or the whole
/// list is refreshed.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE INotifyCollectionChanged: public Core::Interface
{
    virtual NotifyCollectionChangedEventHandler& CollectionChanged() = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(INotifyCollectionChanged, Core::Interface)
};

}
}


#endif
