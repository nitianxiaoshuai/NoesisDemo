////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FRAMEWORKELEMENT_H__
#define __GUI_FRAMEWORKELEMENT_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/DelegateForward.h>
#include <NsGui/UIElement.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/INameScope.h>
#include <NsGui/Style.h>
#include <NsGui/Enums.h>


NS_SFORWARD(Drawing, Size)
NS_SFORWARD(Drawing, Thickness)
NS_CFORWARD(Gui, ContextMenu)
NS_CFORWARD(Gui, NameScope)
NS_CFORWARD(Gui, FocusVisualLayer)
NS_CFORWARD(Gui, EventTrigger)
NS_CFORWARD(Gui, ResourceDictionary)
NS_CFORWARD(Gui, BaseDictionary)
NS_CFORWARD(Gui, TriggerCollection)
NS_CFORWARD(Gui, ElementProvider)
NS_CFORWARD(Gui, BaseBinding)
NS_CFORWARD(Gui, BaseBindingExpression)
NS_CFORWARD(Gui, BindingExpression)
NS_CFORWARD(Gui, ResourceKeyType)
NS_CFORWARD(Gui, FrameworkTemplate)
NS_CFORWARD(Gui, DataTemplate)
NS_CFORWARD(Gui, TemplateLocalValueProvider)
NS_CFORWARD(Gui, DelayedStaticResources)
NS_SFORWARD(Gui, ContextMenuEventArgs)
NS_SFORWARD(Gui, RequestBringIntoViewEventArgs)
NS_SFORWARD(Gui, SizeChangedEventArgs)
NS_SFORWARD(Gui, ToolTipEventArgs)
NS_SFORWARD(Gui, NotifyDictionaryChangedEventArgs)
NS_IFORWARD(Gui, ITimeManager)
NS_IFORWARD(Gui, IView)


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
struct TimeManagerRef: public Core::BaseComponent
{
    Ptr<ITimeManager> timeManager;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum AncestorNameScopeChangeAction
{
    AncestorNameScopeChangeAction_Attach,
    AncestorNameScopeChangeAction_Detach,
    AncestorNameScopeChangeAction_Change
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct AncestorNameScopeChangedArgs
{
    AncestorNameScopeChangeAction action;
    INameScope* nameScope;
    NameScopeChangedArgs changeArgs;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Delegate<void (FrameworkElement*)> AncestorChangedDelegate;
typedef Noesis::Core::Delegate<void(Core::BaseComponent*, const NotifyDictionaryChangedEventArgs&)>
    AncestorResourcesChangedDelegate;
typedef Noesis::Core::Delegate<void (FrameworkElement*, const AncestorNameScopeChangedArgs&)>
    AncestorNameScopeChangedDelegate;
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const ContextMenuEventArgs&)> 
    ContextMenuEventHandler;
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const RequestBringIntoViewEventArgs&)>
    RequestBringIntoViewEventHandler;
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const SizeChangedEventArgs&)> 
    SizeChangedEventHandler;
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const ToolTipEventArgs&)> 
    ToolTipEventHandler;


