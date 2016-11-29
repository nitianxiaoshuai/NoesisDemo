////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #868]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_SIZE_H__
#define __DRAWING_SIZE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsDrawing/TypesApi.h>
#include <NsCore/NSTLForwards.h>


namespace Noesis
{
// Forward declarations
//@{
namespace Drawing
{
struct Size;
struct Sizei;
struct Point;
struct Pointi;
}
//@}

namespace Drawing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Size. Describes the size of an object.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API Size
{
    NsFloat32 width;
    NsFloat32 height;

    /// Constructor
    inline Size(NsFloat32 w = 0.0f, NsFloat32 h = 0.0f);

    /// Constructor from integer Sizei
    inline Size(const Sizei& size);

    /// Constructor from a Point
    explicit Size(const Point& point);

    /// Copy constructor
    inline Size(const Size& size);

    /// Copy operator
    inline Size& operator=(const Size& size);

    /// Comparison operators
    //@{
    inline NsBool operator==(const Size& size) const;
    inline NsBool operator!=(const Size& size) const;
    //@}

    /// Math operators
    //@{
    inline Size operator+(const Size& size) const;
    inline Size operator-(const Size& size) const;
    inline Size operator*(NsFloat32 k) const;
    inline Size operator/(NsFloat32 k) const;
    inline Size& operator+=(const Size& size);
    inline Size& operator-=(const Size& size);
    inline Size& operator*=(NsFloat32 k);
    inline Size& operator/=(NsFloat32 k);
    //@}

    /// Expands width and height with the specified size
    inline void Expand(const Size& size);

    /// Scales width and height by a factor
    inline void Scale(NsFloat32 scaleX, NsFloat32 scaleY);

    /// Generates a string representation of the size
    /// The string has the following form: "width,height"
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Creates a size from the specified string
    static Size Parse(const NsChar* str);

    /// Safe version of parse function
    static NsBool TryParse(const NsChar* str, Size& result);

    /// Empty size (width and height of 0)
    inline static Size Zero();

    /// Infinite size (defined as the higher positive integer)
    inline static Size Infinite();

    NS_DECLARE_REFLECTION(Size, Core::NoParent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Sizei. Describes the integer size of an object.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API Sizei
{
    NsSize width;
    NsSize height;

    /// Constructor
    inline Sizei(NsSize w = 0, NsSize h = 0);

    /// Constructor from a float size
    inline Sizei(const Size& size);

    /// Constructor from a Pointi
    explicit Sizei(const Pointi& point);

    /// Copy constructor
    inline Sizei(const Sizei& size);

    /// Copy operator
    inline Sizei& operator=(const Sizei& size);

    /// Comparison operators
    //@{
    inline NsBool operator==(const Sizei& size) const;
    inline NsBool operator!=(const Sizei& size) const;
    //@}

    /// Math operators
    //@{
    inline Sizei operator+(const Sizei& size) const;
    inline Sizei operator-(const Sizei& size) const;
    inline Sizei operator*(NsSize k) const;
    inline Sizei operator/(NsSize k) const;
    inline Sizei& operator+=(const Sizei& size);
    inline Sizei& operator-=(const Sizei& size);
    inline Sizei& operator*=(NsSize k);
    inline Sizei& operator/=(NsSize k);
    //@}

    /// Expands width and height with the specified size
    inline void Expand(const Sizei& size);

    /// Scales width and height by a factor
    inline void Scale(NsSize scaleX, NsSize scaleY);

    /// Generates a string representation of the size
    /// The string has the following form: "width,height"
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Creates a size from the specified string
    static Sizei Parse(const NsChar* str);

    /// Safe version of parse function
    static NsBool TryParse(const NsChar* str, Sizei& result);

    /// Empty size (width and height of 0)
    inline static Sizei Zero();

    /// Infinite size (defined as the higher positive integer)
    inline static Sizei Infinite();

    NS_DECLARE_REFLECTION(Sizei, Core::NoParent)
};

}
}

#include <NsDrawing/Size.inl>

#endif
