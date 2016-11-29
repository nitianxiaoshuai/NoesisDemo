////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TOOLTIPSERVICE_H__
#define __GUI_TOOLTIPSERVICE_H__


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
class ToolTip;
struct EventArgs;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a service that provides properties and events to control the display and behavior
/// of tooltips.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.tooltipservice.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ToolTipService
{
    /// Dependency properties
    //@{
    static const DependencyProperty* BetweenShowDelayProperty;
    static const DependencyProperty* HasDropShadowProperty;
    static const DependencyProperty* HorizontalOffsetProperty;
    static const DependencyProperty* InitialShowDelayProperty;
    static const DependencyProperty* IsEnabledProperty;
    static const DependencyProperty* IsOpenProperty;
    static const DependencyProperty* PlacementProperty;
    static const DependencyProperty* PlacementRectangleProperty;
    static const DependencyProperty* PlacementTargetProperty;
    static const DependencyProperty* ShowDurationProperty;
    static const DependencyProperty* ShowOnDisabledProperty;
    static const DependencyProperty* ToolTipProperty;
    static const DependencyProperty* VerticalOffsetProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* ToolTipClosingEvent;
    static const RoutedEvent* ToolTipOpeningEvent;
    //@}

    /// Gets the maximum time between the display of two tooltips where the second tooltip
    /// appears without a delay
    static NsInt32 GetBetweenShowDelay(const DependencyObject* obj);
    
    /// Sets the maximum time between the display of two tooltips where the second tooltip
    /// appears without a delay
    static void SetBetweenShowDelay(DependencyObject* obj, NsInt32 delay);

    /// Gets whether the tooltip displays a drop shadow effect
    static NsBool GetHasDropShadow(const DependencyObject* obj);
    
    /// Sets whether the tooltip displays a drop shadow effect
    static void SetHasDropShadow(DependencyObject* obj, NsBool shadow);

    /// Gets the offset from the left of the area that is specified for the tooltip by the
    /// PlacementRectangle and PlacementTarget properties
    static NsFloat32 GetHorizontalOffset(const DependencyObject* obj);
    
    /// Sets the offset from the left of the area that is specified for the tooltip by the
    /// PlacementRectangle and PlacementTarget properties
    static void SetHorizontalOffset(DependencyObject* obj, NsFloat32 offset);

    /// Gets the length of time before a tooltip opens
    static NsInt32 GetInitialShowDelay(const DependencyObject* obj);
    
    /// Sets the length of time before a tooltip opens
    static void SetInitialShowDelay(DependencyObject* obj, NsInt32 delay);

    /// Gets whether a tooltip appears
    static NsBool GetIsEnabled(const DependencyObject* obj);
    
    /// Sets whether a tooltip appears
    static void SetIsEnabled(DependencyObject* obj, NsBool isEnabled);

    /// Gets whether a tooltip is currently visible
    static NsBool GetIsOpen(const DependencyObject* obj);
    
    /// Sets whether a tooltip is currently visible
    static void SetIsOpen(DependencyObject* obj, NsBool isOpen);

    /// Gets the orientation of the tooltip when it opens, and specifies how the tooltip
    /// behaves when it overlaps screen boundaries
    static PlacementMode GetPlacement(const DependencyObject* obj);
    
    /// Sets the orientation of the tooltip when it opens, and specifies how the tooltip
    /// behaves when it overlaps screen boundaries
    static void SetPlacement(DependencyObject* obj, PlacementMode placement);

    /// Gets the rectangular area relative to which the tooltip is positioned
    static const Drawing::Rect& GetPlacementRectangle(const DependencyObject* obj);
    
    /// Sets the rectangular area relative to which the tooltip is positioned
    static void SetPlacementRectangle(DependencyObject* obj, const Drawing::Rect& rect);

    /// Gets the object relative to which the tooltip is positioned
    static UIElement* GetPlacementTarget(const DependencyObject* obj);
    
    /// Sets the object relative to which the tooltip is positioned
    static void SetPlacementTarget(DependencyObject* obj, UIElement* target);

    /// Gets the amount of time that a tooltip remains visible
    static NsInt32 GetShowDuration(const DependencyObject* obj);
    
    /// Sets the amount of time that a tooltip remains visible
    static void SetShowDuration(DependencyObject* obj, NsInt32 duration);

    /// Gets whether a tooltip appears for an object that is not enabled
    static NsBool GetShowOnDisabled(const DependencyObject* obj);
    
    /// Sets whether a tooltip appears for an object that is not enabled
    static void SetShowOnDisabled(DependencyObject* obj, NsBool showOnDisable);

    /// Gets the content of a tooltip
    static Core::BaseComponent* GetToolTip(const DependencyObject* obj);
    
    /// Sets the content of a tooltip
    static void SetToolTip(DependencyObject* obj, Core::BaseComponent* toolTip);

    /// Gets the distance from the top of the area that is specified for the tooltip by the
    /// PlacementRectangle and PlacementTarget properties
    static NsFloat32 GetVerticalOffset(const DependencyObject* obj);
    
    /// Sets the distance from the top of the area that is specified for the tooltip by the
    /// PlacementRectangle and PlacementTarget properties
    static void SetVerticalOffset(DependencyObject* obj, NsFloat32 offset);

    /// Finds the first object in the tree from the specified element that can show a tool tip
    static UIElement* FindValidToolTipOwner(UIElement* obj);

private:
    static const RoutedEvent* FindToolTipEvent;
    struct FindToolTipEventArgs;

private:
    static void StaticOnFindToolTip(Core::BaseComponent* obj, const EventArgs& e);
    static void StaticOnToolTipClosing(Core::BaseComponent* obj, const EventArgs& e);
    static void StaticOnToolTipOpening(Core::BaseComponent* obj, const EventArgs& e);
    static NsBool CanOpenToolTip(DependencyObject* obj);

    NS_DECLARE_REFLECTION(ToolTipService, Core::NoParent)
};

}
}

#endif