#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#ifdef FindResource
#undef FindResource
#endif
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides GUI framework-level features for user interface elements.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.frameworkelement.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FrameworkElement: public UIElement, public IUITreeNode
{
public:
    /// Constructor
    FrameworkElement();

    /// Destructor
    ~FrameworkElement();

    // Property accessors
    //@{

    /// Gets the rendered height of this element.
    NsFloat32 GetActualHeight() const;

    /// Gets the rendered width of this element.
    NsFloat32 GetActualWidth() const;

    /// Gets or sets the context menu element that should appear whenever the context menu is 
    /// requested through user interface (UI) from within this element.
    //@{
    ContextMenu* GetContextMenu() const;
    void SetContextMenu(ContextMenu* menu);
    //@}

    /// Gets or sets the data context for an element when it participates in data binding
    //@{
    Core::BaseComponent* GetDataContext() const;
    void SetDataContext(Core::BaseComponent* context);
    //@}

    /// Gets or sets the key to use to reference the style for this control, when theme styles are
    /// used or defined
    //@{
    ResourceKeyType* GetDefaultStyleKey() const;
    void SetDefaultStyleKey(ResourceKeyType* key);
    //@}

    /// Gets or sets a property that enables customization of appearance, effects, or other style 
    /// characteristics that will apply to this element when it captures keyboard focus
    //@{
    Style* GetFocusVisualStyle() const;
    void SetFocusVisualStyle(Style* style);
    //@}

    /// Gets or sets the suggested height of the element.
    //@{
    NsFloat32 GetHeight() const;
    void SetHeight(NsFloat32 height);
    //@}

    /// Gets or sets the horizontal alignment characteristics applied to this element when it is 
    /// composed within a parent element, such as a panel or items control
    //@{
    HorizontalAlignment GetHorizontalAlignment() const;
    void SetHorizontalAlignment(HorizontalAlignment hAlign);
    //@}

    /// Gets or sets a graphics transformation that should apply to this element when layout is 
    /// performed
    //@{
    Transform* GetLayoutTransform() const;
    void SetLayoutTransform(Transform* transform);
    //@}

    /// Gets or sets the outer margin of an element.
    //@{
    const Drawing::Thickness& GetMargin() const;
    void SetMargin(const Drawing::Thickness& margin);
    //@}

    /// Gets or sets the maximum height constraint of the element.
    //@{
    NsFloat32 GetMaxHeight() const;
    void SetMaxHeight(NsFloat32 maxHeigth);
    //@}

    /// Gets or sets the maximum width constraint of the element. 
    //@{
    NsFloat32 GetMaxWidth() const;
    void SetMaxWidth(NsFloat32 maxWidth);
    //@}

    /// Gets or sets the minimum height constraint of the element.
    //@{
    NsFloat32 GetMinHeight() const;
    void SetMinHeight(NsFloat32 minHeight);
    //@}

    /// Gets or sets the minimum width constraint of the element.
    //@{
    NsFloat32 GetMinWidth() const;
    void SetMinWidth(NsFloat32 minWidth);
    //@}

    /// Gets or sets the identifying name of the element. The name provides a reference so that 
    /// code-behind, such as event handler code, can refer to a markup element after it is 
    /// constructed during processing by a XAML processor. 
    //@{
    const NsChar* GetName() const;
    void SetName(const NsChar* name);
    //@}

    /// Gets or sets a value that indicates whether this element incorporates style properties from 
    /// theme styles.
    //@{
    NsBool GetOverridesDefaultStyle() const;
    void SetOverridesDefaultStyle(NsBool value);
    //@}

    /// Gets or sets the style used by this element when it is rendered
    //@{
    Style* GetStyle() const;
    void SetStyle(Style* style);
    //@}

    /// Gets or sets an arbitrary object value that can be used to store custom information about 
    /// this element
    //@{
    Core::BaseComponent* GetTag() const;
    void SetTag(Core::BaseComponent* tag);
    void SetTag(const NsChar* tag);
    //@}

    /// Gets or sets the tool-tip object that is displayed for this element in the user interface 
    //@{
    Core::BaseComponent* GetToolTip() const;
    void SetToolTip(Core::BaseComponent* tooltip);
    void SetToolTip(const NsChar* tooltip);
    //@}

    /// Gets or sets a value that indicates whether layout rounding should be applied to this
    /// element's size and position during layout
    //@{
    NsBool GetUseLayoutRounding() const;
    void SetUseLayoutRounding(NsBool useLayoutRounding);
    //@}

    /// Gets or sets the vertical alignment characteristics applied to this element when it is 
    /// composed within a parent element such as a panel or items control.
    //@{
    VerticalAlignment GetVerticalAlignment() const;
    void SetVerticalAlignment(VerticalAlignment vAlign);
    //@}

    /// Gets or sets the width of the element
    //@{
    NsFloat32 GetWidth() const;
    void SetWidth(NsFloat32 width);
    //@}

    /// Get the trigger collection
    TriggerCollection* GetTriggers() const;

    //@}

    /// Returns a binding expression if the target property has an active binding; otherwise,
    /// returns null
    BindingExpression* GetBindingExpression(const DependencyProperty* dp);

    /// Attaches a binding to this element, based on the provided binding object
    /// \return The binding expression just set
    BaseBindingExpression* SetBinding(const DependencyProperty* dp, BaseBinding* binding);

    /// Attaches a binding to this element, based on the provided source property name as a path
    /// qualification to the data source
    /// \return The binding expression just set
    BindingExpression* SetBinding(const DependencyProperty* dp, const NsChar* path);

    /// Gets a value that indicates whether this element has been loaded for presentation. 
    NsBool IsLoaded() const;

    /// Attempts to bring this element into view, within any scrollable regions it
    /// is contained within.
    void BringIntoView();

    /// Attempts to bring the provided region size of this element into view, within
    /// any scrollable regions it is contained within.
    void BringIntoView(const Drawing::Rect& targetRectangle);

    /// Gets the TimeManager that controls current element
    ITimeManager* GetTimeManager() const;

    /// Gets the logical parent element of this element
    FrameworkElement* GetParent() const;

    // Template management
    //@{

    /// Gets the logical parent or the templated parent when logical parent is not available
    FrameworkElement* GetParentOrTemplatedParent() const;

    /// Gets or sets the template parent of this element. This property is not relevant if the 
    /// element was not created through a template
    //@{
    FrameworkElement* GetTemplatedParent() const;
    void SetTemplatedParent(FrameworkElement* templatedParent,
        FrameworkTemplate* frameworkTemplate);
    //@}

    /// Looks for a named element in the applied template
    Core::BaseComponent* GetTemplateChild(const NsChar* name) const;
    template<class T>
    T* GetTemplateChild(const NsChar* name) const
    {
        return NsStaticCast<T*>(GetTemplateChild(name));
    }

    /// Gets the root element of the applied template
    FrameworkElement* GetTemplateRoot() const;

    /// Gets applied template on this element
    FrameworkTemplate* GetFrameworkTemplate() const;

    /// Applies a template on this element for the provided context
    void ApplyFrameworkTemplate(FrameworkTemplate* frameworkTemplate,
        Core::BaseComponent* dataContext);

    /// Returns a clone of this element. Used when applying a template
    Ptr<FrameworkElement> Clone(FrameworkElement* parent, FrameworkElement* templatedParent,
        FrameworkTemplate* template_) const;

    //@}

    /// Gets root for VisualState management
    virtual FrameworkElement* GetStateGroupsRoot() const;

    /// Provides accessors that simplifies access to the NameScope registration methods
    //@{
    Core::BaseComponent* FindName(const NsChar* name) const;
    ObjectWithNameScope FindNameAndScope(const NsChar* name) const;
    void RegisterName(const NsChar* name, Core::BaseComponent* object);
    void UnregisterName(const NsChar* name);
    void UpdateName(const NsChar* name, Core::BaseComponent* object);
    INameScope::ChangedDelegate& NameScopeChanged();
    //@}

    /// Templated version of FindName
    /// \remarks Asserts that returned object implements specified type
    template<class T>
    T* FindName(const NsChar* name) const
    {
        return NsStaticCast<T*>(FindName(name));
    }
    
    /// Finds a resource looking in the logical parent chain
    //@{
    Core::BaseComponent* FindResource(IResourceKey* key) const;
    Core::BaseComponent* TryFindResource(IResourceKey* key) const;
    //@}

    /// Templated version of FindResource and TryFindResource
    /// \remarks Asserts that returned object implements specified type
    //@{
    template<class T>
    T* FindResource(IResourceKey* key) const
    {
        return NsStaticCast<T*>(FindResource(key));
    }

    template<class T>
    T* TryFindResource(IResourceKey* key) const
    {
        return NsStaticCast<T*>(TryFindResource(key));
    }
    //@}

    /// Gets or sets the locally-defined resource dictionary
    //@{
    ResourceDictionary* GetResources() const;
    void SetResources(ResourceDictionary* resources);
    //@}

    /// Notifies when an ancestor has changed its parent
    AncestorChangedDelegate& AncestorChanged();
    /// Notifies when a change occurred in the resources dictionary of this element or an ancestor
    AncestorResourcesChangedDelegate& AncestorResourcesChanged();
    /// Notifies when a NameScope in an ancestor has changed any of its items
    AncestorNameScopeChangedDelegate& AncestorNameScopeChanged();
    /// Occurs just before any context menu on the element is closed
    UIElement::RoutedEvent_<ContextMenuEventHandler> ContextMenuClosing();
    /// Occurs when any context menu on the element is opened
    UIElement::RoutedEvent_<ContextMenuEventHandler> ContextMenuOpening();
    /// Occurs when the data context for this element changes
    UIElement::Event_<DependencyPropertyChangedEventHandler> DataContextChanged();
    /// Occurs when this element is initialized
    UIElement::Event_<EventHandler> Initialized();
    /// Occurs when the element is laid out, rendered, and ready for interaction
    UIElement::RoutedEvent_<RoutedEventHandler> Loaded();
    /// Occurs when BringIntoView is called on this element
    UIElement::RoutedEvent_<RequestBringIntoViewEventHandler> RequestBringIntoView();
    /// Occurs when either the ActualHeight or the ActualWidth properties change value on this 
    /// element
    UIElement::RoutedEvent_<SizeChangedEventHandler> SizeChanged();
    /// Occurs just before any tooltip on the element is closed
    UIElement::RoutedEvent_<ToolTipEventHandler> ToolTipClosing();
    /// Occurs when any tooltip on the element is opened
    UIElement::RoutedEvent_<ToolTipEventHandler> ToolTipOpening();
    /// Occurs when the element is removed from within an element tree of loaded elements
    UIElement::RoutedEvent_<RoutedEventHandler> Unloaded();

    /// From UIElement
    //@{
    NsBool MoveFocus(const TraversalRequest& request);
    DependencyObject* PredictFocus(FocusNavigationDirection direction);
    //@}

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ActualHeightProperty;
    static const DependencyProperty* ActualWidthProperty;
    static const DependencyProperty* ContextMenuProperty;
    static const DependencyProperty* DataContextProperty;
    static const DependencyProperty* DefaultStyleKeyProperty;
    static const DependencyProperty* FocusVisualStyleProperty;
    static const DependencyProperty* HeightProperty;
    static const DependencyProperty* HorizontalAlignmentProperty;
    static const DependencyProperty* LayoutTransformProperty;
    static const DependencyProperty* MarginProperty;
    static const DependencyProperty* MaxHeightProperty;
    static const DependencyProperty* MaxWidthProperty;
    static const DependencyProperty* MinHeightProperty;
    static const DependencyProperty* MinWidthProperty;
    static const DependencyProperty* NameProperty;
    static const DependencyProperty* OverridesDefaultStyleProperty;
    static const DependencyProperty* StyleProperty;
    static const DependencyProperty* TagProperty;
    static const DependencyProperty* ToolTipProperty;
    static const DependencyProperty* UseLayoutRoundingProperty;
    static const DependencyProperty* VerticalAlignmentProperty;
    static const DependencyProperty* WidthProperty;
    //@}

    /// Dependency events
    //@{
    static const RoutedEvent* LoadedEvent;
    static const RoutedEvent* RequestBringIntoViewEvent;
    static const RoutedEvent* SizeChangedEvent;
    static const RoutedEvent* UnloadedEvent;
    //@}

protected:
    /// Invoked whenever an unhandled ContextMenuClosing routed event reaches this class in its
    /// route. Implement this method to add class handling for this event
    virtual void OnContextMenuClosing(const ContextMenuEventArgs& e);

    /// Invoked whenever an unhandled ContextMenuOpening routed event reaches this class in its
    /// route. Implement this method to add class handling for this event
    virtual void OnContextMenuOpening(const ContextMenuEventArgs& e);

    /// Invoked when the context menu changes
    virtual void OnContextMenuChanged(ContextMenu* oldMenu, ContextMenu* newMenu);

    /// Invoked when the style in use on this element changes, which will invalidate
    /// the layout.
    virtual void OnStyleChanged(Style* oldStyle, Style* newStyle);

    /// Invoked when focus style changes
    virtual void OnFocusStyleChanged(Style* oldStyle, Style* newStyle);

    /// Invoked whenever an unhandled ToolTipClosing routed event reaches this class in its route. 
    /// Implement this method to add class handling for this event.
    virtual void OnToolTipClosing(const ToolTipEventArgs& e);

    /// Invoked whenever the ToolTipOpening routed event reaches this class in its route. Implement 
    /// this method to add class handling for this event.
    virtual void OnToolTipOpening(const ToolTipEventArgs& e);

    /// Performs custom clone work for a derived class
    virtual void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;

    /// Adds the provided object to the logical tree of this element
    void AddLogicalChild(Core::BaseComponent* child);

    /// Removes the provided object from this element's logical tree. FrameworkElement updates the
    /// affected logical tree parent pointers to keep in sync with this deletion.
    void RemoveLogicalChild(Core::BaseComponent* child);

    /// Gets the number of child logical elements for this element
    /// \remarks Each element implementation will decide how to store logical children
    virtual NsSize GetLogicalChildrenCount() const;

    /// Returns the specified element in the parent Collection
    /// \remarks Each element implementation will decide how to store logical children
    virtual Core::BaseComponent* GetLogicalChild(NsSize index) const;

    /// Allows derived classes to use this visual as the default visual child
    //@{
    Visual* GetSingleVisualChild() const;
    void SetSingleVisualChild(Visual* child);
    //@}

    // Property value changed events
    //@{
    virtual void OnWidthChanged(NsFloat32 width);
    virtual void OnHeightChanged(NsFloat32 height);
    //@}

    /// Looks for a DataTemplate in the UI tree that matches the type specified
    static DataTemplate* TryFindTemplate(FrameworkElement* element, const Core::TypeClass* type);

    /// Indicates if the property specified is set as a local value in the template
    NsBool IsTemplateLocalValue(const DependencyProperty* dp) const;

    /// Invoked when framework template changes
    virtual void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);

    /// Invoked when templated parent changes
    virtual void OnTemplatedParentChanged(FrameworkElement* oldParent, FrameworkElement* newParent);

    /// When overridden in a derived class, measures the size in layout required for child elements
    /// and determines a size for the FrameworkElement-derived class
    /// \return The size that this element determines it needs during layout, based on its
    //// calculations of child element sizes
    ///
    /// \note Override MeasureOverride to implement custom layout sizing behavior for your element
    //// as it participates in the layout system. Your implementation should do the following:
    ///
    //// 1. Iterate your element's particular collection of children that are part of layout,
    ////    call Measure on each child element.
    //// 2. Immediately get DesiredSize on the child (this is set as a property after Measure
    ////    is called).
    //// 3. Compute the net desired size of the parent based upon the measurement of the
    //// child elements.
    ///
    //// The return value of MeasureOverride should be the element's own desired size, which
    //// then becomes the measure input for the parent element of the current element. This
    //// same process continues through the layout system until the root element is reached
    ///
    //// During this process, child elements might return a larger DesiredSize size than the
    //// initial availableSize to indicate that the child element wants more space. This might
    //// be handled in your own implementation by introducing a scrollable region, by resizing
    //// the parent control, by establishing some manner of stacked order, or any number of
    //// solutions for measuring or arranging content
    virtual Drawing::Size MeasureOverride(const Drawing::Size& availableSize);

    /// When overridden in a derived class, positions child elements and determines a size for
    /// a FrameworkElement derived class
    /// \param finalSize The final area within the parent that this element should use to arrange
    //// itself and its children
    /// \return The actual size used
    ///
    /// \note The implementation pattern should call Arrange on each visible child element, and
    //// pass the final desired size for each child element as the finalRect parameter. Parent
    //// elements should call Arrange on each child, otherwise the child elements will not be
    //// rendered
    virtual Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);

    /// Calculates min and max limits depending on width, height and limit values
    void GetMinMax(NsFloat32 width, NsFloat32 height,
        NsFloat32& minW, NsFloat32& minH, NsFloat32& maxW, NsFloat32& maxH) const;

    /// From DependencyObject
    //@{
    void OnInit();
    void OnPostInit();
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    NsBool OnSubPropertyChanged(const DependencyProperty* prop);
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue);
    ProviderValue GetProviderValue(const DependencyProperty* dp) const;
    ProviderValue GetNonCachedProviderValue(const DependencyProperty* dp) const;
    NsUInt8 GetNonCachedValueProvider(const DependencyProperty* dp) const;
    //@}

    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const;
    Visual* GetVisualChild(NsSize index) const;
    void OnConnectToView(IView* view);
    void OnConnectToViewChildren();
    void OnDisconnectFromView();
    void OnVisualOffsetChanged();
    void OnVisualTransformChanged();
    //@}

    /// From UIElement
    //@{
    Drawing::Size MeasureCore(const Drawing::Size& availableSize);
    void ArrangeCore(const Drawing::Rect& finalRect);
    Ptr<Geometry> GetLayoutClip(const Drawing::Size& layoutSlotSize) const;
    UIElement* GetUIParentCore() const;
    void OnGotFocus(const RoutedEventArgs& e);
    void OnRenderSizeChanged(const SizeChangedInfo& sizeInfo);
    //@}

