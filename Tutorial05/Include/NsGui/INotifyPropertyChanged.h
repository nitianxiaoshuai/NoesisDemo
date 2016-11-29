////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INOTIFYPROPERTYCHANGED_H__
#define __GUI_INOTIFYPROPERTYCHANGED_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Events.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Core
{
template<class T> class Delegate;
template<class T> class Ptr;
class BaseComponent;
class Symbol;
}
namespace Gui
{
NS_INTERFACE INotifyPropertyChanged;
}
using Core::Ptr;
//@}

namespace Gui
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// Contains state information for the PropertyChanged event.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct PropertyChangedEventArgs: public EventArgs
{
    NsSymbol propertyName;

    PropertyChangedEventArgs(NsSymbol name): propertyName(name) { }

    NS_IMPLEMENT_INLINE_REFLECTION_(PropertyChangedEventArgs, EventArgs)
};

typedef Core::Delegate<void (Core::BaseComponent*, const PropertyChangedEventArgs&)>
    PropertyChangedEventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Notifies clients that a property value has changed.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE INotifyPropertyChanged: public Core::Interface
{
    /// Occurs when a property value changes
    //@{
    virtual PropertyChangedEventHandler& PropertyChanged() = 0;
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION_(INotifyPropertyChanged, Core::Interface)
};

}
}

#endif