////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CHANGEDHANDLER_H__
#define __GUI_CHANGEDHANDLER_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/FreezableEventReason.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class Freezable;
class DependencyObject;
class DependencyProperty;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ChangedHandler. Handlers are created to check changes of objects stored inside a dependency
/// property (a freezable object or an expression object).
////////////////////////////////////////////////////////////////////////////////////////////////////
class ChangedHandler
{
public:
    /// Constructor
    ChangedHandler();

    /// Destructor
    ~ChangedHandler();

    /// Connects this handler to the specified freezable
    void Attach(Freezable* object, DependencyObject* owner, const DependencyProperty* ownerProp);

    /// Disconnects this handler from the freezable
    void Detach();

    /// Gets object where this handler is attached
    Freezable* GetFreezable() const;

private:
    /// Callback function for object changes
    void OnChanged(Freezable* freezable, FreezableEventReason reason);

private:
    Freezable* mFreezable;
    DependencyObject* mOwner;
    const DependencyProperty* mOwnerProperty;
};


}
}

#endif
