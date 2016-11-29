////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TILEBRUSH_H__
#define __GUI_TILEBRUSH_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Brush.h>
#include <NsGui/Enums.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Drawing
{
struct Rect;
}
namespace Gui
{
struct TileBrushProxy;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes a way to paint a region by using one or more tiles.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.tilebrush.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TileBrush: public Brush
{
public:
    /// Constructor
    TileBrush();

    /// Pure virtual destructor
    virtual ~TileBrush() = 0;

    /// Gets or sets the horizontal alignment of content in the TileBrush base tile
    //@{
    AlignmentX GetAlignmentX() const;
    void SetAlignmentX(AlignmentX value);
    //@}

    /// Gets or sets the vertical alignment of content in the TileBrush base tile
    //@{
    AlignmentY GetAlignmentY() const;
    void SetAlignmentY(AlignmentY value);
    //@}

    /// Gets or sets a value that specifies how the content of this TileBrush stretches to fit its 
    /// tiles
    //@{
    Stretch GetStretch() const;
    void SetStretch(Stretch value);
    //@}

    /// Gets or sets a value that specifies how a TileBrush fills the area that you are painting if 
    /// the base tile is smaller than the output area. 
    //@{
    TileMode GetTileMode() const;
    void SetTileMode(TileMode value);
    //@}

    /// Gets or sets the position and dimensions of the content in a TileBrush tile.
    //@{
    const Drawing::Rect& GetViewbox() const;
    void SetViewbox(const Drawing::Rect& rect);
    //@}

    /// Gets or sets a value that specifies whether the Viewbox value is relative to the bounding
    /// box of the TileBrush contents or whether the value is absolute
    //@{
    BrushMappingMode GetViewboxUnits() const;
    void SetViewboxUnits(BrushMappingMode units);
    //@}

    /// Gets or sets the position and dimensions of the base tile for a TileBrush. 
    //@{
    const Drawing::Rect& GetViewport() const;
    void SetViewport(const Drawing::Rect& rect);
    //@}

    /// Gets or sets a BrushMappingMode enumeration that specifies whether the value of the 
    /// Viewport, which indicates the size and position of the TileBrush base tile, is relative to 
    /// the size of the output area.
    //@{
    BrushMappingMode GetViewportUnits() const;
    void SetViewportUnits(BrushMappingMode units);
    //@}

    /// From IRenderProxyCreator
    //@{
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* AlignmentXProperty;
    static const DependencyProperty* AlignmentYProperty;
    static const DependencyProperty* StretchProperty;
    static const DependencyProperty* TileModeProperty;
    static const DependencyProperty* ViewboxProperty;
    static const DependencyProperty* ViewboxUnitsProperty;
    static const DependencyProperty* ViewportProperty;
    static const DependencyProperty* ViewportUnitsProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

protected:
    enum UpdateFlags
    {
        UpdateFlags_AlignmentX = Brush::UpdateFlags_Sentinel,
        UpdateFlags_AlignmentY,
        UpdateFlags_Stretch,
        UpdateFlags_TileMode,
        UpdateFlags_Viewbox,
        UpdateFlags_ViewboxUnits,
        UpdateFlags_Viewport,
        UpdateFlags_ViewportUnits,

        UpdateFlags_Sentinel
    };

private:
    /// Base classes are non-copyable objects
    //@{
    TileBrush(const TileBrush&);
    TileBrush& operator=(const TileBrush&);
    //@}

    NS_DECLARE_REFLECTION(TileBrush, Brush)
};

}
}

#endif
