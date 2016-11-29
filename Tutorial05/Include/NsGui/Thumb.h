////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_THUMB_H__
#define __GUI_THUMB_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Control.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DragCompletedEventArgs
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API DragCompletedEventArgs: public RoutedEventArgs
{
    /// Gets whether the drag operation for a Thumb was canceled by a call to the CancelDrag method
    NsBool canceled;
    /// Gets horizontal change in position of the Thumb after the user drags the control with mouse
    NsFloat32 horizontalChange;
    /// Gets vertical change in position of the Thumb after the user drags the control with mouse
    NsFloat32 verticalChange;

    DragCompletedEventArgs(Core::BaseComponent* s, NsBool c, NsFloat32 h, NsFloat32 v);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DragStartedEventArgs
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API DragStartedEventArgs: public RoutedEventArgs
{
    /// Gets the horizontal offset of the mouse click relative to the screen coordinates of Thumb
    NsFloat32 horizontalOffset;
    /// Gets the vertical offset of the mouse click relative to the screen coordinates of the Thumb
    NsFloat32 verticalOffset;
    
    DragStartedEventArgs(Core::BaseComponent* s, NsFloat32 h, NsFloat32 v);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DragDeltaEventArgs
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API DragDeltaEventArgs: public RoutedEventArgs
{
    /// Gets horizontal change in position of the Thumb after the user drags the control with mouse
    NsFloat32 horizontalChange;
    /// Gets vertical change in position of the Thumb after the user drags the control with mouse
    NsFloat32 verticalChange;

    DragDeltaEventArgs(Core::BaseComponent* s, NsFloat32 h, NsFloat32 v);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const DragCompletedEventArgs&)> 
    DragCompletedEventHandler;

typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const DragStartedEventArgs&)> 
    DragStartedEventHandler;

typedef Noesis::Core::Delegate<void (Core::BaseComponent*, const DragDeltaEventArgs&)> 
    DragDeltaEventHandler;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that can be dragged by the user.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.thumb.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Thumb: public Control
{
public:
    /// Constructor
    Thumb();

    /// Gets whether the Thumb control has logical focus and mouse capture and the left mouse
    /// button is pressed
    NsBool GetIsDragging() const;

    /// Cancels current dragging operation
    void CancelDrag();

    /// Occurs when the Thumb control loses mouse capture
    UIElement::RoutedEvent_<DragCompletedEventHandler> DragCompleted();

    /// Occurs one or more times as the mouse changes position when a Thumb control has logical
    /// focus and mouse capture
    UIElement::RoutedEvent_<DragDeltaEventHandler> DragDelta();

    /// Occurs when a Thumb control receives logical focus and mouse capture
    UIElement::RoutedEvent_<DragStartedEventHandler> DragStarted();

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* IsDraggingProperty;
    //@}

    /// Dependency events
    //@{
    static const RoutedEvent* DragCompletedEvent;
    static const RoutedEvent* DragDeltaEvent;
    static const RoutedEvent* DragStartedEvent;
    //@}
    
protected:
    
    /// Responds to a change in the value of the IsDragging property
    virtual void OnDraggingChanged(const DependencyPropertyChangedEventArgs& e);
    
    /// From Control
    //@{
    void UpdateVisualStates();
    //@}
    
    /// From FrameworkElement
    //@{
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    //@}
    
    /// From UIElement
    //@{
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e);
    void OnMouseMove(const MouseEventArgs& e);
    //@}
    
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    Drawing::Point mStartThumbPosition;
    Drawing::Point mStartScreenPosition;
    Drawing::Point mCurrentScreenPosition;

    NS_DECLARE_REFLECTION(Thumb, Control)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
