////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STACKPANEL_H__
#define __GUI_STACKPANEL_H__


#include <Noesis.h>
#include <NsGui/Panel.h>
#include <NsGui/IScrollInfo.h>

#include <memory>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
enum Orientation;
enum TextAlignment;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Arranges child elements into a single horizontal or vertical line.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.stackpanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API StackPanel: public Panel, public IScrollInfo
{
public:
    StackPanel();
    ~StackPanel();

    /// Gets or sets orientation of children elements
    //@{
    Orientation GetOrientation() const;
    void SetOrientation(Orientation orientation);
    //@}

    // From IScrollInfo
    //@{
    NsBool GetCanHorizontallyScroll() const;
    void SetCanHorizontallyScroll(NsBool canScroll);
    NsBool GetCanVerticallyScroll() const;
    void SetCanVerticallyScroll(NsBool canScroll);
    NsFloat32 GetExtentWidth() const;
    NsFloat32 GetExtentHeight() const;
    NsFloat32 GetViewportWidth() const;
    NsFloat32 GetViewportHeight() const;
    NsFloat32 GetHorizontalOffset() const;
    NsFloat32 GetVerticalOffset() const;
    ScrollViewer* GetScrollOwner() const;
    void SetScrollOwner(ScrollViewer* owner);
    void LineLeft();
    void LineRight();
    void LineUp();
    void LineDown();
    void PageLeft();
    void PageRight();
    void PageUp();
    void PageDown();
    void MouseWheelLeft(NsFloat32 delta = 1.0f);
    void MouseWheelRight(NsFloat32 delta = 1.0f);
    void MouseWheelUp(NsFloat32 delta = 1.0f);
    void MouseWheelDown(NsFloat32 delta = 1.0f);
    void SetHorizontalOffset(NsFloat32 offset);
    void SetVerticalOffset(NsFloat32 offset);
    Drawing::Rect MakeVisible(Visual* visual, const Drawing::Rect& rect);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* OrientationProperty;
    //@}

protected:
    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    void EnsureScrollData();
    NsBool HasScrollData() const;
    NsBool IsScrolling() const;

private:
    friend class VirtualizingStackPanel;
    friend class ScrollViewerTest;

    struct ScrollData;
    std::auto_ptr<ScrollData> mScrollData;

    NS_DECLARE_REFLECTION(StackPanel, Panel)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
