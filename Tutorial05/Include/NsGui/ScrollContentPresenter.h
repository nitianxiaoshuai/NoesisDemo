////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SCROLLCONTENTPRESENTER_H__
#define __GUI_SCROLLCONTENTPRESENTER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ContentPresenter.h>
#include <NsGui/IScrollInfo.h>
#include <NsGui/ILayerManager.h>
#include <NsDrawing/Size.h>
#include <NsDrawing/Point.h>
#include <NsCore/ReflectionDeclare.h>

#include <memory>


namespace Noesis
{

// Forward declarations
//@{
namespace Drawing
{
struct Rect;
}
namespace Gui
{
class ScrollViewer;
class VisualCollection;
class RectangleGeometry;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the measurements for the VirtualizingPanel.CacheLength attached property.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.scrollcontentpresenter.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ScrollContentPresenter: public ContentPresenter, public IScrollInfo,
    public ILayerManager
{
public:
    ScrollContentPresenter();
    ~ScrollContentPresenter();

    /// Indicates whether the content, if IScrollInfo, should be allowed to control scrolling.
    //@{
    NsBool GetCanContentScroll() const;
    void SetCanContentScroll(NsBool value);
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

    /// From ILayerManager
    //@{
    void AddLayer(Visual* layerRoot);
    void RemoveLayer(Visual* layerRoot);
    //@}

public:
    static const DependencyProperty* CanContentScrollProperty;

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const;
    Visual* GetVisualChild(NsSize index) const;
    //@}

    /// From UIElement
    //@{
    Ptr<Geometry> GetLayoutClip(const Drawing::Size& layoutSlotSize) const;
    //@}

    /// From FrameworkElement
    //@{
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    void OnTemplatedParentChanged(FrameworkElement* oldParent, FrameworkElement* newParent);
    //@}

    /// From ContentPresenter
    //@{
    void OnContentChanged(Core::BaseComponent* oldContent, Core::BaseComponent* newContent);
    //@}

private:
    NsBool IsScrollClient() const;
    void UpdateScrollInfo(FrameworkElement* templatedParent, Core::BaseComponent* content);

    void EnsureScrollData();
    NsBool HasScrollData() const;
    NsBool UpdateScrollData(const Drawing::Size& extent, const Drawing::Size& viewport);

private:
    friend class ScrollViewerTest;
    friend class ItemsControlTest;
    friend class ItemsPresenter;
    Ptr<VisualCollection> mLayers;
    mutable Ptr<RectangleGeometry> mLayoutClip;

    struct ScrollData;
    std::auto_ptr<ScrollData> mScrollData;
    IScrollInfo* mScrollInfo;

    NS_DECLARE_REFLECTION(ScrollContentPresenter, ContentPresenter)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif