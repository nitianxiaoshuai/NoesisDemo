////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TREEVIEW_H__
#define __GUI_TREEVIEW_H__


#include <Noesis.h>
#include <NsGui/ItemsControl.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class TreeViewItem;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that displays hierarchical data in a tree structure that has items that
/// can expand and collapse.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.treeview.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TreeView: public ItemsControl
{
public:
    /// Constructor
    TreeView();

    /// Destructor
    ~TreeView();

    /// Gets the selected item in a TreeView
    Core::BaseComponent* GetSelectedItem() const;

    /// Occurs when a new item is selected in the tree
    UIElement::RoutedEvent_<RoutedPropertyChangedEventHandler<Ptr<BaseComponent> >::Handler>
        SelectedItemChanged();

    /// Used by TreeViewItem implementation
    //@{
    void ItemClicked(TreeViewItem* tvi);
    void ItemExpanded(TreeViewItem* tvi);
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* SelectedItemProperty;
    //@}

    // Routed Events
    //@{
    /// Occurs when the SelectedItem changes.
    static const RoutedEvent* SelectedItemChangedEvent;
    //@}

protected:
    virtual void OnSelectedItemChanged(
        const RoutedPropertyChangedEventArgs<Ptr<BaseComponent> >& e);

    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;
    void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);
    //@}
    
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    Ptr<TreeViewItem> mSelectedContainer;
    
    NS_DECLARE_REFLECTION(TreeView, ItemsControl)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif