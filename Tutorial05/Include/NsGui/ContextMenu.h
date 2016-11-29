////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONTEXTMENU_H__
#define __GUI_CONTEXTMENU_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/BaseMenu.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Drawing
{
struct Rect;
struct Point;
}
namespace Gui
{
class Popup;
class PopupBinder;
enum PlacementMode;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a pop-up menu that enables a control to expose functionality that is specific to
/// the context of the control. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.contextmenu.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ContextMenu: public BaseMenu
{
public:
    ContextMenu();

    /// Gets or sets a value that indicates whether the context menu appears with a dropped shadow
    //@{
    NsBool GetHasDropShadow() const;
    void SetHasDropShadow(NsBool value);
    //@}

    /// Get or sets the horizontal distance between the target origin and the popup alignment point
    //@{
    NsFloat32 GetHorizontalOffset() const;
    void SetHorizontalOffset(NsFloat32 value);
    //@}

    /// Gets or sets a value that indicates whether the ContextMenu is visible. 
    //@{
    NsBool GetIsOpen() const;
    void SetIsOpen(NsBool value);
    //@}

    /// Gets or sets the Placement property of a ContextMenu
    //@{
    PlacementMode GetPlacement() const;
    void SetPlacement(PlacementMode mode);
    //@}

    /// Gets or sets the area relative to which the context menu is positioned when it opens
    //@{
    const Drawing::Rect& GetPlacementRectangle() const;
    void SetPlacementRectangle(const Drawing::Rect& rect);
    //@}

    /// Gets or sets the UIElement relative to which the ContextMenu is positioned when it opens
    //@{
    UIElement* GetPlacementTarget() const;
    void SetPlacementTarget(UIElement* target);
    //@}

    /// Gets or sets a value that indicates whether the ContextMenu should close automatically
    //@{
    NsBool GetStaysOpen() const;
    void SetStaysOpen(NsBool value);
    //@}

    /// Get or sets the vertical distance between the target origin and the popup alignment point
    //@{
    NsFloat32 GetVerticalOffset() const;
    void SetVerticalOffset(NsFloat32 value);
    //@}

    /// Gets Popup where ContextMenu is shown
    Popup* GetPopup() const;

    /// Occurs when a particular instance of a ContextMenu closes
    UIElement::RoutedEvent_<RoutedEventHandler> Closed();

    /// Occurs when a particular instance of a context menu opens
    UIElement::RoutedEvent_<RoutedEventHandler> Opened();

    /// From IUITreeNode
    //@{
    void SetNodeParent(IUITreeNode* parent);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* HasDropShadowProperty;
    static const DependencyProperty* HorizontalOffsetProperty;
    static const DependencyProperty* IsOpenProperty;
    static const DependencyProperty* PlacementProperty;
    static const DependencyProperty* PlacementRectangleProperty;
    static const DependencyProperty* PlacementTargetProperty;
    static const DependencyProperty* StaysOpenProperty;
    static const DependencyProperty* VerticalOffsetProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* ClosedEvent;
    static const RoutedEvent* OpenedEvent;
    //@}

protected:
    virtual void OnOpened(const RoutedEventArgs& e);
    virtual void OnClosed(const RoutedEventArgs& e);

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;
    void ApplyItemContainerStyle(DependencyObject* container) const;
    //@}

private:
    void OnIsOpenChanged(NsBool isOpen);
    void OnPopupClosed(Core::BaseComponent* sender, const EventArgs& e);

    void ShowPopup();
    void HidePopup();

    template<class T>
    static NsBool StaticCoerce(const DependencyProperty* dp,
        const DependencyObject* object, const void* value, void* coercedValue);

    static NsBool StaticCoerceHasDropShadow(const DependencyObject* object, const void* value,
        void* coercedValue);
    static NsBool StaticCoerceHorizontalOffset(const DependencyObject* object, const void* value,
        void* coercedValue);
    static NsBool StaticCoercePlacement(const DependencyObject* object, const void* value,
        void* coercedValue);
    static NsBool StaticCoercePlacementRectangle(const DependencyObject* object, const void* value,
        void* coercedValue);
    static NsBool StaticCoercePlacementTarget(const DependencyObject* object, const void* value,
        void* coercedValue);
    static NsBool StaticCoerceVerticalOffset(const DependencyObject* object, const void* value,
        void* coercedValue);

    static void StaticOnContextMenuLostMouseCapture(Core::BaseComponent* obj, const EventArgs& e);
    void OnContextMenuLostMouseCapture(const MouseEventArgs& e);

    static void StaticOnContextMenuMouseButtonDown(Core::BaseComponent* obj, const EventArgs& e);
    void OnContextMenuMouseButtonDown(const MouseEventArgs& e);

private:
    PopupBinder* mPopupInternal;

    NS_DECLARE_REFLECTION(ContextMenu, BaseMenu)
};

}
}

#endif