private:
    /// Base classes are non-copyable objects
    //@{
    FrameworkElement(const FrameworkElement&);
    FrameworkElement& operator=(const FrameworkElement&);
    //@}

    void OnAppResourcesChanged(Core::BaseComponent* sender,
        const NotifyDictionaryChangedEventArgs& args);
    void OnThemeResourcesChanged(Core::BaseComponent* sender,
        const NotifyDictionaryChangedEventArgs& args);

    NsBool IsStyleTriggerProviderEnabled() const;
    void StyleTriggerProviderEnable();
    void StyleTriggerProviderDisable();
    void ImplicitStyleProviderEnable();
    void ImplicitStyleProviderDisable();
    void DefaultStyleProviderEnable(IView* view);
    void DefaultStyleProviderDisable(IView* view);

    TemplateLocalValueProvider* GetTemplateLocalValues() const;

    Style* GetDefaultStyle() const;

    FocusVisualLayer* GetFocusVisualLayer() const;
    void SetFocusVisualLayer(FocusVisualLayer* focusVisual);

    Core::BaseComponent* TryFindResource(IResourceKey* key, NsBool themeSearch) const;
    Core::BaseComponent* TryFindResourceInElement(IResourceKey* key,
        NsBool fullElementSearch) const;

    void OnFrameworkTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkTemplate* newTemplate);

    void RemoveTemplatedParent();

    struct InheritedValueInfo
    {
        const DependencyProperty* dp;
        const void* val;
        const void* cur;
    };

    typedef NsVector<InheritedValueInfo> InheritedProps;
    struct InheritedComparer;

    FrameworkElement* GetInheritanceParent() const;
    void UpdateInheritedProps();
    void StoreAncestorInheritedProps(InheritedProps& props);
    void UpdateStoredInheritedProps(InheritedProps& props);
    void CheckInheritedPropsChanges(InheritedProps& props);
    void PropagateInheritedPropsChanges(const DependencyProperty* prop, NsBool isSubPropertyChange,
        const void* oldValue, const void* newValue);
    void OnLogicalAncestorChanged(FrameworkElement* element, NsBool traverseChildren,
        NsBool updateInherited, InheritedProps* parentProps);

    void OnResourcesChanged(Core::BaseComponent* sender,
        const NotifyDictionaryChangedEventArgs& args);
    void OnAncestorResourcesChanged(Core::BaseComponent* sender,
        const NotifyDictionaryChangedEventArgs& args);
    void OnNameScopeChanged(INameScope* sender, const NameScopeChangedArgs& args);
    void OnAncestorNameScopeChanged(FrameworkElement* element,
        const AncestorNameScopeChangedArgs& args);

    Drawing::Size ApplyTransformToSize(Transform* transform, const Drawing::Size& size);
    INameScope* GetNameScope() const;
    void SetParent(FrameworkElement* parent);
    void CheckPropertyMetadata(const DependencyProperty* prop, NsBool isSubPropertyChange,
        const void* oldValue, const void* newValue);
    Drawing::Point CalculateArrangeOffset(const Drawing::Size& clientSize,
        const Drawing::Size& renderSize) const;

    // Loaded/Unloaded events
    //@{
    friend class ViewLayout;
    void RaiseLoaded();
    void OnLoaded();
    void OnUnloaded();
    //@}

    // Management of framework element flags
    //@{
    void SetElementFlag(NsUInt32 flag);
    void ClearElementFlag(NsUInt32 flag);
    NsBool CheckElementFlag(NsUInt32 flag) const;
    //@}

    void CloneRoutedEvents(FrameworkElement* clone) const;
    void CloneEvents(FrameworkElement* clone) const;

    void TransferAnimations();
    void EnsureTimeManager(NsBool createTimeManager = true);
    NsBool EnsureTimeManager(FrameworkElement* parent);

    void EnsureResources();
    void ConnectResources();
    void DisconnectResources();

    void EnsureTriggers();
    void RegisterTriggers();
    void UnregisterTriggers();

    NsBool CancelLoadedRequest();

    static NsBool ValidateSize(const void* value);
    static NsBool ValidateMinSize(const void* value);
    static NsBool ValidateMaxSize(const void* value);

    friend class XamlContext;
    void SetDelayedStaticResources(DelayedStaticResources* delayedResources);
    DelayedStaticResources* GetDelayedStaticResources() const;

