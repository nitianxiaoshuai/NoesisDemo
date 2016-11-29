////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRACK_H__
#define __GUI_TRACK_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class RepeatButton;
class Thumb;
enum Orientation;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control primitive that handles the positioning and sizing of a Thumb
/// control and two RepeatButton controls that are used to set a Value.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.track.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Track: public FrameworkElement
{
public:
    Track();
    ~Track();

    /// Gets the RepeatButton that decreases the Value property of the Track
    /// \prop
    //@{
    RepeatButton* GetDecreaseRepeatButton() const;
    void SetDecreaseRepeatButton(RepeatButton* decButton);
    //@}

    /// Gets the RepeatButton that increases the Value property of the Track class
    /// \prop
    //@{
    RepeatButton* GetIncreaseRepeatButton() const;
    void SetIncreaseRepeatButton(RepeatButton* incButton);
    //@}

    /// Gets or sets if the direction of increasing Value is reversed from the default direction
    //@{
    NsBool GetIsDirectionReversed() const;
    void SetIsDirectionReversed(NsBool directionReversed);
    //@}

    /// Gets or sets the maximum possible Value of the Track
    //@{
    NsFloat32 GetMaximum() const;
    void SetMaximum(NsFloat32 maximum);
    //@}

    /// Gets or sets the minimum possible Value of the Track
    //@{
    NsFloat32 GetMinimum() const;
    void SetMinimum(NsFloat32 minimum);
    //@}

    /// Defines the different orientations that a control or layout can have
    //@{
    Orientation GetOrientation() const;
    void SetOrientation(Orientation orientation);
    //@}

    /// Gets the Thumb control that is used to change the Value of a Track
    //@{
    Thumb* GetThumb() const;
    void SetThumb(Thumb* thumb);
    //@}

    /// Gets or sets the current value of the Track as determined by the position of the Thumb
    //@{
    NsFloat32 GetValue() const;
    void SetValue(NsFloat32 val);
    //@}

    /// Gets or sets the size of the part of the scrollable content that is visible
    //@{
    NsFloat32 GetViewportSize() const;
    void SetViewportSize(NsFloat32 size);
    //@}
    
    /// Calculates the change in the Value of the Track when the Thumb moves.
    NsFloat32 ValueFromDistance(NsFloat32 horizontal, NsFloat32 vertical) const;
    
    /// Calculates the distance value from a specified point along the Track
    NsFloat32 ValueFromPoint(const Drawing::Point& point) const;

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* IsDirectionReversedProperty;
    static const DependencyProperty* MaximumProperty;
    static const DependencyProperty* MinimumProperty;
    static const DependencyProperty* OrientationProperty;
    static const DependencyProperty* ValueProperty;
    static const DependencyProperty* ViewportSizeProperty;
    //@}
    
protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const;
    Visual* GetVisualChild(NsSize index) const;
    //@}
    
    /// From FrameworkElement
    //@{
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    void ArrangeHorizontal(const Drawing::Size& finalSize, NsFloat32 trackSize,
        NsFloat32 viewportSize, NsFloat32 thumbPos, RepeatButton* decBtn, RepeatButton* incBtn);
    void ArrangeVertical(const Drawing::Size& finalSize, NsFloat32 trackSize,
        NsFloat32 viewportSize, NsFloat32 thumbPos, RepeatButton* decBtn, RepeatButton* incBtn);

private:
    Ptr<Thumb> mThumb;
    Ptr<RepeatButton> mDecreaseButton;
    Ptr<RepeatButton> mIncreaseButton;

    NS_DECLARE_REFLECTION(Track, FrameworkElement)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
