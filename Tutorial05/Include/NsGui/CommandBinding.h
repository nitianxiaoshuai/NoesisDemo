////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMMANDBINDING_H__
#define __GUI_COMMANDBINDING_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/CommandManager.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Delegate.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
NS_INTERFACE ICommand;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Binds a RoutedCommand to the event handlers that implement the command.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.input.commandbinding.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API CommandBinding: public Core::BaseComponent
{
public:
    /// Constructor
    CommandBinding();

    /// Constructors for code
    //@{
    CommandBinding(ICommand* command);
    CommandBinding(ICommand* command, const CanExecuteRoutedEventHandler& canExecuteHandler);
    CommandBinding(ICommand* command, const ExecutedRoutedEventHandler& executedHandler);
    CommandBinding(ICommand* command, const CanExecuteRoutedEventHandler& canExecuteHandler,
        const ExecutedRoutedEventHandler& executedHandler);
    //@}

    /// Destructor
    ~CommandBinding();

    /// Gets or sets the ICommand associated with this CommandBinding
    //@{
    ICommand* GetCommand() const;
    void SetCommand(ICommand* command);
    //@}

    /// Occurs when the command associated with this CommandBinding initiates a check to determine 
    /// whether the command can be executed on the current command target
    DelegateEvent_<CanExecuteRoutedEventHandler> PreviewCanExecute();

    /// Occurs when the command associated with this CommandBinding initiates a check to determine
    /// whether the command can be executed on the command target
    DelegateEvent_<CanExecuteRoutedEventHandler> CanExecute();

    /// Occurs when the command associated with this CommandBinding executes
    DelegateEvent_<ExecutedRoutedEventHandler> PreviewExecuted();

    /// Occurs when the command associated with this CommandBinding executes
    DelegateEvent_<ExecutedRoutedEventHandler> Executed();

private:
    friend struct CommandManager;

    /// Raises specified event
    //@{
    void RaisePreviewCanExecute(Core::BaseComponent* sender,
        const CanExecuteRoutedEventArgs& args) const;
    void RaiseCanExecute(Core::BaseComponent* sender, const CanExecuteRoutedEventArgs& args) const;
    void RaisePreviewExecuted(Core::BaseComponent* sender,
        const ExecutedRoutedEventArgs& args) const;
    void RaiseExecuted(Core::BaseComponent* sender, const ExecutedRoutedEventArgs& args) const;
    //@}

    NsBool CheckCanExecute(Core::BaseComponent* sender, const ExecutedRoutedEventArgs& args) const;

private:
    Ptr<ICommand> mCommand;

    CanExecuteRoutedEventHandler mPreviewCanExecute;
    CanExecuteRoutedEventHandler mCanExecute;
    ExecutedRoutedEventHandler mPreviewExecuted;
    ExecutedRoutedEventHandler mExecuted;

    NS_DECLARE_REFLECTION(CommandBinding, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
