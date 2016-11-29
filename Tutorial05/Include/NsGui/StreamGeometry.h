////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STREAMGEOMETRY_H__
#define __GUI_STREAMGEOMETRY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Geometry.h>
#include <NsGui/Enums.h>
#include <NsDrawing/Rect.h>
#include <NsDrawing/Path.h>


NS_CFORWARD(Gui, StreamGeometryContext)


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a geometric shape, described using a StreamGeometryContext or a SVG command string
/// as described in the `W3C <http://www.w3.org/TR/SVG11/paths.html>`_ specs.
///
/// .. code-block:: c#
///
///    var geometry = new StreamGeometry();
///
///    using (var context = geometry.Open())
///    {
///        context.BeginFigure(new Point(100.0f, 100.0f), true);
///        context.LineTo(new Point(200.0f, 100.0f));
///        context.LineTo(new Point(200.0f, 200.0f));
///    }
///
/// .. code-block:: c#
///
///    var geometry = new StreamGeometry();
///    geometry.SetData("M 100, 100 L 200, 100 200, 200 Z");
///
/// .. code-block:: xml
///
///    <Canvas xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation">
///      <Path Fill="#FFF2F000" Data="M 100, 100 L 200, 100 200, 200 Z"/>
///    </Canvas>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.streamgeometry.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API StreamGeometry: public Geometry
{
public:
    /// Constructor
    StreamGeometry(const NsChar* data = "");

    /// Constructs a StreamGeometry from SVG path commands
    static Ptr<StreamGeometry> Parse(const NsChar* str);
    static NsBool TryParse(const NsChar* str, Ptr<BaseComponent>& result);

    /// Rebuild the geometry with a new set of `SVG <http://www.w3.org/TR/SVG11/paths.html>`_ 
    /// path commands
    ///
    /// Example:
    ///
    /// .. code-block:: xml
    ///
    ///     M 100, 100 L 200, 100 200, 200 Z
    void SetData(const NsChar* data);

    // Gets stream data
    const Drawing::Path& GetData() const;

    /// Constructs a stream geometry specifying drawing commands
    StreamGeometryContext Open();

    /// Gets or sets a value that determines how the intersecting areas contained in this 
    /// StreamGeometry are combined
    //@{
    Gui::FillRule GetFillRule() const;
    void SetFillRule(Gui::FillRule rule);
    //@}

    /// From Geometry
    //@{
    NsBool IsEmpty() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency property
    static const DependencyProperty* FillRuleProperty;

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}
    
    /// From Freezable
    //@{
    void CloneCommonCore(const Freezable* source);
    //@}

    /// From Geometry
    //@{
    Drawing::Rect GetRenderBoundsOverride(Pen* pen) const;
    NsBool FillContainsOverride(const Drawing::Point& point) const;
    NsBool StrokeContainsOverride(Pen* pen, const Drawing::Point& point) const;
    //@}

private:
    void Close();
    void UpdateFillRule();

private:
    friend class StreamGeometryContext;

    enum UpdateFlags
    {
        UpdateFlags_Path = Geometry::UpdateFlags_Sentinel,
        UpdateFlags_FillRule
    };

    Drawing::Path mPath;
    mutable Drawing::Rect mBounds;

    NS_DECLARE_REFLECTION(StreamGeometry, Geometry)
};

}
}


#endif
