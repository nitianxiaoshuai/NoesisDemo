////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MOUSE_H__
#define __GUI_MOUSE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/InputEnums.h>
#include <NsCore/Delegate.h>
#include <NsCore/Ptr.h>
#include <NsCore/Vector.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsDrawing/Point.h>


NS_IFORWARD(Gui, IUITreeNode)
NS_CFORWARD(Gui, View)
NS_CFORWARD(Gui, DependencyObject)
NS_CFORWARD(Gui, UIElement)
NS_CFORWARD(Gui, FrameworkElement)
NS_CFORWARD(Gui, ToolTip)
NS_CFORWARD(Gui, RoutedEvent)
NS_SFORWARD(Gui, RoutedEventArgs)
NS_SFORWARD(Gui, DependencyPropertyChangedEventArgs)


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum CaptureMode
{
    /// No mouse capture. Mouse input goes to the element under the mouse
    CaptureMode_None,

    /// Mouse capture is applied to a single element. Mouse input goes to the captured element
    CaptureMode_Element,

    /// Mouse capture is applied to a subtree of elements. If the mouse is over a child of the
    /// element with capture, mouse input is sent to the child element. Otherwise, mouse input is
    /// sent to the element with mouse capture
    CaptureMode_SubTree
};

typedef Noesis::Core::Delegate<void (UIElement*)> DirectlyOverChangedEvent;
typedef NsVector< Ptr<UIElement> > ParentElementList;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the mouse device.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Mouse: public Core::BaseComponent
{
public:
    Mouse(View* view);
    ~Mouse();

    /// Resets mouse state
    void ResetState();

    /// Gets last mouse position
    Drawing::Pointi GetPosition() const;

    /// Gets the mouse position relative to the specified element
    static Drawing::Point GetPosition(UIElement* relativeTo);

    /// Gets the state of any mouse button
    MouseButtonState GetButtonState(MouseButton button) const;

    /// Tries to capture the mouse for the specified element
    NsBool Capture(UIElement* element, CaptureMode mode = CaptureMode_Element);

    /// Gets the captured mouse element
    UIElement* GetCaptured() const;

    /// Occurs when the element returned in a hit test corresponding to the position of the mouse
    /// pointer changes
    DirectlyOverChangedEvent& DirectlyOverChanged();

public:
    /// Attached routed events
    //@{
    static const RoutedEvent* GotMouseCaptureEvent;
    static const RoutedEvent* LostMouseCaptureEvent;
    static const RoutedEvent* MouseDownEvent;
    static const RoutedEvent* MouseEnterEvent;
    static const RoutedEvent* MouseLeaveEvent;
    static const RoutedEvent* MouseMoveEvent;
    static const RoutedEvent* MouseUpEvent;
    static const RoutedEvent* MouseWheelEvent;
    static const RoutedEvent* PreviewMouseDownEvent;
    static const RoutedEvent* PreviewMouseMoveEvent;
    static const RoutedEvent* PreviewMouseUpEvent;
    static const RoutedEvent* PreviewMouseWheelEvent;
    static const RoutedEvent* QueryCursorEvent;
    //@}

private:
    friend class View;
    friend class ViewLayout;
    friend class UIElement;

    void ResetDirectlyOver();

    /// Indicates if mouse requires to refresh over/captured element state
    NsBool NeedsUpdate() const;
    void Update();

    void ButtonDown(NsInt x, NsInt y, MouseButton button);
    void ButtonUp(NsInt x, NsInt y, MouseButton button);
    void DoubleClick(NsInt x, NsInt y, MouseButton button);
    void Move(NsInt x, NsInt y);
    void Wheel(NsInt x, NsInt y, NsInt wheelRotation);

    void SetOver(UIElement* uiElement);

    void OnLastPressedControlDestroyed(DependencyObject* dob);

    void DirectlyOverModified(Core::BaseComponent* source, 
        const DependencyPropertyChangedEventArgs& args);
    void UpdateOver();

    void OnCapturedIsEnabledChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);
    void OnCapturedIsVisibleChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);
    void OnCapturedIsHitTestVisibleChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);
    void UpdateCaptured();

    void RegisterCaptured();
    void UnregisterCaptured();

    void OpenContextMenu(UIElement* element, const Drawing::Point& mousePosition);
    void OnContextMenuClosed(Core::BaseComponent* sender, const RoutedEventArgs& args);

    void OpenToolTip(UIElement* element);
    void TryOpenToolTip();
    void TryCloseToolTip();
    void OnToolTipClosed(Core::BaseComponent* sender, const RoutedEventArgs& args);
    void CancelToolTipTimer();
    void ResetToolTip();

    void RegisterToolTipOwner(UIElement* owner);
    void UnregisterToolTipOwner();
    void OnToolTipOwnerHidden(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);
    void OnToolTipOwnerDestroyed(DependencyObject* obj);

    NsUInt32 OnToolTipInitialTimeElapsed(void* state = 0);
    NsUInt32 OnToolTipDurationTimeElapsed(void* state = 0);
    NsUInt32 OnToolTipBetweenTimeElapsed(void* state = 0);

    UIElement* HitTest(const Drawing::Point& point) const;

    void UpdatePosition(NsInt x, NsInt y);
    NsBool UpdateButton(MouseButton button, MouseButtonState state);

private:
    View* mView;

    // Last mouse state
    Drawing::Point mPosition;
    
    static const NsSize NumButtons = 5;
    MouseButtonState mButtonStates[NumButtons];

    typedef NsVector<Ptr<UIElement> > Elements;

    // Captured element
    Ptr<UIElement> mCaptured;
    Elements mCaptureWithinElements;
    CaptureMode mCaptureMode;

    // Last top element under the mouse
    Ptr<UIElement> mDirectlyOver;
    Elements mOverElements;
    DirectlyOverChangedEvent mDirectlyOverChangedEvent;

    // Filled by ButtonDown() and reused by DoubleClick()
    UIElement* mLastPressedControl;

    IUITreeNode* mContextMenuOwner;

    // TODO: Move this management to ToolTipService
    //@{
    FrameworkElement* mLastToolTipOwner;
    Ptr<ToolTip> mToolTip;
    NsUInt32 mToolTipTimer;
    //@}

    union
    {
        struct
        {
            NsBool capturedRegistered : 1;
            NsBool contextMenuOpened : 1;
            NsBool toolTipOwn : 1;
            NsBool toolTipBetween : 1;
            NsBool toolTipTimerCreated : 1;
            NsBool needsUpdateOver : 1;
            NsBool needsUpdateCaptured : 1;
        } mFlags;

        // To quickly set all flags to 0
        NsUInt32 mAllFlags;
    };

    NS_DECLARE_REFLECTION(Mouse, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
