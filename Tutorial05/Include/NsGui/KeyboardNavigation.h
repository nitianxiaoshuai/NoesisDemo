////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_KEYBOARDNAVIGATION_H__
#define __GUI_KEYBOARDNAVIGATION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/UIElementEvents.h>
#include <NsGui/Enums.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclareEnum.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyObject;
class DependencyProperty;
class Visual;
class UIElement;
class FrameworkElement;
class Keyboard;
class FocusVisualLayer;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides logical and directional navigation between focusable objects.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.input.keyboardnavigation.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API KeyboardNavigation: public Core::BaseComponent
{
public:
    KeyboardNavigation();
    KeyboardNavigation(Keyboard* keyboard, Visual* root);
    ~KeyboardNavigation();

    /// Gets or sets the logical tab navigation behavior for the children of the element that this 
    /// property is set on.
    //@{
    static KeyboardNavigationMode GetTabNavigation(const DependencyObject* element);
    static void SetTabNavigation(DependencyObject* element, KeyboardNavigationMode mode);
    //@}

    /// Gets or sets the logical control tab navigation behavior for the children of the element
    /// that this property is set on.
    //@{
    static KeyboardNavigationMode GetControlTabNavigation(const DependencyObject* element);
    static void SetControlTabNavigation(DependencyObject* element, KeyboardNavigationMode mode);
    //@}
    
    /// Gets or sets the directional navigation behavior for the children of the element that this
    /// property is set on. 
    //@{
    static KeyboardNavigationMode GetDirectionalNavigation(const DependencyObject* element);
    static void SetDirectionalNavigation(DependencyObject* element, KeyboardNavigationMode mode);
    //@}

    /// Gets or sets a value indicating whether the Return character is accepted by a control.
    //@{
    static NsBool GetAcceptsReturn(const DependencyObject* element);
    static void SetAcceptsReturn(DependencyObject* element, NsBool value);
    //@}

    /// Gets or sets a value indicating whether the element that this property is set on is a tab
    /// stop.
    //@{
    static NsBool GetIsTabStop(const DependencyObject* element);
    static void SetIsTabStop(DependencyObject* element, NsBool value);
    //@}
    
    /// Gets or sets the tab index for the element that this property is set on. 
    //@{
    static NsInt32 GetTabIndex(const DependencyObject* element);
    static void SetTabIndex(DependencyObject* element, NsInt32 value);
    //@}

    NsBool MoveFocus(FrameworkElement* source, const TraversalRequest& request);
    FrameworkElement* PredictFocus(FrameworkElement* source, FocusNavigationDirection direction);

public:
    static const DependencyProperty* AcceptsReturnProperty; // Attached
    static const DependencyProperty* ControlTabNavigationProperty; // Attached
    static const DependencyProperty* DirectionalNavigationProperty; // Attached
    static const DependencyProperty* IsTabStopProperty; // Attached
    static const DependencyProperty* TabIndexProperty; // Attached
    static const DependencyProperty* TabNavigationProperty; // Attached

private:
    friend class Keyboard;
    void OnKeyDown(Key key);
    void OnFocused(UIElement* focusedElement);

    void UpdateFocus(FrameworkElement* newFocused);
    void UpdateDirectionalFocus(UIElement* focused, FocusNavigationDirection direction);

    void SetFocusStyle(FrameworkElement* focusedElement);
    void HideFocusStyle();

private:
    Keyboard* mKeyboard;
    Visual* mRoot;

    Ptr<FocusVisualLayer> mFocusVisualLayer;
    NsBool mKeyboardFocused;

    NS_DECLARE_REFLECTION(KeyboardNavigation, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
