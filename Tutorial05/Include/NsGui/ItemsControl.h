////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ITEMSCONTROL_H__
#define __GUI_ITEMSCONTROL_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Control.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
NS_INTERFACE IList;
class BaseCollection;
class DataTemplate;
class ItemContainerGenerator;
class ItemsPanelTemplate;
class ItemCollection;
class ItemsPresenter;
class Panel;
class ResourceKeyString;
class ContentControl;
struct NotifyCollectionChangedEventArgs;
NS_INTERFACE INotifyCollectionChanged;
//@}

// Placeholders to be implemented
//@{
class DataTemplateSelector;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that can be used to present a collection of items.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.itemscontrol.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ItemsControl: public Control
{
public:
    /// Constructor
    ItemsControl();
    
    /// Destructor
    ~ItemsControl();

    /// Gets or sets a path to a value on the source object to serve as the visual representation 
    /// of the object
    //@{
    const NsChar* GetDisplayMemberPath() const;
    void SetDisplayMemberPath(const NsChar* path);
    //@}
    
    /// Gets a value that indicates whether the ItemsControl contains items
    NsBool GetHasItems() const;

    /// Gets the ItemContainerGenerator associated with this control
    ItemContainerGenerator* GetItemContainerGenerator() const;

    /// Gets or sets the Style that is applied to the container element generated for each item. 
    //@{
    Style* GetItemContainerStyle() const;
    void SetItemContainerStyle(Style* style);
    //@}

    /// Gets or sets the template that defines the panel that controls the layout of items
    //@{
    ItemsPanelTemplate* GetItemsPanel() const;
    void SetItemsPanel(ItemsPanelTemplate* value);
    //@}

    /// Returns a new instance of the default items panel for this ItemsControl
    virtual Ptr<Panel> GetDefaultItemsPanel() const;

    /// Gets or sets a collection used to generate the content of the ItemsControl. When the
    /// ItemsSource property is set, the Items collection is made read-only and fixed-size
    //@{
    Core::BaseComponent* GetItemsSource() const;
    void SetItemsSource(Core::BaseComponent* items);
    //@}
    
    /// Gets or sets the DataTemplate used to display each item.
    //@{
    DataTemplate* GetItemTemplate() const;
    void SetItemTemplate(DataTemplate* value);
    //@}
    
    /// Gets or sets the custom logic for choosing a template used to display each item.
    //@{
    DataTemplateSelector* GetItemTemplateSelector() const;
    void SetItemTemplateSelector(DataTemplateSelector* selector);
    //@}

    /// Gets the collection used to generate the content of the ItemsControl. When the ItemsSource
    /// property is set, the Items collection is made read-only and fixed-size
    ItemCollection* GetItems() const;

    /// Returns the ItemsControl that owns the specified container element.
    static ItemsControl* ItemsControlFromItemContainer(DependencyObject* container);

    /// Return the container that owns the given element. If itemsControl is not null, return a
    /// container that belongs to the given ItemsControl. If itemsControl is null, return the
    /// closest container belonging to any ItemsControl. Return null if no such container exists
    static DependencyObject* ContainerFromElement(ItemsControl* itemsControl,
        DependencyObject* element);

    /// Return the container belonging to the current ItemsControl that owns the given container
    /// element. Return null if no such container exists
    DependencyObject* ContainerFromElement(DependencyObject* element);

    /// Returns the ItemsControl that the specified element hosts items for. If IsItemsHost is set 
    /// to true on element in a style or if element is a panel created by the ItemsPresenter for an 
    /// ItemsControl, the ItemsControl is returned; otherwise, a null reference
    static ItemsControl* GetItemsOwner(DependencyObject* itemsHost);

    /// Determines if the specified item is (or is eligible to be) its own container
    NsBool IsItemItsOwnContainer(Core::BaseComponent* item) const;

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* DisplayMemberPathProperty;
    static const DependencyProperty* HasItemsProperty;
    static const DependencyProperty* ItemContainerStyleProperty;
    static const DependencyProperty* ItemsPanelProperty;
    static const DependencyProperty* ItemsSourceProperty;
    static const DependencyProperty* ItemTemplateProperty;
    static const DependencyProperty* ItemTemplateSelectorProperty;
    //@}
    
protected:
    /// Gets the panel which is marked by the template to visually host the items
    Panel* GetItemsHost() const;

