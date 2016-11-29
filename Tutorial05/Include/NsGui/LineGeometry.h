////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LINEGEOMETRY_H__
#define __GUI_LINEGEOMETRY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Geometry.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Drawing
{
struct Point;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the geometry of a line. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.linegeometry.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API LineGeometry: public Geometry
{
public:
    /// Constructor
    LineGeometry();

    /// Constructor with start and end points
    LineGeometry(const Drawing::Point& p1, const Drawing::Point& p2);

    /// Gets or sets the end point of a line.
    //@{
    const Drawing::Point& GetEndPoint() const;
    void SetEndPoint(const Drawing::Point& end);
    //@}
    
    /// Gets or sets the start point of the line.
    //@{
    const Drawing::Point& GetStartPoint() const;
    void SetStartPoint(const Drawing::Point& start);
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
    static const DependencyProperty* EndPointProperty;
    static const DependencyProperty* StartPointProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Geometry
    //@{
    Drawing::Rect GetRenderBoundsOverride(Pen* pen) const;
    NsBool StrokeContainsOverride(Pen* pen, const Drawing::Point& point) const;
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_StartPoint = Geometry::UpdateFlags_Sentinel,
        UpdateFlags_EndPoint
    };

    NS_DECLARE_REFLECTION(LineGeometry, Geometry)
};

}
}

#endif