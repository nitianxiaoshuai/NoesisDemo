////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ELLIPSEGEOMETRY_H__
#define __GUI_ELLIPSEGEOMETRY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Geometry.h>


namespace Noesis
{

// Forward declaration
//@{
namespace Drawing
{
struct Point;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the geometry of a circle or ellipse. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.ellipsegeometry.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API EllipseGeometry: public Geometry
{
public:
    /// Constructor
    EllipseGeometry();

    /// Constructor with ellipse parameters
    EllipseGeometry(const Drawing::Point& center, NsFloat32 rX, NsFloat32 rY);

    /// Gets or sets the center point
    //@{
    const Drawing::Point& GetCenter() const;
    void SetCenter(const Drawing::Point& center);
    //@}

    /// Gets or sets the x-radius value
    //@{
    NsFloat32 GetRadiusX() const;
    void SetRadiusX(NsFloat32 value);
    //@}

    /// Gets or sets the y-radius value
    //@{
    NsFloat32 GetRadiusY() const;
    void SetRadiusY(NsFloat32 value);
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
    static const DependencyProperty* CenterProperty;
    static const DependencyProperty* RadiusXProperty;
    static const DependencyProperty* RadiusYProperty;
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
        UpdateFlags_Center = Geometry::UpdateFlags_Sentinel,
        UpdateFlags_RadiusX,
        UpdateFlags_RadiusY
    };

    NS_DECLARE_REFLECTION(EllipseGeometry, Geometry)
};

}
}

#endif
