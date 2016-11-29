////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SCROLLVIEWER_H__
#define __GUI_SCROLLVIEWER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ContentControl.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
NS_INTERFACE IScrollInfo;
enum Visibility;
enum ScrollBarVisibility;
class ScrollBar;
struct RequestBringIntoViewEventArgs;
struct CanExecuteRoutedEventArgs;
struct ExecutedRoutedEventArgs;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ScrollChangedEventArgs
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ScrollChangedEventArgs: public RoutedEventArgs
{
    /// Gets the updated height of the ScrollViewerextent.
    NsFloat32 extentHeight;
    /// Gets a value that indicates the change in height of the ScrollViewerextent.
    NsFloat32 extentHeightChange;
    /// Gets the updated width of the ScrollViewerextent.
    NsFloat32 extentWidth;
    /// Gets a value that indicates the change in width of the ScrollViewerextent.
    NsFloat32 extentWidthChange;
    /// Gets a value that indicates the change in horizontal offset for a ScrollViewer.
    NsFloat32 horizontalChange;
    /// Gets the updated horizontal offset value for a ScrollViewer.
    NsFloat32 horizontalOffset;
    /// Gets a value that indicates the change in vertical offset of a ScrollViewer.
    NsFloat32 verticalChange;
    /// Gets the updated value of the vertical offset for a ScrollViewer.
    NsFloat32 verticalOffset;
    /// Gets the updated value of the viewport height for a ScrollViewer
    NsFloat32 viewportHeight;
    /// Gets a value that indicates the change in value of the viewport height for ScrollViewer
    NsFloat32 viewportHeightChange;
    /// Gets the updated value of the viewport width for a ScrollViewer.
    NsFloat32 viewportWidth;
    /// Gets a value that indicates the change in viewport width of a ScrollViewer.
    NsFloat32 viewportWidthChange;

    ScrollChangedEventArgs(Core::BaseComponent* s);
};

/// Specifies how ScrollViewer reacts to touch manipulation
enum PanningMode
{
    /// The ScrollViewer scrolls horizontally and vertically
    PanningMode_Both,
    /// The ScrollViewer scrolls when the user moves a finger horizontally first. If the user moves
    /// the vertically first, the movement is treated as mouse events. After the ScrollViewer begins
    /// to scroll, it will scroll horizontally and vertically
    PanningMode_HorizontalFirst,
    /// The ScrollViewer scrolls horizontally only
    PanningMode_HorizontalOnly,
    /// The ScrollViewer does not respond to touch input
    PanningMode_None,
    /// The ScrollViewer scrolls when the user moves a finger vertically first. If the user moves
    /// the horizontally first, the movement is treated as mouse events. After the ScrollViewer begins
    /// to scroll, it will scroll horizontally and vertically
    PanningMode_VerticalFirst,
    /// The ScrollViewer scrolls vertically only
    PanningMode_VerticalOnly
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const ScrollChangedEventArgs&)> 
    ScrollChangedEventHandler;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a scrollable area that can contain other visible elements.
