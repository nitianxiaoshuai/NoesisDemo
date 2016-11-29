////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SCROLLBAR_H__
#define __GUI_SCROLLBAR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/RangeBase.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
enum Orientation;
class Track;
class BaseButton;
class RepeatButton;
class ScrollViewer;
struct DragStartedEventArgs;
struct DragDeltaEventArgs;
struct DragCompletedEventArgs;
struct CanExecuteRoutedEventArgs;
struct ExecutedRoutedEventArgs;
class RoutedCommand;
//@}

enum ScrollEventType
{
    /// The Thumb was dragged to a new position and is now no longer being dragged by the user. 
    ScrollEventType_EndScroll,
    /// The Thumb moved to the Minimum position of the ScrollBar. For a vertical ScrollBar, this
    /// movement occurs when the CTRL+HOME keys are pressed. This movement corresponds to a 
    /// ScrollToTopCommand in a vertical ScrollBar and a ScrollToLeftEndCommand in a horizontal 
    /// ScrollBar. 
    ScrollEventType_First,
    /// The Thumb moved a specified distance, as determined by the value of LargeChange, to the 
    /// left for a horizontal ScrollBar or upward for a vertical ScrollBar. For a vertical 
    /// ScrollBar, this movement occurs when the page button that is above the Thumb is pressed, 
    /// or when the PAGE UP key is pressed, and corresponds to a PageUpCommand. For a horizontal 
    /// ScrollBar, this movement occurs when the page button to the left of the Thumb is pressed, 
    /// and corresponds to a PageLeftCommand. 
    ScrollEventType_LargeDecrement,
    /// The Thumb moved a specified distance, as determined by the value of LargeChange, to the 
    /// right for a horizontal ScrollBar or downward for a vertical ScrollBar. For a vertical 
    /// ScrollBar, this movement occurs when the page button that is below the Thumb is pressed, 
    /// or when the PAGE DOWN key is pressed, and corresponds to a PageDownCommand. For a 
    /// horizontal ScrollBar, this movement occurs when the page button to the right of the Thumb 
    /// is pressed, and corresponds to a PageRightCommand. 
    ScrollEventType_LargeIncrement,
    /// The Thumb moved to the Maximum position of the ScrollBar. For a vertical ScrollBar, this 
    /// movement occurs when the CTRL+END keys are pressed. This movement corresponds to a 
    /// ScrollToEndCommand in a vertical ScrollBar and a ScrollToRightEndCommand in a horizontal 
    /// ScrollBar. 
    ScrollEventType_Last,
    /// The Thumb moved a small distance, as determined by the value of SmallChange, to the left 
    /// for a horizontal ScrollBar or upward for a vertical ScrollBar. For a vertical ScrollBar, 
    /// this movement occurs when the upper RepeatButton is pressed or when the UP ARROW key is 
    /// pressed, and corresponds to a LineUpCommand. For a horizontal ScrollBar, this movement 
    /// occurs when the left RepeatButton is pressed, and corresponds to a LineLeftCommand. 
    ScrollEventType_SmallDecrement,
    /// The Thumb moved a small distance, as determined by the value of SmallChange, to the right 
    /// for a horizontal ScrollBar or downward for a vertical ScrollBar. For a vertical ScrollBar,
    /// this movement occurs when the lower RepeatButton is pressed or when the DOWN ARROW key is 
    /// pressed, and corresponds to a LineDownCommand. For a horizontal ScrollBar, this movement 
    /// occurs when the right RepeatButton is pressed, and corresponds to a LineRightCommand. 
    ScrollEventType_SmallIncrement,
    /// The Thumb moved to a new position because the user selected Scroll Here in the shortcut 
    /// menu of the ScrollBar. This movement corresponds to the ScrollHereCommand. To view the 
    /// shortcut menu, right-click the mouse when the pointer is over the ScrollBar.   
    ScrollEventType_ThumbPosition,
    /// The Thumb was dragged and caused a MouseMove event. A Scroll event of this ScrollEventType
    /// may occur more than one time when the Thumb is dragged in the ScrollBar. 
    ScrollEventType_ThumbTrack 
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ScrollEventArgs
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ScrollEventArgs: public RoutedEventArgs
{
    /// Gets a value that represents the new location of the Thumb in the ScrollBar. 
    NsFloat32 newValue;
    
    /// Gets the ScrollEventType enumeration value that describes the change in the Thumb position 
    /// that caused this event.
    ScrollEventType scrollEventType;
    
    ScrollEventArgs(Core::BaseComponent* s, NsFloat32 value, ScrollEventType type);
};

typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const ScrollEventArgs&)> 
    ScrollEventHandler;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that provides a scroll bar that has a sliding Thumb whose position 
