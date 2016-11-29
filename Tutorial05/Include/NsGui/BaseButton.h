////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEBUTTON_H__
#define __GUI_BASEBUTTON_H__


#include <Noesis.h>
#include <NsGui/ContentControl.h>
#include <NsGui/ICommandSource.h>
#include <NsGui/Enums.h>


namespace Noesis
{
namespace Gui
{

// Forward declaration
//@{
NS_INTERFACE ICommand;
enum ClickMode;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for all button controls.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.buttonbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseButton: public ContentControl, public ICommandSource
{
public:
    /// Constructor
    BaseButton();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~BaseButton() = 0;

    /// Gets or sets when the Click event occurs
    //@{
    ClickMode GetClickMode() const;
    void SetClickMode(ClickMode mode);
    //@}

    /// Gets or sets the command to invoke when this button is pressed
    //@{
    ICommand* GetCommand() const;
    void SetCommand(ICommand* command);
    //@}

    /// Gets or sets the parameter to pass to the Command property
    //@{
    Core::BaseComponent* GetCommandParameter() const;
    void SetCommandParameter(Core::BaseComponent* param);
    //@}

    /// Gets or sets the element on which to raise the specified command
    //@{
    UIElement* GetCommandTarget() const;
    void SetCommandTarget(UIElement* target);
    //@}

    /// Gets a value that indicates whether a button is currently activated
    NsBool GetIsPressed() const;

    /// Occurs when a Button is clicked
    UIElement::RoutedEvent_<RoutedEventHandler> Click();

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ClickModeProperty;
    static const DependencyProperty* CommandProperty;
    static const DependencyProperty* CommandParameterProperty;
    static const DependencyProperty* CommandTargetProperty;
    static const DependencyProperty* IsPressedProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* ClickEvent;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    NsBool IsEnabledCore() const;
    void OnKeyDown(const KeyEventArgs& e);
    void OnKeyUp(const KeyEventArgs& e);
    void OnLostKeyboardFocus(const KeyboardFocusChangedEventArgs& e);
    void OnLostMouseCapture(const MouseEventArgs& e);
    void OnMouseEnter(const MouseEventArgs& e);
    void OnMouseLeave(const MouseEventArgs& e);
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e);
    void OnMouseMove(const MouseEventArgs& e);
    //@}
    
    /// From Control
    //@{
    void UpdateVisualStates();
    //@}

    /// Event handlers
    //@{
    virtual void OnClick();
    virtual void OnIsPressedChanged(const DependencyPropertyChangedEventArgs& e);
    //@}

private:
    /// Base classes are non-copyable objects
    //@{
    BaseButton(const BaseButton&);
    BaseButton& operator=(const BaseButton&);
    //@}

private:
    /// Controls if the Space key has been pressed
    NsBool mSpaceKeydown;
    
    /// Controls if the left mouse button is down
    NsBool mLeftButtonDown;

    /// Mantains the CanExecute state
    NsBool mCanExecute;

    NS_DECLARE_REFLECTION(BaseButton, ContentControl)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
