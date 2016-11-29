////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ICOMMAND_H__
#define __GUI_ICOMMAND_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsGui/Events.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Core
{
class BaseComponent;
class Symbol;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a command
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE ICommand: public Core::Interface
{
    /// Gets the name of the command as it is registered in the CommandManager
    /// \prop
    virtual Core::Symbol GetName() const = 0;

    /// Gets the class type of the object that defines the command
    /// \prop
    virtual const Core::TypeClass* GetOwnerType() const = 0;

    /// Occurs when changes occur that affect whether or not the command should execute
    virtual EventHandler& CanExecuteChanged() = 0;

    /// Determines whether the command can execute in its current state
    virtual NsBool CanExecute(Core::BaseComponent* param) const = 0;

    /// This method is called when command is invoked
    virtual void Execute(Core::BaseComponent* param) const = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(ICommand, Core::Interface)
};

}
}


#endif
