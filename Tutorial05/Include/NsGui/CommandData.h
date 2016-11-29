////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMMANDDATA_H__
#define __GUI_COMMANDDATA_H__


#include <Noesis.h>
#include <NsCore/HashMap.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ICommand.h>
#include <NsGui/CommandManager.h>



NS_CFORWARD(Gui, CommandBinding)
NS_CFORWARD(Gui, InputBinding)
NS_CFORWARD(Gui, InputGesture)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::CommandBinding> CommandBindingCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::InputBinding> InputBindingCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// CommandData. Used to register UI commands.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API CommandData: public Core::TypeMetaData
{
public:
    /// Constructor
    CommandData(const Core::TypeClass* ownerType);

    /// Destructor
    ~CommandData();

    /// Registers a routed event for a type
    template<class T>
    const T* RegisterCommand(const Ptr<T>& command);

    /// Finds a command for the owner type given its name
    const ICommand* FindCommand(NsSymbol name) const;

    /// Registers handlers for the specified command
    //@{
    void RegisterCommandHandler(const ICommand* command,
        const ExecutedRoutedEventHandler& executedHandler);
    void RegisterCommandHandler(const ICommand* command,
        const ExecutedRoutedEventHandler& executedHandler, const Ptr<InputGesture>& inputGesture);
    void RegisterCommandHandler(const ICommand* command,
        const ExecutedRoutedEventHandler& executedHandler, const Ptr<InputGesture>& inputGesture1,
        const Ptr<InputGesture>& inputGesture2);
    void RegisterCommandHandler(const ICommand* command,
        const CanExecuteRoutedEventHandler& canExecuteHandler,
        const ExecutedRoutedEventHandler& executedHandler);
    void RegisterCommandHandler(const ICommand* command,
        const CanExecuteRoutedEventHandler& canExecuteHandler,
        const ExecutedRoutedEventHandler& executedHandler, const Ptr<InputGesture>& inputGesture);
    void RegisterCommandHandler(const ICommand* command,
        const CanExecuteRoutedEventHandler& canExecuteHandler,
        const ExecutedRoutedEventHandler& executedHandler, const Ptr<InputGesture>& inputGesture1,
        const Ptr<InputGesture>& inputGesture2);
    //@}

    /// Gets command bindings associated with the owner type
    /// \remarks Returned collection can be null
    const CommandBindingCollection* GetCommandBindings() const;

    /// Gets input bindings associated with the owner type
    /// \remarks Returned collection can be null
    const InputBindingCollection* GetInputBindings() const;

private:
    static void DefaultCanExecute(Core::BaseComponent* sender,
        const CanExecuteRoutedEventArgs& args);

    void InsertCommand(const Ptr<const ICommand>& command);

    void RegisterCommandBinding(const Ptr<CommandBinding>& binding);
    void RegisterInputBinding(const Ptr<InputBinding>& binding);

    void EnsureCommandBindings();
    void EnsureInputBindings();

private:
    const Core::TypeClass* mOwnerType;

    struct Adapter;

    typedef NsHashMap<NsSymbol, Ptr<const ICommand> > CommandMap;
    CommandMap mCommands;

    Ptr<CommandBindingCollection> mCommandBindings;
    Ptr<InputBindingCollection> mInputBindings;

    NS_DECLARE_REFLECTION(CommandData, Core::TypeMetaData)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#include <NsGui/CommandData.inl>


#endif
