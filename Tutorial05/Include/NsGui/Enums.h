////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ENUMS_H__
#define __GUI_ENUMS_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes how content is positioned horizontally in a container.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum AlignmentX
{
    /// The contents align toward the left of the container.
    AlignmentX_Left,
    
    /// The contents align toward the center of the container.
    AlignmentX_Center,
    
    /// The contents align toward the right of the container.
    AlignmentX_Right
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes how content is positioned vertically in a container.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum AlignmentY
{
    /// The contents align toward the upper edge of the container.
    AlignmentY_Top,

    /// The contents align toward the center of the container.
    AlignmentY_Center,

    /// The contents align toward the lower edge of the container.
    AlignmentY_Bottom
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum AutoToolTipPlacement
{
    /// No automatic ToolTip 
    AutoToolTipPlacement_None,
    /// For a horizontal Slider show the automatic ToolTip at the top edge of the Thumb. For a 
    /// vertical Slider show the automatic ToolTip at the left edge of the Thumb. 
    AutoToolTipPlacement_TopLeft,
    /// For a horizontal Slider show the automatic ToolTip at the bottom edge of the Thumb. For a
    /// vertical Slider show the automatic ToolTip at the right edge of the Thumb. 
    AutoToolTipPlacement_BottomRight 
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum BindingMode
{
    /// Uses the default Mode value of the binding target. The default value varies for each 
    /// dependency property. In general, user-editable control properties, such as those of text 
    /// boxes and check boxes, default to two-way bindings, whereas most other properties default 
    /// to one-way bindings. A programmatic way to determine whether a dependency property binds 
    /// one-way or two-way by default is to get the property metadata of the property using 
    /// GetMetaData and then check the Boolean value of the BindsTwoWayByDefault property. 
    BindingMode_Default,

    /// Causes changes to either the source property or the target property to automatically update 
    /// the other. This type of binding is appropriate for editable forms or other 
    /// fully-interactive UI scenarios. 
    BindingMode_TwoWay,

    /// Updates the binding target (target) property when the binding source (source) changes. This 
    /// type of binding is appropriate if the control being bound is implicitly read-only. For 
    /// instance, you may bind to a source such as a stock ticker. Or perhaps your target property 
    /// has no control interface provided for making changes, such as a data-bound background color 
    /// of a table. If there is no need to monitor the changes of the target property, using the 
    /// OneWay binding mode avoids the overhead of the TwoWay binding mode. 
    BindingMode_OneWay,

    /// Updates the binding target when the application starts or when the data context changes. 
    /// This type of binding is appropriate if you are using data where either a snapshot of the 
    /// current state is appropriate to use or the data is truly static. This type of binding is 
    /// also useful if you want to initialize your target property with some value from a source 
    /// property and the data context is not known in advance. This is essentially a simpler form 
    /// of OneWay binding that provides better performance in cases where the source value does not 
    /// change. 
    BindingMode_OneTime,

    /// Updates the source property when the target property changes. 
    BindingMode_OneWayToSource
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies which algorithm is used to scale bitmap images.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum BitmapScalingMode
{
    /// Use the default bitmap scaling mode, which is HighQuality
    /// NOTE: In WPF the default value is LowQuality/Linear
    BitmapScalingMode_Unspecified,

    /// Use bilinear bitmap scaling, which is faster than HighQuality mode, but produces lower
    /// quality output. The LowQuality mode is the same as the Linear mode
    BitmapScalingMode_LowQuality,

    /// Use high quality bitmap scaling, which is slower than LowQuality mode, but produces higher
    //// quality output. The HighQuality mode is the same as the Fant mode
    BitmapScalingMode_HighQuality,

    /// Use linear bitmap scaling, which is faster than HighQuality mode, but produces lower
    /// quality output
    BitmapScalingMode_Linear = BitmapScalingMode_LowQuality,

    /// Use very high quality Fant bitmap scaling, which is slower than all other bitmap scaling
    /// modes, but produces higher quality output
    BitmapScalingMode_Fant = BitmapScalingMode_HighQuality,

    /// Use nearest-neighbor bitmap scaling, which provides performance benefits over LowQuality
    /// mode when the software rasterizer is used. This mode is often used to magnify a bitmap.
    BitmapScalingMode_NearestNeighbor,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the coordinate system used by a Brush. 
////////////////////////////////////////////////////////////////////////////////////////////////////
enum BrushMappingMode
{
    /// The coordinate system is not relative to a bounding box. Values are interpreted directly in 
    /// local space.
    BrushMappingMode_Absolute,

    /// The coordinate system is relative to a bounding box: 0 indicates 0 percent of the bounding 
    /// box, and 1 indicates 100 percent of the bounding box. For example, (0.5, 0.5) describes a 
    /// point in the middle of the bounding box, and (1, 1) describes a point at the bottom right 
    /// of the bounding box.  
    BrushMappingMode_RelativeToBoundingBox
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum CharacterCasing
{
    /// Characters typed into a TextBox are not converted. 
    CharacterCasing_Normal,

    /// Characters typed into a TextBox are converted to lowercase. 
    CharacterCasing_Lower,

    /// Characters typed into a TextBox are converted to uppercase. 
    CharacterCasing_Upper
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies when the Click event should fire.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum ClickMode
{
    /// The Click event should fire when the mouse hovers over a control
    ClickMode_Hover,

    /// The Click event will occur as soon as a button is pressed
    ClickMode_Press,

    /// The Click event will occur when a button is pressed and released
    ClickMode_Release
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Determines how the colors in a gradient are interpolated. 
////////////////////////////////////////////////////////////////////////////////////////////////////
enum ColorInterpolationMode 
{
    /// Colors are interpolated in the scRGB color space
    ColorInterpolationMode_ScRgbLinearInterpolation, 

    /// Colors are interpolated in the sRGB color space 
    ColorInterpolationMode_SRgbLinearInterpolation 
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Dock. Specifies the Dock position of a child element that is inside a DockPanel.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum Dock
{
    /// A child element that is positioned on the left side of the DockPanel
    Dock_Left,

    /// A child element that is positioned at the top of the DockPanel
    Dock_Top, 

    /// A child element that is positioned on the right side of the DockPanel
    Dock_Right,

    /// A child element that is positioned at the bottom of the DockPanel
    Dock_Bottom
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ExpandDirection. Specifies the direction in which an Expander control opens.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum ExpandDirection
{
    /// The Expander control opens down
    ExpandDirection_Down,

    /// The Expander control opens up
    ExpandDirection_Up,

    /// The Expander control opens left
    ExpandDirection_Left,

    ///  The Expander control opens right
    ExpandDirection_Right
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies how the intersecting areas of PathFigure objects contained in a Geometry are combined 
/// to form the area of the Geometry.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FillRule
{
    /// Rule that determines whether a point is in the fill region by drawing a ray from that point 
    /// to infinity in any direction and counting the number of path segments within the given 
    /// shape that the ray crosses. If this number is odd, the point is inside; if even, the point 
    /// is outside. 
    FillRule_EvenOdd,

    /// Rule that determines whether a point is in the fill region of the path by drawing a ray 
    /// from that point to infinity in any direction and then examining the places where a segment 
    /// of the shape crosses the ray. Starting with a count of zero, add one each time a segment 
    /// crosses the ray from left to right and subtract one each time a path segment crosses the 
    /// ray from right to left. After counting the crossings, if the result is zero then the point 
    /// is outside the path. Otherwise, it is inside. 
    FillRule_Nonzero
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// FlowDirection. Specify the content flow direction for text and UI elements
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FlowDirection
{
    /// Indicates that content should flow from left to right. 
    FlowDirection_LeftToRight,

    /// Indicates that content should flow from right to left. 
    FlowDirection_RightToLeft
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes the degree to which a font has been stretched compared to the normal aspect ratio of 
/// that font
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontStretch
{
    /// 50.0%
    FontStretch_UltraCondensed = 1,

    /// 62.5%
    FontStretch_ExtraCondensed = 2,

    /// 75.0%
    FontStretch_Condensed = 3,

    /// 87.5%
    FontStretch_SemiCondensed = 4,

    /// 100.0%
    FontStretch_Normal = 5,
    FontStretch_Medium = 5,

    /// 112.5%
    FontStretch_SemiExpanded = 6,

    /// 125.0%
    FontStretch_Expanded = 7,

    /// 150.0%
    FontStretch_ExtraExpanded = 8,

    /// 200.0%
    FontStretch_UltraExpanded = 9
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a structure that represents the style of a font face as normal, italic, or oblique.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontStyle
{
    /// The characters in a normal, or roman, font are upright.
    FontStyle_Normal,
    
    /// The characters in an italic font are truly slanted and appear as they were designed.
    FontStyle_Italic,
    
    /// The characters in an oblique font are artificially slanted. The slant is achieved by 
    /// performing a shear transformation on the characters from a normal font. When a true italic
    /// font is not available on a computer or printer, an oblique style can generated from the
    /// normal font and used to simulate an italic font.
    FontStyle_Oblique
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Refers to the density of a typeface, in terms of the lightness or heaviness of the strokes
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontWeight
{
    FontWeight_Thin = 100,
    FontWeight_ExtraLight = 200,
    FontWeight_UltraLight = 200,
    FontWeight_Light = 300,
    FontWeight_Normal = 400,
    FontWeight_Regular = 400,
    FontWeight_Medium = 500,
    FontWeight_DemiBold = 600,
    FontWeight_SemiBold = 600,
    FontWeight_Bold = 700,
    FontWeight_ExtraBold = 800,
    FontWeight_UltraBold = 800,
    FontWeight_Black = 900,
    FontWeight_Heavy = 900,
    FontWeight_ExtraBlack = 950,
    FontWeight_UltraBlack = 950
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the different methods by which two geometries can be combined. 
////////////////////////////////////////////////////////////////////////////////////////////////////
enum GeometryCombineMode
{
    /// The two regions are combined by taking the union of both. The resulting geometry is 
    /// geometry A + geometry B. 
    GeometryCombineMode_Union,

    /// The two regions are combined by taking their intersection. The new area consists of the 
    /// overlapping region between the two geometries.  
    GeometryCombineMode_Intersect,

    /// The two regions are combined by taking the area that exists in the first region but not the 
    /// second and the area that exists in the second region but not the first. The new region 
    //// consists of (A-B) + (B-A), where A and B are geometries.  
    GeometryCombineMode_Xor,

    /// The second region is excluded from the first. Given two geometries, A and B, the area of 
    /// geometry B is removed from the area of geometry A, producing a region that is A-B. 
    GeometryCombineMode_Exclude
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies how to draw the gradient outside a gradient brush's gradient vector or space.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum GradientSpreadMethod
{
    /// Fill the remaining space with boundary colors (default)
    GradientSpreadMethod_Pad,

    /// Gradient is repeated in the reverse direction
    GradientSpreadMethod_Reflect,

    /// Gradient is repeated in the original direction
    GradientSpreadMethod_Repeat
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Indicates where an element should be displayed on the horizontal axis relative to the
/// allocated layout slot of the parent element.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum HorizontalAlignment
{
    /// Element aligned to the left of the layout slot for the parent
    HorizontalAlignment_Left,

    /// Element aligned to the center of the layout slot for the parent
    HorizontalAlignment_Center,

    /// Element aligned to the right of the layout slot for the parent
    HorizontalAlignment_Right,

    /// Element stretched to fill the entire layout slot of the parent
    HorizontalAlignment_Stretch
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum KeyboardNavigationMode
{
    /// Each element receives keyboard focus, as long as it is a navigation stop. Navigation leaves
    /// the containing element when an edge is reached. 
    KeyboardNavigationMode_Continue,

    /// The container and all of its child elements as a whole receive focus only once. Either the 
    /// first tree child or the or the last focused element in the group receives focus 
    KeyboardNavigationMode_Once,

    /// Depending on the direction of the navigation, the focus returns to the first or the last 
    /// item when the end or the beginning of the container is reached. Focus cannot leave the 
    /// container using logical navigation. 
    KeyboardNavigationMode_Cycle,

    /// No keyboard navigation is allowed inside this container. 
    KeyboardNavigationMode_None,

    /// Depending on the direction of the navigation, focus returns to the first or the last item 
    /// when the end or the beginning of the container is reached, but does not move past the 
    /// beginning or end of the container. 
    KeyboardNavigationMode_Contained,

    /// Tab Indexes are considered on local subtree only inside this container and behave like 
    /// Continue after that. 
    KeyboardNavigationMode_Local
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum LineStackingStrategy
{
    /// The stack height is determined by the block element line-height property value.  
    LineStackingStrategy_BlockLineHeight,
    /// The stack height is the smallest value that containing all the inline elements on that line
    /// when those elements are properly aligned.
    LineStackingStrategy_MaxHeight
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum ListSortDirection
{
    ListSortDirection_Ascending,
    ListSortDirection_Descending
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// MenuItemRole. Defines the different roles that a MenuItem can have.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum MenuItemRole
{
    /// Top-level menu item that can invoke commands
    MenuItemRole_TopLevelItem,

    /// Header for top-level menus
    MenuItemRole_TopLevelHeader,

    /// Menu item in a submenu that can invoke commands
    MenuItemRole_SubmenuItem,

    /// Header for a submenu
    MenuItemRole_SubmenuHeader
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines the different orientations that a control or layout can have.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum Orientation
{
    /// Control or layout should be horizontally oriented.   
    Orientation_Horizontal,

    /// Control or layout should be vertically oriented 
    Orientation_Vertical
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum OverflowMode
{
    /// Item moves between the main panel and overflow panel, depending on the available space.  
    OverflowMode_AsNeeded,

    /// Item is permanently placed in the overflow panel.  
    OverflowMode_Always,

    /// Item is never allowed to overflow.  
    OverflowMode_Never 
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PenLineCap. Describes the shape at the end of a line or segment. 
////////////////////////////////////////////////////////////////////////////////////////////////////
enum PenLineCap
{
    /// A cap that does not extend past the last point of the line. Comparable to no line cap
    PenLineCap_Flat,

    /// A rectangle that has a height equal to the line thickness and a length equal to half the
    /// line thickness
    PenLineCap_Square,

    /// A semicircle that has a diameter equal to the line thickness
    PenLineCap_Round,

    /// An isosceles right triangle whose base length is equal to the thickness of the line
    PenLineCap_Triangle
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PenLineJoin. Describes the shape that joins two lines or segments.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum PenLineJoin
{
    /// Regular angular vertices
    PenLineJoin_Miter,

    /// Beveled vertices
    PenLineJoin_Bevel,

    /// Rounded vertices
    PenLineJoin_Round
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PlacementMode. Describes the placement of where a Popup control appears on the screen.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum PlacementMode
{
    /// A position of the Popup control relative to the upper-left corner of the screen and at an
    /// offset that is defined by the HorizontalOffset and VerticalOffset property values. If the
    /// screen edge obscures the Popup, the control then repositions itself to align with the edge
    PlacementMode_Absolute,

    /// A position of the Popup control relative to the upper-left corner of the PlacementTarget
    /// and at an offset that is defined by the HorizontalOffset and VerticalOffset property values.
    /// If the screen edge obscures the Popup, the control repositions itself to align with the
    /// screen edge
    PlacementMode_Relative,

    /// A position of the Popup control where the control aligns its upper edge with the lower edge
    /// of the PlacementTarget and aligns its left edge with the left edge of the PlacementTarget.
    /// If the lower screen-edge obscures the Popup, the control repositions itself so that its
    /// lower edge aligns with the upper edge of the PlacementTarget. If the upper screen-edge
    /// obscures the Popup, the control then repositions itself so that its upper edge aligns with
    /// the upper screen-edge
    PlacementMode_Bottom,

    /// A position of the Popup control where it is centered over the PlacementTarget. If a screen
    /// edge obscures the Popup, the control repositions itself to align with the screen edge
    PlacementMode_Center,

    /// A position of the Popup control that aligns its left edge with the right edge of the
    /// PlacementTarget and aligns its upper edge with the upper edge of the PlacementTarget. If
    /// the right screen-edge obscures the Popup, the control repositions itself so that its left
    /// edge aligns with the left edge of the PlacementTarget. If the left screen-edge obscures
    /// the Popup, the control repositions itself so that its left edge aligns with the left
    /// screen-edge. If the upper or lower screen-edge obscures the Popup, the control then
    /// repositions itself to align with the obscuring screen edge
    PlacementMode_Right,

    /// A position of the Popup control relative to the upper-left corner of the screen and at an
    /// offset that is defined by the HorizontalOffset and VerticalOffset property values. If the
    /// screen edge obscures the Popup, the control extends in the opposite direction from the axis
    /// defined by the HorizontalOffset or VerticalOffset
    PlacementMode_AbsolutePoint,

    /// A position of the Popup control relative to the upper-left corner of the PlacementTarget
    /// and at an offset that is defined by the HorizontalOffset and VerticalOffset property values.
    /// If a screen edge obscures the Popup, the Popup extends in the opposite direction from the
    /// direction from the axis defined by the HorizontalOffset or VerticalOffset. If the opposite
    /// screen edge also obscures the Popup, the control then aligns with this screen edge
    PlacementMode_RelativePoint,

    /// A postion of the Popup control that aligns its upper edge with the lower edge of the
    /// bounding box of the mouse and aligns its left edge with the left edge of the bounding box
    /// of the mouse. If the lower screen-edge obscures the Popup, it repositions itself to align
    /// with the upper edge of the bounding box of the mouse. If the upper screen-edge obscures the
    /// Popup, the control repositions itself to align with the upper screen-edge
    PlacementMode_Mouse,

    /// A position of the Popup control relative to the tip of the mouse cursor and at an offset
    /// that is defined by the HorizontalOffset and VerticalOffset property values. If a horizontal
    /// or vertical screen edge obscures the Popup, it opens in the opposite direction from the
    /// obscuring edge. If the opposite screen edge also obscures the Popup, it then aligns with
    /// the obscuring screen edge
    PlacementMode_MousePoint,

    /// A Popup control that aligns its right edge with the left edge of the PlacementTarget and
    /// aligns its upper edge with the upper edge of the PlacementTarget. If the left screen-edge
    /// obscures the Popup, the Popup repositions itself so that its left edge aligns with the
    /// right edge of the PlacementTarget. If the right screen-edge obscures the Popup, the right
    /// edge of the control aligns with the right screen-edge. If the upper or lower screen-edge
    /// obscures the Popup, the control repositions itself to align with the obscuring screen edge
    PlacementMode_Left,

    /// A position of the Popup control that aligns its lower edge with the upper edge of the
    /// PlacementTarget and aligns its left edge with the left edge of the PlacementTarget. If the
    /// upper screen-edge obscures the Popup, the control repositions itself so that its upper edge
    /// aligns with the lower edge of the PlacementTarget. If the lower screen-edge obscures the
    /// Popup, the lower edge of the control aligns with the lower screen-edge. If the left or
    /// right screen-edge obscures the Popup, it then repositions itself to align with the
    /// obscuring screen
    PlacementMode_Top,

    /// A position and repositioning behavior for the Popup control that is defined by the
    /// CustomPopupPlacementCallback delegate specified by the CustomPopupPlacementCallback property
    PlacementMode_Custom
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PopupAnimation. Represents a pop-up window that has content.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum PopupAnimation
{
    /// The Popup control appears without animation
    PopupAnimation_None,

    /// The Popup control gradually appears, or fades in. This effect is created by increasing the
    /// opacity of the Popup window over time
    PopupAnimation_Fade,

    /// The Popup control slides down or up into place. By default, a Popup slides down. However, if
    /// the screen does not provide enough room for the Popup to slide down, it slides up instead
    PopupAnimation_Slide,

    ///  The Popup control scrolls from the upper-left corner of its parent. If the screen does not
    /// provide enough room to allow the Popup default behavior, the Popup scrolls from the
    /// lower-right corner instead
    PopupAnimation_Scroll
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum RelativeSourceMode
{
    /// Allows you to bind the previous data item (not that control that contains the data item) 
    /// in the list of data items being displayed
    RelativeSourceMode_PreviousData, 

    /// Refers to the element to which the template (in which the data-bound element exists) is 
    /// applied. This is similar to setting a TemplateBindingExtension and is only applicable if 
    /// the Binding is within a template
    RelativeSourceMode_TemplatedParent,

    /// Refers to the element on which you are setting the binding and allows you to bind one 
    /// property of that element to another property on the same element
    RelativeSourceMode_Self, 

    /// Refers to the ancestor in the parent chain of the data-bound element. You can use this to 
    /// bind to an ancestor of a specific type or its subclasses. This is the mode you use if you 
    /// want to specify AncestorType and/or AncestorLevel
    RelativeSourceMode_FindAncestor 
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum SelectionMode
{
    /// The user can select only one item at a time. This is the default mode.
    SelectionMode_Single, 
    /// The user can select multiple items without holding down a modifier key. 
    SelectionMode_Multiple,
    /// The user can select multiple consecutive items while holding down the SHIFT key.  
    SelectionMode_Extended
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the visibility of a ScrollBar for scrollable content.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum ScrollBarVisibility
{
    /// A ScrollBar does not appear even when the viewport cannot display all of the content. The
    /// dimension of the content is set to the corresponding dimension of the ScrollViewer parent.
    /// For a horizontal ScrollBar, the width of the content is set to the ViewportWidth of the
    /// ScrollViewer. For a vertical ScrollBar, the height of the content is set to the
    /// ViewportHeight of the ScrollViewer
    ScrollBarVisibility_Disabled,

    /// A ScrollBar appears and the dimension of the ScrollViewer is applied to the content when
    /// the viewport cannot display all of the content. For a horizontal ScrollBar, the width of
    /// the content is set to the ViewportWidth of the ScrollViewer. For a vertical ScrollBar, the
    /// height of the content is set to the ViewportHeight of the ScrollViewer
    ScrollBarVisibility_Auto,

    /// A ScrollBar does not appear even when the viewport cannot display all of the content. The
    /// dimension of the ScrollViewer is not applied to the content
    ScrollBarVisibility_Hidden,

    /// A ScrollBar always appears. The dimension of the ScrollViewer is applied to the content.
    /// For a horizontal ScrollBar, the width of the content is set to the ViewportWidth of the
    /// ScrollViewer. For a vertical ScrollBar, the height of the content is set to the
    /// ViewportHeight of the ScrollViewer
    ScrollBarVisibility_Visible
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes how content is resized to fill its allocated space.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum Stretch
{
    /// The content preserves its original size.  
    Stretch_None,
    
    /// The content is resized to fill the destination dimensions. The aspect ratio is not preserved
    Stretch_Fill,
    
    /// The content is resized to fit in the destination dimensions while it preserves its native 
    /// aspect ratio
    Stretch_Uniform,
    
    /// The content is resized to fill the destination dimensions while it preserves its native 
    /// aspect ratio. If the aspect ratio of the destination rectangle differs from the source, the 
    /// source content is clipped to fit in the destination dimensions. 
    Stretch_UniformToFill 
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes how scaling applies to content and restricts scaling to named axis types.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum StretchDirection
{
    ///  The content scales upward only when it is smaller than the parent. If the content is
    /// larger, no scaling downward is performed
    StretchDirection_UpOnly,

    /// The content scales downward only when it is larger than the parent. If the content is
    /// smaller, no scaling upward is performed.  
    StretchDirection_DownOnly,

    /// The content stretches to fit the parent according to the Stretch mode
    StretchDirection_Both
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies if the text in the object is left-aligned, right-aligned, centered, or justified.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum TextAlignment
{
    /// Text is centered
    TextAlignment_Center,

    /// Text is justified
    TextAlignment_Justify,

    /// Text is aligned to the left (default)
    TextAlignment_Left,

    /// Text is aligned to the right
    TextAlignment_Right
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum TextTrimming
{
    /// Text is not trimmed.
    TextTrimming_None,
    /// Text is trimmed at a character boundary. An ellipsis (...) is drawn in place of remaining 
    /// text
    TextTrimming_CharacterEllipsis,
    /// Text is trimmed at a word boundary. An ellipsis (...) is drawn in place of remaining text.
    TextTrimming_WordEllipsis
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies whether text wraps when it reaches the edge of the containing box.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum TextWrapping
{
    /// No line wrapping is performed
    TextWrapping_NoWrap,

    /// Line-breaking occurs if the line overflows beyond the available block width, even if the
    /// standard line breaking algorithm cannot determine any line break opportunity, as in the
    /// case of a very long word constrained in a fixed-width container with no scrolling allowed
    TextWrapping_Wrap,

    /// Line-breaking occurs if the line overflows beyond the available block width. However, a
    /// line may overflow beyond the block width if the line breaking algorithm cannot determine a
    /// line break opportunity, as in the case of a very long word constrained in a fixed-width
    /// container with no scrolling allowed. 
    TextWrapping_WrapWithOverflow
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the placement of a TickBar with respect to the Track of a Slider.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum TickBarPlacement
{
    /// The tick bar is positioned to the left of the Track of the Slider
    TickBarPlacement_Left,

    /// The tick bar is positioned above the Track of the Slider
    TickBarPlacement_Top,

    /// The tick bar is positioned to the right of the Track of the Slider
    TickBarPlacement_Right,

    ///  The tick bar is positioned below the Track of the Slider
    TickBarPlacement_Bottom
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum TickPlacement
{
    /// No tick marks appear.
    TickPlacement_None,
    /// Tick marks appear above the Track for a horizontal Slider, or to the left of the Track for 
    /// a vertical Slider.  
    TickPlacement_TopLeft,
    /// Tick marks appear below the Track for a horizontal Slider, or to the right of the Track for
    /// a vertical Slider.  
    TickPlacement_BottomRight,
    /// Tick marks appear above and below the Track bar for a horizontal Slider, or to the left and
    /// right of the Track for a vertical Slider. 
    TickPlacement_Both
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes how a TileBrush paints tiles onto an output area.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum TileMode
{
    /// The base tile is drawn but not repeated. The remaining area is transparent  
    TileMode_None,
    
    /// The base tile is drawn and the remaining area is filled by repeating the base tile. The 
    /// right edge of one tile meets the left edge of the next, and similarly for the bottom and 
    /// top edges.
    TileMode_Tile,
    
    /// The same as Tile except that alternate columns of tiles are flipped horizontally. The base 
    /// tile itself is not flipped.  
    TileMode_FlipX,
    
    /// The same as Tile except that alternate rows of tiles are flipped vertically. The base tile 
    /// itself is not flipped.  
    TileMode_FlipY,
    
    /// The combination of FlipX and FlipY. The base tile itself is not flipped.  
    TileMode_FlipXY
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Indicates where an element should be displayed on the vertical axis relative to the
/// allocated layout slot of the parent element.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum VerticalAlignment
{
    /// Element aligned to the top of the parent's layout slot
    VerticalAlignment_Top,

    /// Element aligned to the center of the parent's layout slot
    VerticalAlignment_Center,

    /// Element aligned to the bottom of the parent's layout slot
    VerticalAlignment_Bottom,

    /// Element stretches to fill the parent's layout slot
    VerticalAlignment_Stretch
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the display state of an element.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum Visibility
{
    /// Do not display the element, do not reserve space for it in layout
    Visibility_Collapsed,

    /// Do not display the element, but reserve space for it in layout
    Visibility_Hidden,

    /// Display the element
    Visibility_Visible
};

}
}

NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::AlignmentX)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::AlignmentY)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::AutoToolTipPlacement)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::BindingMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::BitmapScalingMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::BrushMappingMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::CharacterCasing)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::ClickMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::ColorInterpolationMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::Dock)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::ExpandDirection)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::FillRule)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::FlowDirection)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::FontStretch)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::FontStyle)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::FontWeight)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::GeometryCombineMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::GradientSpreadMethod)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::HorizontalAlignment)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::KeyboardNavigationMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::LineStackingStrategy)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::ListSortDirection)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::MenuItemRole)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::Orientation)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::OverflowMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::PenLineCap)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::PenLineJoin)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::PlacementMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::PopupAnimation)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::RelativeSourceMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::SelectionMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::ScrollBarVisibility)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::Stretch)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::StretchDirection)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::TextAlignment)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::TextTrimming)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::TextWrapping)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::TickBarPlacement)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::TickPlacement)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::TileMode)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::VerticalAlignment)
NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::Visibility)


#endif
