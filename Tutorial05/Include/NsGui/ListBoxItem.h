////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LISTBOXITEM_H__
#define __GUI_LISTBOXITEM_H__


#include <Noesis.h>
#include <NsGui/ContentControl.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
struct MouseButtonEventArgs;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a selectable item in a ListBox. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.listboxitem.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ListBoxItem: public ContentControl
{
public:
    ListBoxItem();

    /// Gets or sets a value that indicates whether a ListBoxItem is selected
    //@{
    NsBool GetIsSelected() const;
    void SetIsSelected(NsBool value);
    //@}

    /// Occurs when a ListBoxItem is selected
    UIElement::RoutedEvent_<RoutedEventHandler> Selected();

    /// Occurs when a ListBoxItem is unselected
    UIElement::RoutedEvent_<RoutedEventHandler> Unselected();

public:
    static const DependencyProperty* IsSelectedProperty;
    
    static const RoutedEvent* SelectedEvent;
    static const RoutedEvent* UnselectedEvent;

protected:
    /// Called when the ListBoxItem is selected in a ListBox
    virtual void OnSelected(const RoutedEventArgs& e);

    /// Called when the ListBoxItem is unselected in a ListBox
    virtual void OnUnselected(const RoutedEventArgs& e);

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnMouseEnter(const MouseEventArgs& e);
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseRightButtonDown(const MouseButtonEventArgs& e);
    void OnGotFocus(const RoutedEventArgs& e);
    void OnKeyDown(const KeyEventArgs& e);
    //@}
    
    /// From Control
    //@{
    void UpdateVisualStates();
    //@}
    
    // Common code for OnMouseLeftButtonDown and OnMouseRightButtonDown
    void OnMouseButtonCommon(const MouseButtonEventArgs& e);
    
    virtual const Core::TypeClass* GetOwnerType() const;

protected:
    NsBool mIsMouseClicked;

    NS_DECLARE_REFLECTION(ListBoxItem, ContentControl)
};

}
}

#endif