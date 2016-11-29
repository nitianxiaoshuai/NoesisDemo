////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONTEXTMENUSERVICE_H__
#define __GUI_CONTEXTMENUSERVICE_H__


#include <Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Enums.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
class BaseComponent;
}
namespace Drawing
{
struct Rect;
}
namespace Gui
{
class DependencyObject;
class DependencyProperty;
class RoutedEvent;
class UIElement;
class ContextMenu;
struct EventArgs;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ContextMenuService. The ContextMenuService class provides attached properties that can be used
/// to specify the appearance and position of a context menu.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ContextMenuService
{
    /// Dependency properties
    //@{
    static const DependencyProperty* ContextMenuProperty;
    static const DependencyProperty* HasDropShadowProperty;
    static const DependencyProperty* HorizontalOffsetProperty;
    static const DependencyProperty* IsEnabledProperty;
    static const DependencyProperty* PlacementProperty;
    static const DependencyProperty* PlacementRectangleProperty;
    static const DependencyProperty* PlacementTargetProperty;
    static const DependencyProperty* ShowOnDisabledProperty;
    static const DependencyProperty* VerticalOffsetProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* ContextMenuClosingEvent;
    static const RoutedEvent* ContextMenuOpeningEvent;
    //@}

    /// Gets the value of the ContextMenu property of the specified object
    static ContextMenu* GetContextMenu(DependencyObject* obj);
    
    /// Sets the value of the ContextMenu property of the specified object
    static void SetContextMenu(DependencyObject* obj, ContextMenu* contextMenu);

    /// Gets a value that indicates whether the context menu appears with a dropped 
    static NsBool GetHasDropShadow(DependencyObject* obj);
    
    /// Sets a value that indicates whether the context menu appears with a dropped 
    static void SetHasDropShadow(DependencyObject* obj, NsBool hasDropShadow);

    /// Gets the horizontal distance between the target origin and the popup alignment point
    static NsFloat32 GetHorizontalOffset(DependencyObject* obj);
    
    /// Sets the horizontal distance between the target origin and the popup alignment point
    static void SetHorizontalOffset(DependencyObject* obj, NsFloat32 offset);

    /// Gets a value that indicates whether the ContextMenu can be shown
    static NsBool GetIsEnabled(DependencyObject* obj);
    
    /// Sets a value that indicates whether the ContextMenu can be shown
    static void SetIsEnabled(DependencyObject* obj, NsBool isEnabled);

    /// Gets the Placement property of a ContextMenu
    static PlacementMode GetPlacement(DependencyObject* obj);
    
    /// Sets the Placement property of a ContextMenu
    static void SetPlacement(DependencyObject* obj, PlacementMode mode);

    /// Gets the area relative to which the context menu is positioned when it opens
    static const Drawing::Rect& GetPlacementRectangle(DependencyObject* obj);
    
    /// Sets the area relative to which the context menu is positioned when it opens
    static void SetPlacementRectangle(DependencyObject* obj, const Drawing::Rect& rect);

    /// Gets the UIElement relative to which the ContextMenu is positioned when it opens
    static UIElement* GetPlacementTarget(DependencyObject* obj);
    
    /// Sets the UIElement relative to which the ContextMenu is positioned when it opens
    static void SetPlacementTarget(DependencyObject* obj, UIElement* target);

    /// Gets a value that indicates whether the ContextMenu should be shown when its parent
    /// is grayed out
    static NsBool GetShowOnDisabled(DependencyObject* obj);
    
    /// Sets a value that indicates whether the ContextMenu should be shown when its parent
    /// is grayed out
    static void SetShowOnDisabled(DependencyObject* obj, NsBool showOnDisable);

    /// Gets the vertical distance between the target origin and the popup alignment point
    static NsFloat32 GetVerticalOffset(DependencyObject* obj);
    
    /// Sets the vertical distance between the target origin and the popup alignment point
    static void SetVerticalOffset(DependencyObject* obj, NsFloat32 offset);

private:
    static void StaticOnContextMenuClosing(Core::BaseComponent* obj, const EventArgs& e);
    static void StaticOnContextMenuOpening(Core::BaseComponent* obj, const EventArgs& e);
    static NsBool CanOpenContextMenu(DependencyObject* obj);

    NS_DECLARE_REFLECTION(ContextMenuService, Core::NoParent)
};

}
}

#endif
