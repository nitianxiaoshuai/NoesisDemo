////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TREEVIEWITEM_H__
#define __GUI_TREEVIEWITEM_H__


#include <Noesis.h>
#include <NsGui/HeaderedItemsControl.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class ToggleButton;
class TreeView;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements a selectable item in a TreeView control.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.treeviewitem.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TreeViewItem: public HeaderedItemsControl
{
public:
    TreeViewItem();
    ~TreeViewItem();
    
    /// Gets or sets whether the nested items in a TreeViewItem are expanded or collapsed
    //@{
    NsBool GetIsExpanded() const;
    void SetIsExpanded(NsBool value);
    //@}
    
    /// Gets or sets whether a TreeViewItem control is selected.
    //@{
    NsBool GetIsSelected() const;
    void SetIsSelected(NsBool value);
    //@}
    
    /// Gets or sets whether a TreeViewItem control is selected.
    //@{
    NsBool GetIsSelectionActive() const;
    void SetIsSelectionActive(NsBool value);
    //@}

    // Events
    //@{
    /// Occurs when the IsExpanded property changes from true to false.
    UIElement::RoutedEvent_<RoutedEventHandler> Collapsed();

    /// Occurs when the IsExpanded property changes from false to true.
    UIElement::RoutedEvent_<RoutedEventHandler> Expanded();

    /// Occurs when the IsSelected property of a TreeViewItem changes from false to true.
    UIElement::RoutedEvent_<RoutedEventHandler> Selected();

    /// Occurs when the IsSelected property of a TreeViewItem changes from true to false.
    UIElement::RoutedEvent_<RoutedEventHandler> Unselected();
    //@}

public:
    static const DependencyProperty* IsExpandedProperty;
    static const DependencyProperty* IsSelectedProperty;
    static const DependencyProperty* IsSelectionActiveProperty;
    
    static const RoutedEvent* CollapsedEvent;
    static const RoutedEvent* ExpandedEvent;
    static const RoutedEvent* SelectedEvent;
    static const RoutedEvent* UnselectedEvent;
    
protected:
    virtual void OnCollapsed(const RoutedEventArgs& e);
    virtual void OnExpanded(const RoutedEventArgs& e);
    virtual void OnSelected(const RoutedEventArgs& e);
    virtual void OnUnselected(const RoutedEventArgs& e);

    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    NsBool IsItemItsOwnContainerOverride(BaseComponent* item) const;
    void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);
    //@}

    /// From Control
    //@{
    void UpdateVisualStates();
    void OnMouseDoubleClick(const MouseButtonEventArgs& e);
    //@}
    
    /// From UIElement
    //@{
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnGotFocus(const RoutedEventArgs& e);
    //@}
    
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    void OnButtonClick(Core::BaseComponent* sender, const RoutedEventArgs& e);
    TreeView* GetSourceTreeView() const;

    NS_DECLARE_REFLECTION(TreeViewItem, HeaderedItemsControl)
};

}
}

#endif
