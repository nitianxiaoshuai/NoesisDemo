////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ISCROLLINFO_H__
#define __GUI_ISCROLLINFO_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Gui
{
class Visual;
class ScrollViewer;
}
namespace Drawing
{
struct Rect;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the main scrollable region inside a ScrollViewer control.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IScrollInfo: public Core::Interface
{
    /// Gets or sets a value that indicates whether scrolling on the horizontal axis is possible
    /// \prop
    //@{
    virtual NsBool GetCanHorizontallyScroll() const = 0;
    virtual void SetCanHorizontallyScroll(NsBool canScroll) = 0;
    //@}

    /// Gets or sets a value that indicates whether scrolling on the vertical axis is possible
    /// \prop
    //@{
    virtual NsBool GetCanVerticallyScroll() const = 0;
    virtual void SetCanVerticallyScroll(NsBool canScroll) = 0;
    //@}

    /// Gets the horizontal size of the extent
    /// \prop
    virtual NsFloat32 GetExtentWidth() const = 0;

    /// Gets the vertical size of the extent
    /// \prop
    virtual NsFloat32 GetExtentHeight() const = 0;

    /// Gets the horizontal size of the viewport for this content
    /// \prop
    virtual NsFloat32 GetViewportWidth() const = 0;

    /// Gets the vertical size of the viewport for this content
    /// \prop
    virtual NsFloat32 GetViewportHeight() const = 0;

    /// Gets the horizontal offset of the scrolled content
    /// \prop
    virtual NsFloat32 GetHorizontalOffset() const = 0;

    /// Gets the vertical offset of the scrolled content
    /// \prop
    virtual NsFloat32 GetVerticalOffset() const = 0;

    /// Gets or sets a ScrollViewer element that controls scrolling behavior
    /// \prop
    //@{
    virtual ScrollViewer* GetScrollOwner() const = 0;
    virtual void SetScrollOwner(ScrollViewer* owner) = 0;
    //@}

    /// Scrolls left within content by one logical unit
    virtual void LineLeft() = 0;

    /// Scrolls right within content by one logical unit
    virtual void LineRight() = 0;

    /// Scrolls up within content by one logical unit
    virtual void LineUp() = 0;

    /// Scrolls down within content by one logical unit
    virtual void LineDown() = 0;

    /// Scrolls left within content by one page
    virtual void PageLeft() = 0;

    /// Scrolls right within content by one page
    virtual void PageRight() = 0;

    /// Scrolls up within content by one page
    virtual void PageUp() = 0;

    /// Scrolls down within content by one page
    virtual void PageDown() = 0;

    /// Scrolls left within content after a user spins the wheel button on a mouse. Delta value
    /// indicates the number of turns made on the mouse wheel. Number of lines advanced on each
    /// wheel turn can be configured in the operating system
    virtual void MouseWheelLeft(NsFloat32 delta = 1.0f) = 0;

    /// Scrolls right within content after a user spins the wheel button on a mouse. Delta value
    /// indicates the number of turns made on the mouse wheel. Number of lines advanced on each
    /// wheel turn can be configured in the operating system
    virtual void MouseWheelRight(NsFloat32 delta = 1.0f) = 0;

    /// Scrolls up within content after a user spins the wheel button on a mouse. Delta value
    /// indicates the number of turns made on the mouse wheel. Number of lines advanced on each
    /// wheel turn can be configured in the operating system
    virtual void MouseWheelUp(NsFloat32 delta = 1.0f) = 0;

    /// Scrolls down within content after a user spins the wheel button on a mouse. Delta value
    /// indicates the number of turns made on the mouse wheel. Number of lines advanced on each
    /// wheel turn can be configured in the operating system
    virtual void MouseWheelDown(NsFloat32 delta = 1.0f) = 0;

    /// Sets the amount of horizontal offset
    virtual void SetHorizontalOffset(NsFloat32 offset) = 0;

    /// Sets the amount of vertical offset
    virtual void SetVerticalOffset(NsFloat32 offset) = 0;

    /// Forces content to scroll until the coordinate space of a Visual object is visible.
    virtual Drawing::Rect MakeVisible(Visual* visual, const Drawing::Rect& rectangle) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IScrollInfo, Core::Interface)
};

}
}


#endif
