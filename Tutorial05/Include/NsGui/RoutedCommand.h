////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ROUTEDCOMMAND_H__
#define __GUI_ROUTEDCOMMAND_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ICommand.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Delegate.h>
#include <NsCore/Symbol.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
class ConfigValueList;
}
namespace Gui
{
class InputGesture;
class KeyGestureConverter;
class UIElement;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::InputGesture> InputGestureCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A command that is routed through the element tree.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.input.routedcommand.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RoutedCommand: public Core::BaseComponent, public ICommand
{
public:
    /// Constructor
    RoutedCommand(NsSymbol name, const Core::TypeClass* owner,
        InputGestureCollection* inputGestures);

    /// Destructor
    ~RoutedCommand();

    // Creates a routed command
    //@{
    static Ptr<RoutedCommand> Create(const NsChar* name, const Core::TypeClass* owner);
    static Ptr<RoutedCommand> Create(const NsChar* name, const Core::TypeClass* owner,
        InputGesture* inputGesture);
    static Ptr<RoutedCommand> Create(const NsChar* name, const Core::TypeClass* owner,
        InputGesture* inputGesture1, InputGesture* inputGesture2);
    //@}

    /// Gets the collection of InputGesture objects that are associated with this command
    InputGestureCollection* GetInputGestures() const;

    /// Determines whether this RoutedCommand can execute in its current state
    NsBool CanExecute(Core::BaseComponent* param, UIElement* target) const;

    /// Executes the RoutedCommand on the current command target
    void Execute(Core::BaseComponent* param, UIElement* target) const;

    /// From ICommand
    //@{
    NsSymbol GetName() const;
    const Core::TypeClass* GetOwnerType() const;
    EventHandler& CanExecuteChanged();
    NsBool CanExecute(Core::BaseComponent* param) const;
    void Execute(Core::BaseComponent* param) const;
    //@}

protected:
    static Ptr<InputGestureCollection> CreateInputGestures(InputGesture* inputGesture1,
        InputGesture* inputGesture2);

private:
    friend struct CommandManager;
    NsBool CanExecute(Core::BaseComponent* param, UIElement* target,
        NsBool& continueRouting) const;

private:
    NsSymbol mName;
    const Core::TypeClass* mOwnerType;

    EventHandler mCanExecuteChanged;

    Ptr<InputGestureCollection> mInputGestures;

    NS_DECLARE_REFLECTION(RoutedCommand, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
