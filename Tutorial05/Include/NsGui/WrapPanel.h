////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_WRAPPANEL_H__
#define __GUI_WRAPPANEL_H__


#include <Noesis.h>
#include <NsGui/Panel.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
enum Orientation;
//@}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Positions child elements in sequential position from left to right, breaking content
/// to the next line at the edge of the containing box. Subsequent ordering happens sequentially
/// from top to bottom or from right to left, depending on the value of the Orientation property.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.wrappanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API WrapPanel: public Panel
{
public:
    /// Constructor
    WrapPanel();

    /// Gets or sets a value that specifies the width of all items contained in the panel
    //@{
    NsFloat32 GetItemWidth() const;
    void SetItemWidth(NsFloat32 itemWidth);
    //@}

    /// Gets or sets a value that specifies the height of all items contained in the panel
    //@{
    NsFloat32 GetItemHeight() const;
    void SetItemHeight(NsFloat32 itemHeight);
    //@}

    /// Gets or sets orientation of children elements
    //@{
    Orientation GetOrientation() const;
    void SetOrientation(Orientation orientation);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ItemWidthProperty;
    static const DependencyProperty* ItemHeightProperty;
    static const DependencyProperty* OrientationProperty;
    //@}

private:
    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

    Drawing::Size MeasureHorizontal(const Drawing::Size& availableSize);
    Drawing::Size MeasureVertical(const Drawing::Size& availableSize);

    void ArrangeHorizontal(const Drawing::Size& finalSize);
    void ArrangeVertical(const Drawing::Size& finalSize);

    void ArrangeLine(NsSize start, NsSize end, NsFloat32 y, NsFloat32 height,
        NsBool autoW, NsFloat32 itemW);
    void ArrangeColumn(NsSize start, NsSize end, NsFloat32 x, NsFloat32 width,
        NsBool autoH, NsFloat32 itemH);

    NS_DECLARE_REFLECTION(WrapPanel, Panel)
};

}
}

#endif
