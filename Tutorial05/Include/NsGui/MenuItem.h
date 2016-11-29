////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MENUITEM_H__
#define __GUI_MENUITEM_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/CoreApi.h>
#include <NsGui/HeaderedItemsControl.h>
#include <NsGui/ICommandSource.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class PopupLayer;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a selectable item inside a Menu.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.menuitem.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API MenuItem: public HeaderedItemsControl, public ICommandSource
{
public:
    MenuItem();

    /// Gets or sets the parameter to pass to the Command property of a MenuItem
    //@{
    Core::BaseComponent* GetCommandParameter() const;
    void SetCommandParameter(Core::BaseComponent* parameter);
    //@}

    /// Gets or sets the command associated with the menu item
    //@{
    ICommand* GetCommand() const;
    void SetCommand(ICommand* command);
    //@}

    /// Gets or sets the target element on which to raise the specified command
    //@{
    UIElement* GetCommandTarget() const;
    void SetCommandTarget(UIElement* target);
    //@}

    /// Gets or sets the icon that appears in a MenuItem
    //@{
    Core::BaseComponent* GetIcon() const;
    void SetIcon(Core::BaseComponent* icon);
    //@}

    /// Sets the text describing an input gesture that will call the command tied to the specified 
    /// item
    //@{
    const NsChar* GetInputGestureText() const;
    void SetInputGestureText(const NsChar* text);
    //@}

    /// Gets a value that indicates whether a MenuItem can be checked
    //@{
    NsBool GetIsCheckable() const;
    void SetIsCheckable(NsBool value);
    //@}

    /// Gets or sets a value that indicates whether the MenuItem is checked
    //@{
    NsBool GetIsChecked() const;
    void SetIsChecked(NsBool value);
    //@}

    /// Gets a value that indicates whether a MenuItem is highlighted
    NsBool GetIsHighlighted() const;

    /// Gets a value that indicates whether a MenuItem is pressed
    NsBool GetIsPressed() const;

    /// Gets or sets a value that indicates whether the submenu of the MenuItem is open
    //@{
    NsBool GetIsSubmenuOpen() const;
    void SetIsSubmenuOpen(NsBool value);
    //@}
    
    /// Gets a value that indicates the role of a MenuItem
    MenuItemRole GetRole() const;

    /// Gets or sets a value that indicates that the submenu in which this MenuItem is located 
    /// should not close when this item is clicked
    //@{
    NsBool GetStaysOpenOnClick() const;
    void SetStaysOpenOnClick(NsBool value);
    //@}

    /// Occurs when a menu item is checked
    UIElement::RoutedEvent_<RoutedEventHandler> Checked();

    /// Occurs when a MenuItem is clicked
    UIElement::RoutedEvent_<RoutedEventHandler> Click();

    /// Occurs when the state of the IsSubmenuOpen property changes to false
    UIElement::RoutedEvent_<RoutedEventHandler> SubmenuClosed();

    /// Occurs when the state of the IsSubmenuOpen property changes to true
    UIElement::RoutedEvent_<RoutedEventHandler> SubmenuOpened();

    /// Occurs when a MenuItem is unchecked
    UIElement::RoutedEvent_<RoutedEventHandler> Unchecked();

public:
    static const DependencyProperty* CommandParameterProperty;
    static const DependencyProperty* CommandProperty;
    static const DependencyProperty* CommandTargetProperty;
    static const DependencyProperty* IconProperty;
    static const DependencyProperty* InputGestureTextProperty;
    static const DependencyProperty* IsCheckableProperty;
    static const DependencyProperty* IsCheckedProperty;
    static const DependencyProperty* IsHighlightedProperty;
    static const DependencyProperty* IsPressedProperty;
    static const DependencyProperty* IsSubmenuOpenProperty;
    static const DependencyProperty* RoleProperty;
    static const DependencyProperty* StaysOpenOnClickProperty;

    static const DependencyProperty* SeparatorStyleKey;

    static const RoutedEvent* CheckedEvent;
    static const RoutedEvent* ClickEvent;
    static const RoutedEvent* SubmenuClosedEvent;
    static const RoutedEvent* SubmenuOpenedEvent;
    static const RoutedEvent* UncheckedEvent;

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Visual
    //@{
    void OnDisconnectFromView();
    //@}

    /// From UIElement
    //@{
    NsBool IsEnabledCore() const;
    void OnMouseEnter(const MouseEventArgs& e);
    void OnMouseLeave(const MouseEventArgs& e);
    void OnMouseMove(const MouseEventArgs& e);
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e);
    void OnMouseRightButtonDown(const MouseButtonEventArgs& e);
    void OnMouseRightButtonUp(const MouseButtonEventArgs& e);
    //@}

    /// From FrameworkElement
    //@{
    void OnLogicalParentChanged(FrameworkElement* oldParent);
    //@}

    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;
    void ApplyItemContainerStyle(DependencyObject* container) const;
    void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);
    //@}

private:
    friend class ContextMenu;
    static void SetIsInsideContextMenu(DependencyObject* element, NsBool value);
    NsBool GetIsInsideContextMenu() const;

    NsBool IsSeparator() const;

    void OnIsCheckedChanged(NsBool isChecked);
    void OnIsSubmenuOpenChanged(NsBool isOpen);

    void OnHeaderClicked();
    void OnItemClicked();

    void OnDirectlyOverChanged(UIElement* directlyOver);

    void UpdateSubmenuVisibility(NsBool visible);
    void UpdateRole();

    void ShowSubmenu();
    void HideSubmenu();

    void ActivateMenu(NsBool activate);

    void CloseAncestors();
    void CloseDescendants();

    void RegisterMouse();
    void UnregisterMouse();

    friend class Popup;
    void SetSubmenuLayer(PopupLayer* submenuLayer);

    static NsBool StaticCoerceHeader(const DependencyObject* object, const void* value,
        void* coercedValue);
    static NsBool StaticCoerceInputGesture(const DependencyObject* object, const void* value,
        void* coercedValue);

private:
    NsUInt32 mFlags;
    PopupLayer* mSubmenuLayer;

    static const DependencyProperty* IsInsideContextMenuProperty;

    NS_DECLARE_REFLECTION(MenuItem, HeaderedItemsControl)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
