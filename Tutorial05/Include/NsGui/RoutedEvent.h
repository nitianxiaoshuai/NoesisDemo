////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ROUTEDEVENT_H__
#define __GUI_ROUTEDEVENT_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/Symbol.h>
#include <NsGui/Events.h>
#include <NsCore/CompilerTools.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
template<class T> class Delegate;
}
namespace Gui
{
class RoutedEventSerializer;
}
//@}

namespace Gui
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// RoutingStrategy. Defines the routing strategy of the dependency event.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum RoutingStrategy
{
    /// Event is routed to the root of the element tree
    RoutingStrategy_Bubbling,

    /// Event is routed to children elements of the tree
    RoutingStrategy_Tunneling,

    /// Event is routed directly to a specific element in the tree
    RoutingStrategy_Direct
};


#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// RoutedEvent. An event instance that propagates through a tree of related elements. There are
/// three types of routing: bubbling, tunneling and direct. With bubbling, the event instance moves
/// from the source of the event up to the top of the tree. With tunneling, the event instance
/// starts at the top of the tree and moves down to the source of the event. With direct routing,
/// the event instance behaves like a standard event.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RoutedEvent: public Core::BaseComponent
{
public:
    RoutedEvent(NsSymbol name);
    RoutedEvent(NsSymbol name, const Core::TypeClass* ownerType, RoutingStrategy routingStrategy);
    ~RoutedEvent();

    /// Gets event name
    inline NsSymbol GetName() const;

    /// Gets or sets event owner type
    //@{
    inline const Core::TypeClass* GetOwnerType() const;
    void SetOwnerType(const Core::TypeClass* owner);
    //@}

    /// Gets or sets event routing strategy
    //@{
    inline RoutingStrategy GetRoutingStrategy() const;
    void SetRoutingStrategy(RoutingStrategy strategy);
    //@}
    
    /// Gets the event helper serializer
    RoutedEventSerializer* GetSerializer() const;

private:
    NsSymbol mName;
    const Core::TypeClass* mOwnerType;
    RoutingStrategy mRoutingStrategy;
    mutable Ptr<RoutedEventSerializer> mSerializer;

    NS_DECLARE_REFLECTION(RoutedEvent, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Contains state information and event arguments associated with a routed event.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API RoutedEventArgs: public EventArgs
{
public:
    Core::BaseComponent* source;
    const RoutedEvent* routedEvent;
    mutable NsBool handled;

    /// Constructor
    RoutedEventArgs(Core::BaseComponent* s, const RoutedEvent* e);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the delegate for handlers that receive dependency events.
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const RoutedEventArgs&)>
    RoutedEventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// RoutedPropertyChangedEventArgs
// TODO [srodriguez] WPF implementation is templatized. We must decide if this is necessary
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct RoutedPropertyChangedEventArgs: public RoutedEventArgs
{
    T oldValue;
    T newValue;

    RoutedPropertyChangedEventArgs(Core::BaseComponent* s, const RoutedEvent* e, 
        typename Core::Param<T>::Type oldV, typename Core::Param<T>::Type newV): 
        RoutedEventArgs(s, e), oldValue(oldV), newValue(newV)
    {
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct RoutedPropertyChangedEventHandler
{
    typedef Core::Delegate<void (Core::BaseComponent*, const RoutedPropertyChangedEventArgs<T>&)>
        Handler;
};

}
}

#include <NsGui/RoutedEvent.inl>


#endif