private:
    friend class UIElementCollection;
    friend class ItemCollection;
    friend struct LogicalTreeHelper;
    friend class ContextMenu;
    friend struct ContextMenuService;
    friend class ToolTip;
    friend struct ToolTipService;
    friend class UserControl;
    friend class ContentControl;
    friend class FocusVisualLayer;
    friend class DynamicResourceExpression;
    friend struct TemplatedParentTriggerProvider;
    friend class TemplateLocalValueProvider;
    friend struct ImplicitStyleProvider;
    friend struct StyleTriggerProvider;
    friend struct TemplateTriggerProvider;
    friend struct DefaultStyleTriggerProvider;
    friend struct DefaultStyleSetterProvider;
    friend struct InheritedPropertyProvider;
    friend class FrameworkElementTest;
    friend class InheritedPropertyProviderTest;
    friend class StoryboardTest;

    // Animation time manager used for this element
    Ptr<TimeManagerRef> mTimeManagerRef;

    // Parent node in the XAML tree
    IUITreeNode* mOwner;

    // Logical parent of this element
    FrameworkElement* mParent;

    // Control that contains this element as part of its template visual tree
    FrameworkElement* mTemplatedParent;

    // Template applied to this framework element
    static const DependencyProperty* TemplateProperty;

    // Stores local values for elements that are part of a template
    static const DependencyProperty* TemplateLocalValuesProperty;

    // Default style if one is available for this element type
    static const DependencyProperty* DefaultStyleProperty;

    // Layer that renders focus visual style
    static const DependencyProperty* FocusVisualLayerProperty;
    struct FocusVisualContainer;

    // Prevents triggers to enter into an infinite recursion when invalidating
    NsVector<const DependencyProperty*> mInvalidatedProperties;

    // Element resources dictionary
    Ptr<ResourceDictionary> mResources;

    // Stores a list of StaticResources that need to be resolved during initialization
    static const DependencyProperty* DelayedStaticResourcesProperty;

    // Trigger collection
    Ptr<TriggerCollection> mTriggers;

    // Default storage for a single visual child
    Ptr<Visual> mVisualChild;

    // Desired size without applying clipping
    Drawing::Size mUnclippedSize;

    // Inherited properties set in the ancestors
    InheritedProps mInheritedProps;

    // FrameworkElement flags
    NsInt32 mElementFlags;

    // Element request to raise Loaded event when layout finalizes
    LayoutRequest mLoadedRequest;

    // Delegates
    //@{
    AncestorChangedDelegate mAncestorChanged;
    AncestorResourcesChangedDelegate mAncestorResourcesChanged;
    AncestorNameScopeChangedDelegate mAncestorNameScopeChanged;
    //@}

    NS_DECLARE_REFLECTION(FrameworkElement, UIElement)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
