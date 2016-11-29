////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_PATH_H__
#define __DRAWING_PATH_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsDrawing/TypesApi.h>
#include <NsCore/Vector.h>
#include <NsCore/FixedVector.h>


NS_SFORWARD(Drawing, Rect)
NS_SFORWARD(Drawing, Point)
NS_SFORWARD(Drawing, PathCommandIterator)


namespace Noesis
{
namespace Drawing
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Paths represent the geometry of the outline of an object
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API Path
{
    /// Empty path constructor
    Path();

    /// Builds a path from SVG path commands as described in http://www.w3.org/TR/SVG11/paths.html
    /// Example: "M 100, 100 L 200, 100 200, 200 Z"
    Path(const NsChar* svgCommands, NsBool reverseCw = false);

    /// Parses a string value to create an instance of a Path
    static NsBool TryParse(const NsChar* str, Path& result, NsBool reverseCw = false);

    /// Resets the path to an empty one
    void Clear();

    /// Rebuilds the path with a new set of SVG path commands
    void SetCommands(const NsChar* svgCommands, NsBool reverseCw = false);

    /// Returns an iterator of commands describing the path
    PathCommandIterator GetCommands() const;

    /// Calculates path bounds
    Rect CalculateBounds() const;

    /// Indicates whether the path contains the specified point
    NsBool FillContains(const Point& point) const;

    /// Determines whether the specified point is contained in the given stroke
    NsBool StrokeContains(const Point& point, NsFloat32 strokeThickness) const;

public:
    /// Override default fill rule when drawing this path
    NsBool overrideFillRule;

    enum FillRule
    {
        FillRule_EvenOdd,
        FillRule_NonZero
    };

    FillRule fillRule;

    NsVector<NsUInt32> commands;

    NS_DECLARE_REFLECTION(Path, Core::NoParent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Move
{
    NsBool absolute;
    NsFloat32 x, y;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Line
{
    NsBool absolute;
    NsFloat32 x, y;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct HLine
{
    NsBool absolute;
    NsFloat32 coord;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct VLine
{
    NsBool absolute;
    NsFloat32 coord;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Cubic
{
    NsBool absolute;
    NsFloat32 x0, y0;
    NsFloat32 x1, y1;
    NsFloat32 x2, y2;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Quadratic
{
    NsBool absolute;
    NsFloat32 x0, y0;
    NsFloat32 x1, y1;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct SmoothCubic
{
    NsBool absolute;
    NsFloat32 x0, y0;
    NsFloat32 x1, y1;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct SmoothQuadratic
{
    NsBool absolute;
    NsFloat32 x0, y0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Arc
{
    NsFloat32 rx, ry;
    NsFloat32 rot;
    NsFloat32 x, y;
    
    NsBool isLarge;
    NsBool isCw;
    NsBool absolute;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FigureCommand
{
    FigureCommand_Move,
    FigureCommand_Line,
    FigureCommand_HLine,
    FigureCommand_VLine,
    FigureCommand_Cubic,
    FigureCommand_Quadratic,
    FigureCommand_SmoothCubic,
    FigureCommand_SmoothQuadratic,
    FigureCommand_Arc,
    FigureCommand_Close
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Command
{
    FigureCommand figureCommand;

    union
    {
        Move move;
        Line line;
        HLine hLine;
        VLine vLine;
        Cubic cubic;
        Quadratic quadratic;
        SmoothCubic smoothCubic;
        SmoothQuadratic smoothQuadratic;
        Arc arc;
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API PathContext
{
    void PushCommand(const Command& command);
    NsFixedVector<NsUInt32, 512> commands;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API PathCommandIterator
{
    PathCommandIterator(const NsUInt32* data, const NsUInt32* end);
    PathCommandIterator(const PathCommandIterator& it);

    NsBool End() const;
    Command Next();

private:
    PathCommandIterator operator=(const PathCommandIterator&);

    const NsUInt32* mData;
    const NsUInt32* const mEnd;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
