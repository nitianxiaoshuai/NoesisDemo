////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VIRTUALIZINGSTACKPANEL_H__
#define __GUI_VIRTUALIZINGSTACKPANEL_H__


#include <Noesis.h>
#include <NsGui/VirtualizingPanel.h>
#include <NsGui/IScrollInfo.h>

#include <memory>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class ItemsControl;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Arranges and virtualizes content on a single line that is oriented either horizontally or
/// vertically.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.virtualizingstackpanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API VirtualizingStackPanel: public VirtualizingPanel, public IScrollInfo
{
public:
    VirtualizingStackPanel();
    ~VirtualizingStackPanel();

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

    // From Panel
    //@{
    void OnItemsChangedOverride(Core::BaseComponent* sender, const ItemsChangedEventArgs& e);
    void GenerateChildren();
    void OnConnectToGenerator(ItemsControl* itemsControl);
    void OnDisconnectFromGenerator();
    //@}

    // From VirtualizingPanel
    //@{
    void BringIndexIntoViewOverride(NsInt32 index);
    //@}

private:
    friend class VirtualizingStackPanelTest;

    struct LayoutHelper;
    struct MakeVisibleHelper;
    struct MeasureHelper;
    struct ArrangeHelper;

    void MakeOffsetVisible(NsFloat32& offset, NsFloat32& p0, NsFloat32& p1, NsFloat32 viewport);

    void OffsetToIndex(Drawing::Point& offset, NsBool itemScrolling, NsBool isHorizontal);
    NsFloat32 OffsetToIndex(ItemContainerGenerator* generator, UIElementCollection* children,
        NsInt numItems, const Drawing::Size& constraint, NsBool isHorizontal, NsBool itemScrolling,
        NsBool isRecycling, NsFloat32& direction);
    void AccumDesiredSize(Drawing::Size& desiredSize, DependencyObject* container,
        NsBool isHorizontal);
    void RemoveDesiredSize(Drawing::Size& desiredSize, NsFloat32 size, NsBool isHorizontal);
    NsInt CachedItems(NsInt viewportItems, NsFloat32 cacheLength,
        VirtualizationCacheLengthUnit cacheUnit);
    void EnsureEstimatedSize(ItemContainerGenerator* generator, UIElementCollection* children,
        const Drawing::Size& constraint, NsBool isHorizontal, NsBool isRecycling);
    void UpdateItemSize(NsInt index, NsFloat32 itemSize);
    NsFloat32 ItemSize(NsInt i) const;
    NsFloat32 ItemSize(NsFloat32 size) const;

    Drawing::Size MeasureViewport(ItemContainerGenerator* generator, UIElementCollection* children,
        const Drawing::Size& constraint, NsFloat32 viewportSize, NsInt numItems,
        NsInt& firstVisible, NsInt& lastVisible, NsFloat32& accumVisibleSize, NsBool isHorizontal,
        NsBool itemScrolling, NsBool isRecycling);
    void MeasureUnrealized(ItemContainerGenerator* generator, UIElementCollection* children,
        const Drawing::Size& constraint, Drawing::Size& desiredSize, NsInt start, NsInt end,
        NsBool isHorizontal, NsBool updateArrangeOffset = false);
    NsFloat32 MeasureContainer(DependencyObject* container, const Drawing::Size& constraint,
        NsInt itemIndex, NsBool isHorizontal);
    void AccumDeltaSize(NsFloat32 oldSize, NsFloat32 newSize, NsFloat32& deltaSize,
        NsBool shouldAccumSize = true);
    NsBool AdjustOffset(NsFloat32 direction, NsFloat32 viewportSize, NsFloat32& deltaSize,
        NsFloat32& accumVisibleSize, Drawing::Size& desiredSize, NsFloat32 firstVisibleSize,
        NsFloat32 firstVisiblePerc, NsInt& firstVisible, NsInt& lastVisible, NsInt itemIndex,
        NsBool isHorizontal, NsBool itemScrolling, NsBool makingVisible,
        NsBool visibleContainerMeasured, NsInt visibleContainerIndex);
    void AdjustOffset(NsFloat32 deltaSize, NsBool isHorizontal);

    Drawing::Point ArrangeOffset(NsBool isHorizontal, NsBool itemScrolling);
    Drawing::Size ArrangeSize(const Drawing::Size& finalSize, const Drawing::Size& childSize,
        NsBool isHorizontal);
    void AccumArrangeOffset(Drawing::Point& offset, NsInt start, NsInt end, NsFloat32 averageSize,
        NsBool isHorizontal);
    void AccumArrangeOffset(Drawing::Point& offset, const Drawing::Size& arrangeSize,
        NsBool isHorizontal);

    Ptr<DependencyObject> GenerateContainer(ItemContainerGenerator* generator,
        UIElementCollection* children, NsInt index, NsBool isRecycling);
    Ptr<DependencyObject> GenerateContainer(ItemContainerGenerator* generator,
        UIElementCollection* children, NsInt index, NsBool isRecycling, NsBool& isNewChild);
    NsBool IsRecycledContainer(DependencyObject* container, UIElementCollection* children,
        NsInt index, NsBool isRecycling);
    void GenerateRange(ItemContainerGenerator* generator, UIElementCollection* children,
        NsInt start, NsInt end, NsBool isHorizontal, NsBool isRecycling,
        const Drawing::Size& constraint, Drawing::Size& desiredSize);

    void RemoveHiddenItems(ItemsControl* itemsControl, ItemContainerGenerator* generator,
        UIElementCollection* children, NsInt firstVisible, NsInt lastVisible, NsBool isRecycling);
    void RemoveRange(ItemContainerGenerator* generator, UIElementCollection* children,
        NsInt start, NsInt count, NsBool isRecycling);

    void UpdateScrollData(NsBool isHorizontal, NsBool itemScrolling,
        const Drawing::Size& extent, NsInt itemExtent,
        const Drawing::Size& viewport, NsInt itemViewport,
        const Drawing::Point& offset, NsInt itemOffset);

    void EnsureScrollData();
    NsBool HasScrollData() const;
    NsBool IsScrolling() const;
    NsBool IsHorizontal() const;
    NsBool IsVertical() const;
    NsBool ItemScrolling() const;
    NsBool ItemScrolling(ItemsControl* itemsControl) const;

    void ResetScrolling();

    void UpdateSizes(Core::BaseComponent* sender, const NotifyCollectionChangedEventArgs& e);

    static void OnOrientationChanged(DependencyObject* d,
        const DependencyPropertyChangedEventArgs& e);

private:
    struct ScrollData;
    std::auto_ptr<ScrollData> mScrollData;

    NS_DECLARE_REFLECTION(VirtualizingStackPanel, VirtualizingPanel)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
