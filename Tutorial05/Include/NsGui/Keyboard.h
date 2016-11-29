////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_KEYBOARD_H__
#define __GUI_KEYBOARD_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IView.h>
#include <NsCore/Ptr.h>
#include <NsCore/Vector.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class View;
class UIElement;
class RoutedEvent;
class KeyboardNavigation;
typedef NsVector< Ptr<UIElement> > ParentElementList;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the keyboard device.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Keyboard: public Core::BaseComponent
{
public:
    Keyboard(View* view);
    ~Keyboard();

    /// Resets keyboard state
    void ResetState();

    /// Gets the set of ModifierKeys that are currently pressed
    NsUInt32 GetModifiers() const;

    /// Gets the set of key states for the specified key
    NsUInt32 GetKeyStates(Key key) const;

    /// Determines whether the specified key is pressed
    NsBool IsKeyDown(Key key) const;

    /// Determines whether the specified key is released
    NsBool IsKeyUp(Key key) const;

    /// Determines whether the specified key is toggled
    NsBool IsKeyToggled(Key key) const;

    /// Gets the element that has keyboard focus
    UIElement* GetFocused() const;

    /// Sets keyboard focus on the specified element
    /// \return The element that has focus after calling the function. May be an element other than
    /// that specified, even a null element
    UIElement* Focus(UIElement* element);

public:
    /// Attached routed events
    //@{
    static const RoutedEvent* GotKeyboardFocusEvent;
    static const RoutedEvent* KeyDownEvent;
    static const RoutedEvent* KeyUpEvent;
    static const RoutedEvent* LostKeyboardFocusEvent;
    static const RoutedEvent* PreviewGotKeyboardFocusEvent;
    static const RoutedEvent* PreviewKeyDownEvent;
    static const RoutedEvent* PreviewKeyUpEvent;
    static const RoutedEvent* PreviewLostKeyboardFocusEvent;
    //@}

private:
    friend class View;

    void Char(NsUInt32 ch);
    void KeyDown(Key key);
    void KeyUp(Key key);

    void UpdateKey(Key key, NsBool isKeyDown);

    friend class FrameworkElement;
    KeyboardNavigation* GetKeyboardNavigation() const;

private:
    // Last keyboard key states
    NsUInt32 mKeyStates[Key_Count];

    Ptr<UIElement> mFocusedElement;

    typedef NsVector<Ptr<UIElement> > Elements;
    Elements mFocusWithinElements;

    Ptr<KeyboardNavigation> mKeyboardNavigation;

    NsBool mKeyDownHandled;

    NS_DECLARE_REFLECTION(Keyboard, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
