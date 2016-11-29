////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #868]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_POINT_H__
#define __DRAWING_POINT_H__


#include <Noesis.h>
#include <NsDrawing/TypesApi.h>
#include <NsDrawing/Size.h>
#include <NsMath/Vector.h>
#include <NsCore/NSTLForwards.h>


NS_SFORWARD(Drawing, Point)
NS_SFORWARD(Drawing, Pointi)


namespace Noesis
{
namespace Drawing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Point. Represents an x- and y-coordinate pair in two-dimensional space.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct Point: public Noesis::Math::Vector2f
{
    /// Default constructor that creates a (0,0) point
    inline Point();

    /// Constructor for x, y
    inline Point(NsFloat32 x, NsFloat32 y);

    /// Construct from Pointi
    inline Point(const Pointi& point);

    /// Constructor from Math::Vector
    inline Point(const Math::Vector2f& v);

    /// Constructor from size
    explicit inline Point(const Size& size);

    /// Copy constructor
    inline Point(const Point& point);

    /// Copy operator
    inline Point& operator=(const Point& point);

    /// Generates a string representation of the point
    /// The string has the following form: "x,y"
    NS_DRAWING_TYPES_API NsString ToString() const;

    /// Creates a Point from the specified string
    NS_DRAWING_TYPES_API static Point Parse(const NsChar* str);

    /// Safe function for Parse
    NS_DRAWING_TYPES_API static NsBool TryParse(const NsChar* str, Point& result);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Pointi. Represents an x- and y-coordinate pair in integer two-dimensional space.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct Pointi: public Noesis::Math::Vector2i
{
    /// Default constructor that creates a (0,0) point
    inline Pointi();

    /// Constructor for x, y
    inline Pointi(NsInt x, NsInt y);

    /// Constructor from float Point
    inline Pointi(const Point& p);

    /// Constructor from Math::Vector
    inline Pointi(const Math::Vector2i& v);

    /// Constructor from size
    explicit inline Pointi(const Sizei& size);

    /// Copy constructor
    inline Pointi(const Pointi& point);

    /// Copy operator
    inline Pointi& operator=(const Pointi& point);

    /// Generates a string representation of the point
    /// The string has the following form: "x,y"
    NS_DRAWING_TYPES_API NsString ToString() const;

    /// Creates a Pointi from the specified string
    NS_DRAWING_TYPES_API static Pointi Parse(const NsChar* str);

    /// Safe function for Parse
    NS_DRAWING_TYPES_API static NsBool TryParse(const NsChar* str, Pointi& result);
};

}
}

#include <NsDrawing/Point.inl>

#endif
