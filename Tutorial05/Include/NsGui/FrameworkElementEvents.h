////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FRAMEWORKELEMENTEVENTARGS_H__
#define __GUI_FRAMEWORKELEMENTEVENTARGS_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/RoutedEvent.h>
#include <NsDrawing/Rect.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class UIElement;
class DependencyObject;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the context menu event. 
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ContextMenuEventArgs: public RoutedEventArgs
{
    // Gets the object that has the ContextMenu that will be opened
    mutable Ptr<UIElement> owner;

    // Gets mouse position
    //@{
    NsFloat32 cursorLeft;
    NsFloat32 cursorTop;
    //@}

    ContextMenuEventArgs(Core::BaseComponent* s, const RoutedEvent* e,
        NsFloat32 left = -1.0f, NsFloat32 top = -1.0f);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides event information for events that occur when a tooltip opens or closes.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ToolTipEventArgs: public RoutedEventArgs
{
    ToolTipEventArgs(Core::BaseComponent* s, const RoutedEvent* e);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides data for the RequestBringIntoView routed event
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API RequestBringIntoViewEventArgs: public RoutedEventArgs
{
    /// Gets the object that should be made visible in response to the event. 
    Ptr<DependencyObject> targetObject;

    /// Gets the rectangular region in the object's coordinate space which should be made visible. 
    Drawing::Rect targetRect;

    RequestBringIntoViewEventArgs(Core::BaseComponent* s, DependencyObject* object,
        const Drawing::Rect& rect);
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif