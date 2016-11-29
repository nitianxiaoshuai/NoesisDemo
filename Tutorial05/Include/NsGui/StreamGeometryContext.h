////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STREAMGEOMETRYCONTEXT_H__
#define __GUI_STREAMGEOMETRYCONTEXT_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/Ptr.h>
#include <NsDrawing/Path.h>


NS_SFORWARD(Drawing, Point)
NS_SFORWARD(Drawing, Size)
NS_CFORWARD(Gui, StreamGeometry)


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines the direction an elliptical arc is drawn.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum SweepDirection
{
    /// Specifies that arcs are drawn in a counter clockwise (negative-angle) direction
    SweepDirection_Counterclockwise,
    /// Specifies that arcs are drawn in a clockwise (positive-angle) direction
    SweepDirection_Clockwise
};

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes a geometry using drawing commands. This class is used with the StreamGeometry class
/// to create a lightweight geometry that does not support data binding, animation, or modification.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API StreamGeometryContext
{
public:
    /// Destructor
    ~StreamGeometryContext();

    /// Specifies the starting point for a new figure
    void BeginFigure(const Drawing::Point& startPoint, NsBool isClosed) const;

    /// Draws a straight line to the specified Point
    void LineTo(const Drawing::Point& point) const;
    
    /// Draws a cubic Bezier curve to the specified point
    void CubicTo(const Drawing::Point& point1, const Drawing::Point& point2,
        const Drawing::Point& point3) const;

    /// Draws a quadratic Bezier curve to the specified point
    void QuadraticTo(const Drawing::Point& point1, const Drawing::Point& point2) const;
    
    /// Draws a G1 smooth cubic Bezier curve to the specified point
    void SmoothCubicTo(const Drawing::Point& point1, const Drawing::Point& point2) const;

    /// Draws a G1 smooth quadratic Bezier curve to the specified point
    void SmoothQuadraticTo(const Drawing::Point& point) const;

    /// Draws an arc to the specified point
    void ArcTo(const Drawing::Point& point, const Drawing::Size& size, NsFloat32 rotationAngleDeg,
        NsBool isLargeArc, SweepDirection sweepDirection) const;

    /// Closes this context and flushes its content so that it can be rendered. 
    void Close() const;

private:
    friend class StreamGeometry;
    StreamGeometryContext(StreamGeometry* geometry);
    StreamGeometryContext& operator=(const StreamGeometryContext&);

    void CloseFigure() const;

private:
    Ptr<StreamGeometry> mGeometry;
    mutable Drawing::PathContext mPathContext;
    mutable NsBool mCurrentFigureClosed;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
