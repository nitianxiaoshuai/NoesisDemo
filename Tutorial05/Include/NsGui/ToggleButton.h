////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TOGGLEBUTTON_H__
#define __GUI_TOGGLEBUTTON_H__


#include <Noesis.h>
#include <NsGui/BaseButton.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{
namespace Core
{
// Forward declarations
//@{
template<class T> class Nullable;
//@}
}
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for button controls that can switch states.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.togglebutton.aspx#inheritanceContinued
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ToggleButton: public BaseButton
{
public:
    /// Constructor
    ToggleButton();

    /// Gets or sets whether the ToggleButton is checked.
    //@{
    const Core::Nullable<NsBool>& GetIsChecked() const;
    void SetIsChecked(const Core::Nullable<NsBool>& checked);
    //@}

    /// Determines whether the control supports two or three states
    //@{
    NsBool GetIsThreeState() const;
    void SetIsThreeState(NsBool state);
    //@}
    
    // Events
    //@{
    /// Occurs when a ToggleButton is checked.
    UIElement::RoutedEvent_<RoutedEventHandler> Checked();
    /// Occurs when the state of a ToggleButton is neither on nor off.
    UIElement::RoutedEvent_<RoutedEventHandler> Indeterminate();
    /// Occurs when a ToggleButton is unchecked.
    UIElement::RoutedEvent_<RoutedEventHandler> Unchecked();
    //@}
    
protected:
    
    /// Called when a ToggleButton raises a Checked event.
    virtual void OnChecked(const RoutedEventArgs& e);

    /// Called when a ToggleButton raises an Indeterminate event.
    virtual void OnIndeterminate(const RoutedEventArgs& e);
    
    /// Called by the OnClick() method to implement toggle behavior.
    virtual void OnToggle();
    
    /// Called when a ToggleButton raises an Unchecked event.
    virtual void OnUnchecked(const RoutedEventArgs& e);
    
    /// From BaseButton
    //@{
    void OnClick();
    //@}
    
    /// From Control
    //@{
    void UpdateVisualStates();
    //@}
    
    /// From UIElement
    //@{
    //protected override AutomationPeer OnCreateAutomationPeer();
    //@}
    
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    /// Base classes are non-copyable objects
    //@{
    ToggleButton(const ToggleButton&);
    ToggleButton& operator=(const ToggleButton&);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* IsCheckedProperty;
    static const DependencyProperty* IsThreeStateProperty;
    //@}

    /// Dependency events
    //@{
    static const RoutedEvent* CheckedEvent;
    static const RoutedEvent* IndeterminateEvent;
    static const RoutedEvent* UncheckedEvent;
    //@}

private:
    NS_DECLARE_REFLECTION(ToggleButton, BaseButton)
};

}
}

#endif
