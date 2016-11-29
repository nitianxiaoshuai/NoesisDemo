////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMMANDMANAGER_H__
#define __GUI_COMMANDMANAGER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/RoutedEvent.h>
#include <NsCore/ReflectionDeclare.h>


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
NS_INTERFACE ICommand;
class UIElement;
struct KeyEventArgs;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the CanExecute and PreviewCanExecute routed events.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API CanExecuteRoutedEventArgs: public RoutedEventArgs
{
    /// The command associated with this event
    const ICommand* command;

    /// The command specific data
    Ptr<Core::BaseComponent> parameter;

    /// Indicates whether the RoutedCommand associated with this event can be executed on the target
    mutable NsBool canExecute;

    /// Determines whether the input routed event that invoked the command should continue to route
    /// through the element tree
    mutable NsBool continueRouting;

    /// Constructor
    CanExecuteRoutedEventArgs(Core::BaseComponent* s, const RoutedEvent* e, const ICommand* c,
        Core::BaseComponent* p);

    /// Destructor
    ~CanExecuteRoutedEventArgs();
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const CanExecuteRoutedEventArgs&)>
    CanExecuteRoutedEventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the Executed and PreviewExecuted routed events.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ExecutedRoutedEventArgs: public RoutedEventArgs
{
    /// The command associated with this event
    const ICommand* command;

    /// The command specific data
    Ptr<Core::BaseComponent> parameter;

    /// Constructor
    ExecutedRoutedEventArgs(Core::BaseComponent* s, const RoutedEvent* e, const ICommand* c,
        Core::BaseComponent* p);

    /// Destructor
    ~ExecutedRoutedEventArgs();
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const ExecutedRoutedEventArgs&)>
    ExecutedRoutedEventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a command that implements ICommand and is routed through the element tree.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API CommandManager
{
    /// Attached events
    //@{
    static const RoutedEvent* PreviewCanExecuteEvent;
    static const RoutedEvent* CanExecuteEvent;
    static const RoutedEvent* PreviewExecutedEvent;
    static const RoutedEvent* ExecutedEvent;
    //@}

    /// Process keyboard input (for internal use only)
    static void ProcessKeyboardInput(UIElement* target, const KeyEventArgs& args);

private:
    static void ExecuteCommand(const ICommand* command, Core::BaseComponent* param,
        UIElement* target, const KeyEventArgs& args);

    static void StaticOnPreviewCanExecute(Core::BaseComponent* obj, const EventArgs& e);
    static void StaticOnCanExecute(Core::BaseComponent* obj, const EventArgs& e);
    static void StaticOnPreviewExecuted(Core::BaseComponent* obj, const EventArgs& e);
    static void StaticOnExecuted(Core::BaseComponent* obj, const EventArgs& e);

    NS_DECLARE_REFLECTION(CommandManager, Core::NoParent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
