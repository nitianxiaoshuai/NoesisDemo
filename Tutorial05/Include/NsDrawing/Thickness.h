////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_THICKNESS_H__
#define __DRAWING_THICKNESS_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsDrawing/TypesApi.h>
#include <NsCore/NSTLForwards.h>


namespace Noesis
{

namespace Drawing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Thickness. Describes the thickness of a frame around a rectangle.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API Thickness
{
    NsFloat32 left;
    NsFloat32 top;
    NsFloat32 right;
    NsFloat32 bottom;

    /// Constructor
    //@{
    Thickness(NsFloat32 thickness = 0);
    Thickness(NsFloat32 l, NsFloat32 t, NsFloat32 r, NsFloat32 b);

    /// Copy constructor
    Thickness(const Thickness& thickness);

    /// Copy operator
    Thickness operator=(const Thickness& thickness);

    /// Comparisson operators
    //@{
    NsBool operator==(const Thickness& thickness) const;
    NsBool operator!=(const Thickness& thickness) const;
    //@}

    /// Creates a string representation of this thickness structure
    /// The string has the following form: "left,top,right,bottom" or "left,top" or "left"
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Converts a string into the equivalent thickness structure
    static Thickness Parse(const NsChar* str);

    /// Safe version of Parse function
    static NsBool TryParse(const NsChar* str, Thickness& result);

    NS_DECLARE_REFLECTION(Thickness, Core::NoParent)
};

}
}

#endif