/// corresponds to a value.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.scrollbar.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ScrollBar: public RangeBase
{
public:
    ScrollBar();
    ~ScrollBar();

    /// Gets or sets whether the ScrollBar is displayed horizontally or vertically. 
    //@{
    Orientation GetOrientation() const;
    void SetOrientation(Orientation orientation);
    //@}

    /// Gets or sets the amount of the scrollable content that is currently visible.
    //@{
    NsFloat32 GetViewportSize() const;
    void SetViewportSize(NsFloat32 size);
    //@}

    /// Gets the Track for a ScrollBar control
    Track* GetTrack() const;

    /// Occurs one or more times as content scrolls in a ScrollBar when the user moves the Thumb by
    /// using the mouse
    UIElement::RoutedEvent_<ScrollEventHandler> Scroll();

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* OrientationProperty;
    static const DependencyProperty* ViewportSizeProperty;
    //@}

    /// Routed Events
    //@{
    static const RoutedEvent* ScrollEvent;
    //@}

    /// Routed Commands
    //@{
    static const RoutedCommand* DeferScrollToHorizontalOffsetCommand;
    static const RoutedCommand* DeferScrollToVerticalOffsetCommand;
    static const RoutedCommand* LineDownCommand;
    static const RoutedCommand* LineLeftCommand;
    static const RoutedCommand* LineRightCommand;
    static const RoutedCommand* LineUpCommand;
    static const RoutedCommand* PageDownCommand;
    static const RoutedCommand* PageLeftCommand;
    static const RoutedCommand* PageRightCommand;
    static const RoutedCommand* PageUpCommand;
    static const RoutedCommand* ScrollHereCommand;
    static const RoutedCommand* ScrollToBottomCommand;
    static const RoutedCommand* ScrollToEndCommand;
    static const RoutedCommand* ScrollToHomeCommand;
    static const RoutedCommand* ScrollToHorizontalOffsetCommand;
    static const RoutedCommand* ScrollToLeftEndCommand;
    static const RoutedCommand* ScrollToRightEndCommand;
    static const RoutedCommand* ScrollToTopCommand;
    static const RoutedCommand* ScrollToVerticalOffsetCommand;
    //@}

protected:
    /// From Control
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    //@}
    
    /// From FrameworkElement
    //@{
    void OnTemplatedParentChanged(FrameworkElement* oldParent, FrameworkElement* newParent);
    //@}

    /// From UIElement
    //@{
    NsBool IsEnabledCore() const;
    void OnPreviewMouseLeftButtonDown(const MouseButtonEventArgs& e);
    //@}

private:
    void OnThumbDragStarted(Core::BaseComponent* sender, const DragStartedEventArgs& e);
    void OnThumbDragDelta(Core::BaseComponent* sender, const DragDeltaEventArgs& e);
    void OnThumbDragCompleted(Core::BaseComponent* sender, const DragCompletedEventArgs& e);
    
    void RegisterDelegates();
    void FreeDelegates();

    void LineLeft();
    void LineRight();
    void LineDown();
    void LineUp();
    void SmallDecrement();
    void SmallIncrement();

    void PageLeft();
    void PageRight();
    void PageDown();
    void PageUp();
    void LargeDecrement();
    void LargeIncrement();

    void ScrollToLeftEnd();
    void ScrollToRightEnd();
    void ScrollToBottom();
    void ScrollToTop();
    void ToMinimum();
    void ToMaximum();

    NsBool IsStandalone() const;

    static void OnCanScrollCommand(Core::BaseComponent* o, const CanExecuteRoutedEventArgs& e);
    static void OnScrollCommand(Core::BaseComponent* o, const ExecutedRoutedEventArgs& e);

private:
    Ptr<Track> mTrack;
    ScrollViewer* mScrollViewerOwner;
    NsBool mHasScrolled;

    NS_DECLARE_REFLECTION(ScrollBar, RangeBase)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
