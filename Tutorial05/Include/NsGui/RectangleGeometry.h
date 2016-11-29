////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RECTANGLEGEOMETRY_H__
#define __GUI_RECTANGLEGEOMETRY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Geometry.h>
#include <NsDrawing/Rect.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes a two-dimensional rectangle. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.rectanglegeometry.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RectangleGeometry: public Geometry
{
public:
    /// Constructor
    RectangleGeometry();

    /// Constructor
    RectangleGeometry(const Drawing::Rect& rect, NsFloat32 rX = 0.0f, NsFloat32 rY = 0.0f);

    /// Gets or sets the x-radius of the ellipse use to round the corners of the rectangle.
    //@{
    NsFloat32 GetRadiusX() const;
    void SetRadiusX(NsFloat32 value);
    //@}
    
    /// Gets or sets the y-radius of the ellipse use to round the corners of the rectangle.
    //@{
    NsFloat32 GetRadiusY() const;
    void SetRadiusY(NsFloat32 value);
    //@}
    
    /// Gets or sets the dimensions of the rectangle
    //@{
    const Drawing::Rect& GetRect() const;
    void SetRect(const Drawing::Rect& value);
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
    /// Dependency properties
    //@{
    static const DependencyProperty* RadiusXProperty;
    static const DependencyProperty* RadiusYProperty;
    static const DependencyProperty* RectProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Geometry
    //@{
    Drawing::Rect GetRenderBoundsOverride(Pen* pen) const;
    NsBool FillContainsOverride(const Drawing::Point& point) const;
    NsBool StrokeContainsOverride(Pen* pen, const Drawing::Point& point) const;
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_Rect = Geometry::UpdateFlags_Sentinel,
        UpdateFlags_RadiusX,
        UpdateFlags_RadiusY
    };

    NS_DECLARE_REFLECTION(RectangleGeometry, Geometry)
};

}
}

#endif
