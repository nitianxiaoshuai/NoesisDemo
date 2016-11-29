////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASECOMMAND_H__
#define __GUI_BASECOMMAND_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ICommand.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Delegate.h>
#include <NsCore/Symbol.h>

namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for commands. *Commands* allows you to define actions in one place and then refer to
/// them from all your user interface controls like menu items, toolbar or buttons. Examples of
/// commands are the *Copy*, *Cut*, and *Paste* operations found on many applications. Applications
/// often expose these actions through many mechanisms simultaneously: *MenuItems* in a Menu,
/// *MenuItems* on a ContextMenu, *Buttons* on a ToolBar, *keyboard shortcuts* and so on.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseCommand: public Core::BaseComponent, public ICommand
{
public:
    /// Constructor
    BaseCommand(NsSymbol name = NsSymbol::Null(), const Core::TypeClass* owner = 0);

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~BaseCommand() = 0;

    // From ICommand
    //@{
    Core::Symbol GetName() const;
    const Core::TypeClass* GetOwnerType() const;
    EventHandler& CanExecuteChanged();
    NsBool CanExecute(Core::BaseComponent* param) const;
    void Execute(Core::BaseComponent* param) const;
    //@}

private:
    NsSymbol mName;
    const Core::TypeClass* mOwnerType;

    EventHandler mCanExecuteChanged;

    NS_DECLARE_REFLECTION(BaseCommand, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
