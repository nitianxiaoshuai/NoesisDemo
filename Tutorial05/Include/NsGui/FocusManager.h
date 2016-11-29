////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FOCUSMANAGER_H__
#define __GUI_FOCUSMANAGER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>


namespace Noesis
{
// Forward declarations
//@{
namespace Core
{
template<class T> class Ptr;
}
using Core::Ptr;
namespace Gui
{
class DependencyObject;
class DependencyProperty;
class RoutedEvent;
class UIElement;
}
//@}

namespace Gui
{

class NS_GUI_CORE_API FocusManager
{
public:
    /// Gets or sets the element with logical focus within the specified focus scope
    //@{
    static UIElement* GetFocusedElement(DependencyObject* element);
    static void SetFocusedElement(DependencyObject* element, UIElement* value);
    //@}

    /// Determines the closest ancestor of the specified element that has IsFocusScope set to true
    static DependencyObject* GetFocusScope(DependencyObject* element);

    /// Determines whether the specified DependencyObject is a focus scope
    //@{
    static NsBool GetIsFocusScope(DependencyObject* element);
    static void SetIsFocusScope(DependencyObject* element, NsBool value);
    //@}

    /// Dependency properties
    //@{
    static const DependencyProperty* FocusedElementProperty;
    static const DependencyProperty* IsFocusScopeProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* LostFocusEvent;
    static const RoutedEvent* GotFocusEvent;
    //@}

private:
    FocusManager();

    NS_DECLARE_REFLECTION(FocusManager, Core::NoParent)
};

}
}

#endif