///
/// http://msdn.microsoft.com/en-us/library/ms612678.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ScrollViewer: public ContentControl
{
public:
    /// Constructor
    ScrollViewer();
    
    /// Destructor
    ~ScrollViewer();

    /// Gets a value that indicates whether elements that support the IScrollInfo interface are
    /// allowed to scroll
    static NsBool GetCanContentScroll(const DependencyObject* element);
    /// Sets a value that indicates whether elements that support the IScrollInfo interface are
    /// allowed to scroll
    static void SetCanContentScroll(DependencyObject* element, NsBool canScroll);

    /// Gets a value that indicates whether a horizontal ScrollBar should be displayed
    static ScrollBarVisibility GetHorizontalScrollBarVisibility(const DependencyObject* element);
    /// Sets a value that indicates whether a horizontal ScrollBar should be displayed
    static void SetHorizontalScrollBarVisibility(DependencyObject* element,
        ScrollBarVisibility visibility);

    /// Gets a value that indicates whether a vertical ScrollBar should be displayed
    static ScrollBarVisibility GetVerticalScrollBarVisibility(const DependencyObject* element);
    /// Sets a value that indicates whether a vertical ScrollBar should be displayed
    static void SetVerticalScrollBarVisibility(DependencyObject* element,
        ScrollBarVisibility visibility);

    /// Gets a value that indicates whether the ScrollViewer should scroll contents immediately
    /// during a thumb drag or defer until a drag completes
    static NsBool GetIsDeferredScrollingEnabled(const DependencyObject* element);
    /// Sets a value that indicates whether the ScrollViewer should scroll contents immediately
    /// during a thumb drag or defer until a drag completes
    static void SetIsDeferredScrollingEnabled(DependencyObject* element, NsBool value);

    /// Gets the way ScrollViewer reacts to touch manipulation
    static PanningMode GetPanningMode(const DependencyObject* element);
    /// Sets the way ScrollViewer reacts to touch manipulation
    static void SetPanningMode(DependencyObject* element, PanningMode panningMode);

    /// Gets the rate ScrollViewer slows in pixel per squared millisecond when in inertia
    static NsFloat32 GetPanningDeceleration(const DependencyObject* element);
    /// Sets the rate ScrollViewer slows in pixel per squared millisecond when in inertia
    static void SetPanningDeceleration(DependencyObject* element, NsFloat32 deceleration);

    /// Gets the ratio of scrolling offset to translate manipulation offset
    static NsFloat32 GetPanningRatio(const DependencyObject* element);
    /// Sets the ratio of scrolling offset to translate manipulation offset
    static void SetPanningRatio(DependencyObject* element, NsFloat32 panningRatio);

    /// Gets or sets a value that indicates whether elements that support the IScrollInfo interface
    /// are allowed to scroll
    //@}
    NsBool GetCanContentScroll() const;
    void SetCanContentScroll(NsBool canScroll);
    //@}

    /// Gets or sets a value that indicates whether a horizontal ScrollBar should be displayed
    //@{
    ScrollBarVisibility GetHorizontalScrollBarVisibility() const;
    void SetHorizontalScrollBarVisibility(ScrollBarVisibility visibility);
    //@}

    /// Gets or sets a value that indicates whether a vertical ScrollBar should be displayed
    //@{
    ScrollBarVisibility GetVerticalScrollBarVisibility() const;
    void SetVerticalScrollBarVisibility(ScrollBarVisibility visibility);
    //@}

    /// Gets or sets a value that indicates whether the ScrollViewer should scroll contents
    /// immediately during a thumb drag or defer until a drag completes
    //@{
    NsBool GetIsDeferredScrollingEnabled() const;
    void SetIsDeferredScrollingEnabled(NsBool value);
    //@}

    /// Gets or sets the way ScrollViewer reacts to touch manipulation
    //@{
    PanningMode GetPanningMode() const;
    void SetPanningMode(PanningMode panningMode);
    //@}

    /// Gets or sets the rate ScrollViewer slows in pixel per squared millisecond when in inertia
    //@{
    NsFloat32 GetPanningDeceleration() const;
    void SetPanningDeceleration(NsFloat32 deceleration);
    //@}

    /// Gets or sets the ratio of scrolling offset to translate manipulation offset
    //@{
    NsFloat32 GetPanningRatio() const;
    void SetPanningRatio(NsFloat32 panningRatio);
    //@}

    /// Gets a value that indicates whether the horizontal ScrollBar is visible
    Visibility GetComputedHorizontalScrollBarVisibility() const;

    /// Gets a value that indicates whether the vertical ScrollBar is visible
    Visibility GetComputedVerticalScrollBarVisibility() const;

    /// Gets a value that contains the vertical size of the extent
    NsFloat32 GetExtentHeight() const;

    /// Gets a value that contains the horizontal size of the extent
    NsFloat32 GetExtentWidth() const;

    /// Gets a value that contains the horizontal offset of the scrolled content
    NsFloat32 GetHorizontalOffset() const;

    /// Gets a value that represents the vertical size of the content element that can be scrolled
    NsFloat32 GetScrollableHeight() const;

    /// Gets a value that represents the horizontal size of the content element that can be scrolled
    NsFloat32 GetScrollableWidth() const;

    /// Gets a value that contains the vertical offset of the scrolled content
    NsFloat32 GetVerticalOffset() const;

    /// Gets a value that contains the vertical size of the content's viewport
    NsFloat32 GetViewportHeight() const;

    /// Gets a value that contains the horizontal size of the content's viewport
    NsFloat32 GetViewportWidth() const;

    /// Scrolls left within content by one logical unit
    void LineLeft();

    /// Scrolls right within content by one logical unit
    void LineRight();

    /// Scrolls up within content by one logical unit
    void LineUp();

    /// Scrolls down within content by one logical unit
    void LineDown();

    /// Scrolls left within content by one page
    void PageLeft();

    /// Scrolls right within content by one page
    void PageRight();

    /// Scrolls up within content by one page
    void PageUp();

    /// Scrolls down within content by one page
    void PageDown();

    /// Horizontally scroll to the beginning of the content.
    void ScrollToLeftEnd();

    /// Horizontally scroll to the end of the content.
    void ScrollToRightEnd();

    /// Vertically scroll to the beginning of the content.
    void ScrollToTop();

    /// Vertically scroll to the end of the content.
    void ScrollToBottom();

    /// Scroll to Top-Left of the content.
    void ScrollToHome();

    /// Scroll to Bottom-Left of the content.
    void ScrollToEnd();

    /// Scrolls the content within the ScrollViewer to the specified horizontal offset position.
    void ScrollToHorizontalOffset(NsFloat32 offset);

    /// Scrolls the content within the ScrollViewer to the specified vertical offset position.
    void ScrollToVerticalOffset(NsFloat32 offset);

    /// Called by ScrollInfo object when any scrolling property changes
    void InvalidateScrollInfo();

    /// Notifies about changes in scroll position, extent, or viewport size
    UIElement::RoutedEvent_<ScrollChangedEventHandler> ScrollChanged();

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* CanContentScrollProperty;
    static const DependencyProperty* ComputedHorizontalScrollBarVisibilityProperty;
    static const DependencyProperty* ComputedVerticalScrollBarVisibilityProperty;
    static const DependencyProperty* ExtentHeightProperty;
    static const DependencyProperty* ExtentWidthProperty;
    static const DependencyProperty* HorizontalOffsetProperty;
    static const DependencyProperty* HorizontalScrollBarVisibilityProperty;
    static const DependencyProperty* IsDeferredScrollingEnabledProperty;
    static const DependencyProperty* ScrollableHeightProperty;
    static const DependencyProperty* ScrollableWidthProperty;
    static const DependencyProperty* VerticalOffsetProperty;
    static const DependencyProperty* VerticalScrollBarVisibilityProperty;
    static const DependencyProperty* ViewportHeightProperty;
    static const DependencyProperty* ViewportWidthProperty;
    static const DependencyProperty* PanningModeProperty;
    static const DependencyProperty* PanningDecelerationProperty;
    static const DependencyProperty* PanningRatioProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* ScrollChangedEvent;
    //@}

protected:
    /// Fires the ScrollChanged event. Inheritors should call base OnScrollChanged(e) if they want
    /// the event to be fired
    virtual void OnScrollChanged(const ScrollChangedEventArgs& e);

    /// From Control
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    void OnTemplatedParentChanged(FrameworkElement* oldParent, FrameworkElement* newParent);
    //@}

    /// From UIElement
    //@{
    void OnMouseWheel(const MouseWheelEventArgs& e);
    void OnManipulationStarting(const ManipulationStartingEventArgs& e);
    void OnManipulationDelta(const ManipulationDeltaEventArgs& e);
    void OnManipulationInertiaStarting(const ManipulationInertiaStartingEventArgs& e);
    void OnManipulationCompleted(const ManipulationCompletedEventArgs& e);
    //@}

    /// From DependencyProperty
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    friend class ScrollViewerTest;
    friend class ScrollContentPresenter;
    friend class TextContainer;
    friend class TextBox;

    // Gets or sets the element that implements the IScrollInfo interface and provides values for
    // scrolling properties of this ScrollViewer
    //@{
    IScrollInfo* GetScrollInfo() const;
    void SetScrollInfo(IScrollInfo* scrollInfo);
    //@}

    void DeferScrollToHorizontalOffset(NsFloat32 offset);
    void DeferScrollToVerticalOffset(NsFloat32 offset);

    void BindToTemplatedParent(const DependencyProperty* property);
    static void StaticOnRequestBringIntoView(BaseComponent* obj, const EventArgs& e);
    void OnRequestBringIntoView(const RequestBringIntoViewEventArgs& e);

    void AdjustOffsets(NsBool& fitsWidth, NsBool& fitsHeight);

    static void OnCanExecuteScrollCommand(BaseComponent* o, const CanExecuteRoutedEventArgs& e);
    static void OnScrollCommand(BaseComponent* o, const ExecutedRoutedEventArgs& e);

private:
    Ptr<ScrollBar> mHorizontalScrollBar;
    Ptr<ScrollBar> mVerticalScrollBar;
    Ptr<IScrollInfo> mScrollInfo;

    union
    {
        struct
        {
            NsBool measureInvalidated:1;
            NsBool launchScrollEvent:1;
            NsBool isTouchPanning:1;
            NsBool completeManipulation:1;
        } mFlags;

        // To quickly set all flags to 0
        NsUInt32 mAllFlags;
    };

    NS_DECLARE_REFLECTION(ScrollViewer, ContentControl)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::PanningMode)


#endif