    /// Creates or identifies the element that is used to display the given item.
    virtual Ptr<DependencyObject> GetContainerForItemOverride() const;

    /// Determines if the specified item is (or is eligible to be) its own container.
    virtual NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;

    /// Configures container
    virtual void PrepareContainerForItemOverride(DependencyObject* container,
        Core::BaseComponent* item) const;

    /// Clears container attachments
    virtual void ClearContainerForItemOverride(DependencyObject* container,
        Core::BaseComponent* item) const;

    /// Applies the appropriate style to item container
    virtual void ApplyItemContainerStyle(DependencyObject* container) const;
    static void OverrideContainerStyle(DependencyObject* container, ResourceKeyString* key);

    /// Invoked when the Items property changes
    virtual void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);

    /// Invoked when the current item changes
    virtual void OnCurrentItemChanged();

    /// Invoked when Item template changes
    virtual void OnItemTemplateChanged(DataTemplate* oldTemplate, DataTemplate* newTemplate);

    /// Invoked when Item template selector changes
    virtual void OnItemTemplateSelectorChanged(DataTemplateSelector* oldSelector,
        DataTemplateSelector* newSelector);

    /// Tries to bring item into view
    void BringIntoView(Core::BaseComponent* item);

    /// From DependencyObject
    //@{
    void OnInit();
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    //@}

    /// Called when ItemsSource has changed
    virtual void OnItemsSourceChanged(Core::BaseComponent* oldSource,
        Core::BaseComponent* newSource);

    // ItemsControl flag management
    //@{
    void SetItemsFlag(NsUInt32 flag);
    void ClearItemsFlag(NsUInt32 flag);
    NsBool CheckItemsFlag(NsUInt32 flag) const;

    struct ScopeItemsFlag
    {
        ScopeItemsFlag(ItemsControl* ic, NsUInt32 f);
        ~ScopeItemsFlag();
    private:
        ItemsControl* itemsControl;
        NsUInt32 flag;
    };

    enum
    {
        UsesExternalCollectionView = 1,
        RemovingExternalCollectionView = UsesExternalCollectionView * 2,
        NeedsRefreshItems = RemovingExternalCollectionView * 2,

        LastFlag = NeedsRefreshItems
    };
    //@}

    void PrepareContainer(Core::BaseComponent* item, ItemsControl* parent);

private:
    friend class ItemContainerGenerator;
    friend class ItemsControlTest;
    friend class ItemCollection;
    friend class ItemsPresenter;
    friend class Panel;
    friend class VirtualizingPanel;

    // ItemContainerGenerator host interface
    //@{
    Ptr<DependencyObject> GetContainerForItem(Core::BaseComponent* item) const;
    void PrepareItemContainer(DependencyObject* container, Core::BaseComponent* item) const;
    void ClearContainerForItem(DependencyObject* container, Core::BaseComponent* item) const;
    NsBool IsHostForItemContainer(DependencyObject* container) const;
    //@}

    static NsBool IsContainerForItemsControl(DependencyObject* element,
        ItemsControl* itemsControl);

    void OnCollectionViewSourceChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);
    void OnItemsChangedInternal(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);
    void OnCurrentItemChangedInternal(Core::BaseComponent* c, const EventArgs& args);

    // Allows ItemsPresenter to update items presenter
    void SetItemsPresenter(ItemsPresenter* itemsPresenter);

    // Allows Panel to update items host
    void SetItemsHost(Panel* itemsHost);

    void EnsureItems();
    void ConnectItems();
    void DisconnectItems();

    void InvalidateItemsPresenter();
    void InvalidateItems();
    void RefreshItems();

    void CheckTemplateProperties();

private:
    Ptr<ItemCollection> mItems;
    Ptr<ItemContainerGenerator> mGenerator;
    Ptr<ItemsPresenter> mItemsPresenter;
    Ptr<Panel> mItemsHost;
    Ptr<DataTemplate> mDisplayMemberTemplate;

    NsUInt32 mItemsFlags;

    NS_DECLARE_REFLECTION(ItemsControl, Control)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
