////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SELECTOR_H__
#define __GUI_SELECTOR_H__


#include <Noesis.h>
#include <NsGui/ItemsControl.h>
#include <NsGui/RoutedEvent.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
template<class T> class Nullable;
}
namespace Gui
{
struct PathElement;
class PropertyPath;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// SelectionChanged event args
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API SelectionChangedEventArgs: public RoutedEventArgs
{
    typedef NsVector<Ptr<Core::BaseComponent> > ItemList;
    ItemList addedItems;
    ItemList removedItems;

    SelectionChangedEventArgs(Core::BaseComponent* s);
};

typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const SelectionChangedEventArgs&)> 
    SelectionChangedEventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that allows a user to select items from among its child elements. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.selector.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Selector: public ItemsControl
{
public:
    /// Constructor
    Selector();
    
    /// Destructor
    virtual ~Selector() = 0;
    
    /// Gets or sets a value that indicates whether an item is selected.
    //@{
    static NsBool GetIsSelected(DependencyObject* element);
    static void SetIsSelected(DependencyObject* element, NsBool value);
    //@}

    /// Gets a value that indicates whether the keyboard focus is within the value returned by a 
    /// Selector.
    static NsBool GetIsSelectionActive(UIElement* element);

    /// Gets or sets a value that indicates whether a Selector should keep the SelectedItem 
    /// synchronized with the current item in the Items property.
    /// \Remarks
    ///     true if the SelectedItem is always synchronized with the current item in the 
    ///     ItemCollection
    ///     false if the SelectedItem is never synchronized with the current item
    ///     null: if the SelectedItem is synchronized with the current item only if the Selector 
    ///     uses a CollectionView. The default value is null
    //@{
    const Core::Nullable<NsBool>& GetIsSynchronizedWithCurrentItem() const;
    void SetIsSynchronizedWithCurrentItem(const Core::Nullable<NsBool>& value);
    //@}

    /// Gets or sets the index of the first item in the current selection or returns negative one 
    /// (-1) if the selection is empty
    //@{
    NsInt32 GetSelectedIndex() const;
    void SetSelectedIndex(NsInt32 index);
    //@}

    /// Gets or sets the first item in the current selection or returns null if the selection is 
    /// empty
    //@{
    Noesis::Core::BaseComponent* GetSelectedItem() const;
    void SetSelectedItem(Noesis::Core::BaseComponent* item);
    //@}

    /// Gets or sets the value of the SelectedItem, obtained by using SelectedValuePath
    //@{
    Noesis::Core::BaseComponent* GetSelectedValue() const;
    void SetSelectedValue(Noesis::Core::BaseComponent* selectedValue);
    //@}

    /// Gets or sets the path that is used to get the SelectedValue from the SelectedItem
    //@{
    const NsChar* GetSelectedValuePath() const;
    void SetSelectedValuePath(const NsChar* selectedValuePath);
    //@}

    /// Occurs when the selection of a Selector changes
    UIElement::RoutedEvent_<SelectionChangedEventHandler> SelectionChanged();

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* IsSelectedProperty; // Attached
    static const DependencyProperty* IsSelectionActiveProperty; // Attached
    static const DependencyProperty* IsSynchronizedWithCurrentItemProperty;
    static const DependencyProperty* SelectedIndexProperty;
    static const DependencyProperty* SelectedItemProperty;
    static const DependencyProperty* SelectedValueProperty;
    static const DependencyProperty* SelectedValuePathProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* SelectedEvent; // Attached
    static const RoutedEvent* SelectionChangedEvent;
    static const RoutedEvent* UnselectedEvent; // Attached
    //@}

protected:
    /// Called when item containers are generated
    virtual void OnContainersGeneratedOverride(Core::BaseComponent* sender, const EventArgs& e);

    /// Called when the selection changes
    virtual void OnSelectionChanged(const SelectionChangedEventArgs& args);

    /// From ItemsControl
    //@{
    void OnItemsSourceChanged(Core::BaseComponent* oldSource, Core::BaseComponent* newSource);
    void OnCurrentItemChanged();
    void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);
    void ClearContainerForItemOverride(DependencyObject* container,
        Core::BaseComponent* item) const;
    //@}
    
    /// From UIElement
    //@{
    void OnGotFocus(const RoutedEventArgs& e);
    void OnIsKeyboardFocusWithinChanged(const DependencyPropertyChangedEventArgs& e);
    //@}

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    void OnPostInit();
    //@}

    IList* GetInternalSelectedItems() const;

    void InternalSelectAll();
    void InternalUnselectAll();
    void InternalSelectRange(NsInt32 start, NsInt32 end);

    virtual NsBool IsMultiSelectEnabled() const;

protected:
    static const DependencyProperty* InternalSelectedItemsProperty;

    enum
    {
        IsUpdatingSelection = ItemsControl::LastFlag * 2,
        IsSynchronizingCurrent = IsUpdatingSelection * 2,
        IsSelectingItem = IsSynchronizingCurrent * 2,

        LastFlag = IsSelectingItem
    };

private:
    void SynchronizeWithCurrent(NsInt32 currentIndex);
    Core::BaseComponent* SelectItem(Core::BaseComponent* selectedValue);
    void UpdateSelectedValue(Core::BaseComponent* selectedItem);
    void UpdateSelectedIndex(NsInt32 selectedIndex);
    void EnumPath(const PathElement& element, void* context);

    void OnContainersGenerated(Core::BaseComponent* sender, const EventArgs& e);

    void UpdateSingleSelectedList(SelectionChangedEventArgs& e,
        Core::BaseComponent* selectedItem, NsInt32 selectedIndex);
    void UpdateSingleSelectedAndRaiseEvent(const SelectionChangedEventArgs& e,
        NsInt32 selectedIndex);
    void UpdateSingleSelectedAndRaiseEvent(const SelectionChangedEventArgs& e,
        Core::BaseComponent* selectedItem, NsInt32 selectedIndex,
        NsBool raiseSelectionChanged = true);

    void OnItemSelected(SelectionChangedEventArgs& e, Core::BaseComponent* item, NsInt32 index);
    void OnItemUnselected(SelectionChangedEventArgs& e, Core::BaseComponent* item, NsInt32 index);

    void OnSelectedIndexChanged(NsInt32 oldIndex, NsInt32 newIndex);
    void OnSelectedItemChanged(Core::BaseComponent* oldItem, Core::BaseComponent* newItem);

    void OnSelectedItemsChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& e);

    void OnSelectedItemAdded(SelectionChangedEventArgs& args, Core::BaseComponent* item,
        NsInt32 index);
    void OnSelectedItemRemoved(SelectionChangedEventArgs& args, Core::BaseComponent* item,
        NsInt32 index, NsInt32& selectedIndex);

    static NsBool CoerceSelectedIndex(const Gui::DependencyObject* object,
        const void* value, void* coercedValue);

    static NsBool CoerceSelectedItem(const Gui::DependencyObject* object,
        const void* value, void* coercedValue);

    static NsBool CoerceSelectedValue(const Gui::DependencyObject* object,
        const void* value, void* coercedValue);

private:
    friend class ListBoxTest;

    // Used to resolve SelectedValuePath
    Ptr<PropertyPath> mPath;

    // Selected items indices
    NsVector<NsInt32> mSelectedIndices;

    NS_DECLARE_REFLECTION(Selector, ItemsControl)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
