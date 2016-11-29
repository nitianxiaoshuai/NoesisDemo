////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_EVENTS_H__
#define __GUI_EVENTS_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Core
{
class BaseComponent;
template<class T> class Delegate;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// EventArgs is the base class for classes containing event data.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API EventArgs
{
    /// Default empty event args
    static const EventArgs Empty;

    NS_DECLARE_REFLECTION(EventArgs, Core::NoParent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the delegate for handlers that receive normal events.
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const EventArgs&)> EventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Wrapper for events based on a delegate
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct DelegateEvent_
{
    /// Constructor
    DelegateEvent_(T& delegate): _delegate(delegate) { }
    DelegateEvent_& operator=(const DelegateEvent_& other)
    {
        _delegate = other._delegate;
        return *this;
    }

    /// Adds a handler to the delegate event
    void operator+=(const T& handler) { _delegate += handler; }

    /// Removes a handler from the delegate event
    void operator-=(const T& handler) { _delegate -= handler; }

private:
    T& _delegate;
};

}
}


#endif
