////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_UIELEMENTEVENTARGS_H__
#define __GUI_UIELEMENTEVENTARGS_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/RoutedEvent.h>
#include <NsGui/InputEnums.h>
#include <NsCore/Ptr.h>
#include <NsCore/String.h>
#include <NsDrawing/Point.h>
#include <NsDrawing/Size.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Gui
{
class UIElement;
class Visual;
struct MouseState;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// MouseEventArgs.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API MouseEventArgs: public RoutedEventArgs
{
    Drawing::Point position;
    MouseButtonState leftButton;
    MouseButtonState middleButton;
    MouseButtonState rightButton;
    MouseButtonState xButton1Button;
    MouseButtonState xButton2Button;

    MouseEventArgs(Core::BaseComponent* s, const RoutedEvent* e, const MouseState& mouseState);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// MouseButtonEventArgs.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API MouseButtonEventArgs: public MouseEventArgs
{
    MouseButton changedButton;
    MouseButtonState buttonState;
    NsUInt buttonClicks;

    MouseButtonEventArgs(Core::BaseComponent* s, const RoutedEvent* e, const MouseState& mouseState,
        MouseButton button, MouseButtonState state, NsUInt clicks);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// MouseWheelEventArgs.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API MouseWheelEventArgs: public MouseEventArgs
{
    NsInt wheelRotation;

    MouseWheelEventArgs(Core::BaseComponent* s, const RoutedEvent* e, const MouseState& mouseState,
        NsInt delta);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TouchEventArgs.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API TouchEventArgs: public RoutedEventArgs
{
    Drawing::Point touchPoint;
    NsUInt32 touchDevice;

    TouchEventArgs(Core::BaseComponent* s, const RoutedEvent* e, const Drawing::Point& touchPoint,
        NsUInt32 touchDevice);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies how manipulation events are interpreted
////////////////////////////////////////////////////////////////////////////////////////////////////
enum ManipulationModes
{
    /// Manipulation events do not occur
    ManipulationModes_None = 0,
    /// A manipulation can rotate an object
    ManipulationModes_Rotate = 1,
    /// A manipulation can scale an object
    ManipulationModes_Scale = 2,
    /// A manipulation can translate an object horizontally
    ManipulationModes_TranslateX = 4,
    /// A manipulation can translate an object vertically.
    ManipulationModes_TranslateY = 8,
    /// A manipulation can translate an object.
    ManipulationModes_Translate = ManipulationModes_TranslateX | ManipulationModes_TranslateY,
    /// A manipulation can scale, translate, or rotate an object
    ManipulationModes_All = ManipulationModes_Rotate | ManipulationModes_Scale |
        ManipulationModes_Translate
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the ManipulationStarting event 
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ManipulationStartingEventArgs: public RoutedEventArgs
{
    /// The container that all manipulation events and calculations are relative to
    mutable Visual* manipulationContainer;
    /// Which types of manipulations are possible
    mutable ManipulationModes mode;
    /// Cancels the manipulation and promotes touch to mouse events
    mutable NsBool cancel;

    ManipulationStartingEventArgs(Core::BaseComponent* s, const RoutedEvent* e,
        Visual* manipulationContainer);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the ManipulationStarted event
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ManipulationStartedEventArgs: public RoutedEventArgs
{
    /// The container that the manipulationOrigin member is relative to
    Visual* manipulationContainer;
    /// The point from which the manipulation originated
    Drawing::Point manipulationOrigin;
    /// Cancels the manipulation
    mutable NsBool cancel;
    /// Completes the manipulation without inertia
    mutable NsBool complete;
    
    ManipulationStartedEventArgs(Core::BaseComponent* s, const RoutedEvent* e,
        Visual* manipulationContainer, const Drawing::Point& manipulationOrigin);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Contains transformation data that is accumulated when manipulation events occur
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ManipulationDelta
{
    /// The amount the manipulation has resized in pixels
    Drawing::Point expansion;
    /// The rotation of the manipulation in degrees
    NsFloat32 rotation;
    /// The amount the manipulation has resized as a multiplier
    NsFloat32 scale;
    /// The linear motion of the manipulation in pixels
    Drawing::Point translation;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes the speed at which manipulations occurs
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ManipulationVelocities
{
    /// The speed of rotation in degrees per millisecond
    NsFloat32 angularVelocity;
    /// The rate at which the manipulation is resized in pixels per millisecond
    Drawing::Point expansionVelocity;
    /// The speed of linear motion in pixels per millisecond
    Drawing::Point linearVelocity;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the ManipulationDelta event
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ManipulationDeltaEventArgs: public RoutedEventArgs
{
    /// The container that defines the coordinates for the manipulation
    Visual* manipulationContainer;
    /// The point from which the manipulation originated
    Drawing::Point manipulationOrigin;
    /// The most recent changes of the current manipulation
    ManipulationDelta deltaManipulation;
    /// The cumulated changes of the current manipulation
    ManipulationDelta cumulativeManipulation;
    /// The rates of the most recent changes to the manipulation
    ManipulationVelocities velocities;
    /// Indicates whether the ManipulationDelta event occurs during inertia
    NsBool isInertial;
    /// Cancels the manipulation
    mutable NsBool cancel;
    /// Completes the manipulation without inertia
    mutable NsBool complete;
    
    ManipulationDeltaEventArgs(Core::BaseComponent* s, const RoutedEvent* e,
        Visual* manipulationContainer, const Drawing::Point& manipulationOrigin,
        const ManipulationDelta& deltaManipulation, const ManipulationDelta& cumulativeManipulation,
        const ManipulationVelocities& velocities, NsBool isInertial);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Controls the deceleration of a resizing manipulation during inertia
////////////////////////////////////////////////////////////////////////////////////////////////////
struct InertiaExpansionBehavior
{
    /// The rate that resizing slows in pixels per square milliseconds
    NsFloat32 desiredDeceleration;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Controls the deceleration of a rotation manipulation during inertia
////////////////////////////////////////////////////////////////////////////////////////////////////
struct InertiaRotationBehavior
{
    /// The rate the rotation slows in degrees per squared millisecond
    NsFloat32 desiredDeceleration;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Controls deceleration on a translation manipulation during inertia
////////////////////////////////////////////////////////////////////////////////////////////////////
struct InertiaTranslationBehavior
{
    /// The rate the linear movement slows in pixels per squared millisecond
    NsFloat32 desiredDeceleration;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the ManipulationInertiaStarting event
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ManipulationInertiaStartingEventArgs: public RoutedEventArgs
{
    /// The container that the ManipulationOrigin property is relative to
    Visual* manipulationContainer;
    /// The point from which the manipulation originated
    Drawing::Point manipulationOrigin;
    /// The rates of changes to the manipulation that occur before inertia starts
    mutable ManipulationVelocities initialVelocities;
    /// The rate of slowdown of rotational inertial movement
    mutable InertiaRotationBehavior rotationBehavior;
    /// The rate of slowdown of expansion inertial movement
    mutable InertiaExpansionBehavior expansionBehavior;
    /// The rate of slowdown of linear inertial movement
    mutable InertiaTranslationBehavior translationBehavior;
    /// Cancels the manipulation
    mutable NsBool cancel;
    
    ManipulationInertiaStartingEventArgs(Core::BaseComponent* s, const RoutedEvent* e,
        Visual* manipulationContainer, const Drawing::Point& manipulationOrigin,
        const ManipulationVelocities& initialVelocities);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the ManipulationCompleted event
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ManipulationCompletedEventArgs: public RoutedEventArgs
{
    /// The container that defines the coordinates for the manipulation
    Visual* manipulationContainer;
    /// The point from which the manipulation originated
    Drawing::Point manipulationOrigin;
    /// The velocities that are used for the manipulation
    ManipulationVelocities finalVelocities;
    /// The total transformation that occurs during the current manipulation
    ManipulationDelta totalManipulation; 
    /// Indicates whether the ManipulationDelta event occurs during inertia
    NsBool isInertial;
    /// Cancels the manipulation
    mutable NsBool cancel;
    
    ManipulationCompletedEventArgs(Core::BaseComponent* s, const RoutedEvent* e,
        Visual* manipulationContainer, const Drawing::Point& manipulationOrigin,
        const ManipulationVelocities& finalVelocities, const ManipulationDelta& totalManipulation,
        NsBool isInertial);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides information for access keys events.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API AccessKeyEventArgs: public EventArgs
{
    /// Gets a value that indicates whether other elements are invoked by the key.
    NsBool isMultiple;

    /// Gets the access keys that was pressed.
    NsString key;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for LostKeyboardFocus and GotKeyboardFocus routed events, as well as related 
/// attached and Preview events.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API KeyboardFocusChangedEventArgs: public RoutedEventArgs
{
    /// Gets the element that previously had focus.
    UIElement* oldFocus;

    /// Gets the element that focus has moved to.
    UIElement* newFocus;

    /// Constructor
    KeyboardFocusChangedEventArgs(Core::BaseComponent* s, const RoutedEvent* e, UIElement* o,
        UIElement* n);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the KeyUp and KeyDown routed events, as well as related attached and Preview 
/// events.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API KeyEventArgs: public RoutedEventArgs
{
    // TODO
    Key deadCharProcessedKey;

    /// Gets the keyboard key referenced by the event, if the key will be processed by an Input 
    /// Method Editor (IME).
    // TODO
    Key imeProcessedKey;

    /// Gets the keyboard key associated with the event.
    Key key;

    /// Gets the state of the keyboard key associated with this event.
    NsUInt32 keyStates;

    /// Gets the keyboard key referenced by the event, if the key will be processed by the system.
    // TODO
    Key systemKey;

    /// Constructor
    KeyEventArgs(Core::BaseComponent* s, const RoutedEvent* e, Key key, NsUInt32 keyStates);

    /// Gets a value that indicates whether the key referenced by the event is in the down state.
    NsBool GetIsDown() const;

    /// Gets a value that indicates whether the keyboard key referenced by the event is a 
    /// repeated key.
    NsBool GetIsRepeat() const;

    /// Gets a value that indicates whether the key referenced by the event is in the toggled state.
    NsBool GetIsToggled() const;

    /// Gets a value that indicates whether the key referenced by the event is in the up state.
    NsBool GetIsUp() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Contains arguments associated with changes to a TextComposition.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API TextCompositionEventArgs: public RoutedEventArgs
{
    /// Gets control text associated with a TextComposition event.
    //NsString controlText;

    /// Gets system text associated with a TextComposition event.
    //NsString systemText;

    /// Gets input text associated with a TextComposition event.
    //NsString text;

    /// Gets the System.Windows.Input.TextComposition associated with a TextComposition event.
    //TextComposition textComposition;
    NsUInt32 ch;

    /// Constructor
    TextCompositionEventArgs(Core::BaseComponent* s, const RoutedEvent* e, NsUInt32 ch);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the direction within a user interface (UI) in which a desired focus change request is 
/// attempted. The direction is either based on tab order or by relative direction in layout.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FocusNavigationDirection
{
    /// Move focus to the next focusable element in tab order. Not supported for PredictFocus. 
    FocusNavigationDirection_Next,

    /// Move focus to the previous focusable element in tab order. Not supported for PredictFocus. 
    FocusNavigationDirection_Previous,

    /// Move focus to the first focusable element in tab order. Not supported for PredictFocus. 
    FocusNavigationDirection_First,

    /// Move focus to the last focusable element in tab order. Not supported for PredictFocus. 
    FocusNavigationDirection_Last,

    /// Move focus to another focusable element to the left of the currently focused element. 
    FocusNavigationDirection_Left,

    /// Move focus to another focusable element to the right of the currently focused element. 
    FocusNavigationDirection_Right,

    /// Move focus to another focusable element upwards from the currently focused element. 
    FocusNavigationDirection_Up,

    /// Move focus to another focusable element downwards from the currently focused element. 
    FocusNavigationDirection_Down
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a request to move focus to another control. 
////////////////////////////////////////////////////////////////////////////////////////////////////
struct TraversalRequest
{
    /// Gets the traversal direction.
    FocusNavigationDirection focusNavigationDirection;

    /// Gets or sets a value that indicates whether focus traversal has reached the end of child 
    /// elements that can have focus.
    NsBool wrapped;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
