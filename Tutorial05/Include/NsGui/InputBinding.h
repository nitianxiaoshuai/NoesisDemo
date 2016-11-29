////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INPUTBINDING_H__
#define __GUI_INPUTBINDING_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Freezable.h>
#include <NsGui/ICommandSource.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
NS_INTERFACE ICommand;
class UIElement;
class InputGesture;
class DependencyProperty;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a binding between an InputGesture and a command.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.input.inputbinding.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API InputBinding: public Freezable, public ICommandSource, public IUITreeNode
{
public:
    /// Constructor
    InputBinding();

    /// Constructor for code
    InputBinding(ICommand* command, InputGesture* gesture);

    /// Destructor
    ~InputBinding();

    /// Gets or sets the ICommand associated with this InputBinding
    //@{
    ICommand* GetCommand() const;
    void SetCommand(ICommand* command);
    //@}

    /// Gets or sets the command-specific data for a particular command
    //@{
    Core::BaseComponent* GetCommandParameter() const;
    void SetCommandParameter(Core::BaseComponent* param);
    //@}

    /// Gets or sets the target element of the command
    //@{
    UIElement* GetCommandTarget() const;
    void SetCommandTarget(UIElement* target);
    //@}

    /// Gets or sets the InputGesture associated with this input binding
    //@{
    InputGesture* GetGesture() const;
    void SetGesture(InputGesture* gesture);
    //@}

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* CommandProperty;
    static const DependencyProperty* CommandParameterProperty;
    static const DependencyProperty* CommandTargetProperty;
    //@}

protected:
    /// Used by inheritors to manage command property changes
    virtual void OnCommandChanged(ICommand* oldCommand, ICommand* newCommand);

    /// Used by inheritors to manage gesture property changes
    virtual void OnGestureChanged(InputGesture* oldGesture, InputGesture* newGesture);

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Freezable
    //@{
    void CloneCommonCore(const Freezable* source);
    //@}

private:
    IUITreeNode* mOwner;
    Ptr<InputGesture> mGesture;

    NS_DECLARE_REFLECTION(InputBinding, Freezable)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
