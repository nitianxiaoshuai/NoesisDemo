////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_CORNERRADIUS_H__
#define __DRAWING_CORNERRADIUS_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsDrawing/TypesApi.h>
#include <NsCore/String.h>


namespace Noesis
{

namespace Drawing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// CornerRadius. Represents the radii of rectangle corners.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API CornerRadius
{
    NsFloat32 topLeft;
    NsFloat32 topRight;
    NsFloat32 bottomRight;
    NsFloat32 bottomLeft;

    /// Constructor
    //@{
    CornerRadius(NsFloat32 radius = 0.0f);
    CornerRadius(NsFloat32 tl, NsFloat32 tr, NsFloat32 br, NsFloat32 bl);
    //@}

    /// Copy constructor
    CornerRadius(const CornerRadius& cornerRadius);

    /// Copy operator
    CornerRadius operator=(const CornerRadius& cornerRadius);

    /// Comparisson operators
    //@{
    NsBool operator==(const CornerRadius& cornerRadius) const;
    NsBool operator!=(const CornerRadius& cornerRadius) const;
    //@}

    /// Creates a string representation of this CornerRadius structure
    /// The string has the following form: "topLeft,topRight,bottomRight,bottomLeft" or "radius"
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Converts a string into the equivalent CornerRadius structure
    static CornerRadius Parse(const NsChar* str);

    /// Safe versiion of parse function
    static NsBool TryParse(const NsChar* str, CornerRadius& radius);

    NS_DECLARE_REFLECTION(CornerRadius, Core::NoParent)
};

}
}

#endif
