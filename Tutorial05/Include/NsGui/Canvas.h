////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CANVAS_H__
#define __GUI_CANVAS_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines an area within which you can explicitly position child elements by using
/// coordinates that are relative to the Canvas area.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.canvas.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Canvas: public Panel
{
public:
    /// Constructor
    Canvas();

    /// Gets a value that represents the distance between the left side of an element and
    /// the left side of its parent Canvas
    static NsFloat32 GetLeft(UIElement* element);
    /// Sets a value that represents the distance between the left side of an element and
    /// the left side of its parent Canvas
    static void SetLeft(UIElement* element, NsFloat32 left);

    /// Gets a value that represents the distance between the top of an element and the top
    /// of its parent Canvas
    static NsFloat32 GetTop(UIElement* element);
    /// Sets a value that represents the distance between the top of an element and the top
    /// of its parent Canvas
    static void SetTop(UIElement* element, NsFloat32 top);

    /// Gets a value that represents the distance between the right side of an element and
    /// the right side of its parent Canvas
    static NsFloat32 GetRight(UIElement* element);
    /// Sets a value that represents the distance between the right side of an element and
    /// the right side of its parent Canvas
    static void SetRight(UIElement* element, NsFloat32 right);

    /// Gets a value that represents the distance between the bottom of an element and the
    /// bottom of its parent Canvas
    static NsFloat32 GetBottom(UIElement* element);
    /// Sets a value that represents the distance between the bottom of an element and the
    /// bottom of its parent Canvas
    static void SetBottom(UIElement* element, NsFloat32 bottom);

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* BottomProperty; // attached property
    static const DependencyProperty* LeftProperty; // attached property
    static const DependencyProperty* RightProperty; // attached property
    static const DependencyProperty* TopProperty; // attached property
    //@}

protected:
    /// From UIElement
    //@{
    Ptr<Geometry> GetLayoutClip(const Drawing::Size& layoutSlotSize) const;
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    // Detects canvas position changes in children elements
    static void StaticPositionChanged(DependencyObject* obj,
        const DependencyPropertyChangedEventArgs& args);

    NS_DECLARE_REFLECTION(Canvas, Panel)
};

}
}

#endif
