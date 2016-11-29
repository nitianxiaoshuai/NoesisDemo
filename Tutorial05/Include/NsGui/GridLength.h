////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRIDLENGTH_H__
#define __GUI_GRIDLENGTH_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/NSTLForwards.h>


namespace Noesis
{

namespace Gui
{

/// Describes the kind of value that a GridLength object is holding. 
enum GridUnitType
{
    /// The size is determined by the size properties of the content object.
    GridUnitType_Auto,
    /// The value is expressed as a pixel.
    GridUnitType_Pixel,
    /// Star The value is expressed as a weighted proportion of available space.
    GridUnitType_Star
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// GridLength. Represents the length of elements that explicitly support Star unit types.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API GridLength
{
public:
    /// Default Constructor
    GridLength();

    /// Constructor using the specified absolute value in pixels
    GridLength(NsFloat32 value);

    /// Constructor which specifies what kind of value it holds
    GridLength(NsFloat32 value, GridUnitType type);

    /// Associated GridUnitType for the GridLength.  
    GridUnitType GetGridUnitType() const;

    /// Indicates whether the GridLength holds a value that is expressed in pixels.  
    NsBool IsAbsolute() const;

    /// Indicates whether the GridLength holds a value whose size is determined by the size 
    /// properties of the content object.  
    NsBool IsAuto() const;

    /// Indicates whether the GridLength holds a value that is expressed as a weighted proportion of 
    /// available space.  
    NsBool IsStar() const;

    /// Gets a float that represents the value of the GridLength. 
    NsFloat32 GetValue() const;

    /// Copy constructor
    GridLength(const GridLength& gridLength);

    /// Copy operator
    GridLength& operator=(const GridLength& gridLength);

    /// Comparison operators
    //@{
    NsBool operator==(const GridLength& gridLength) const;
    NsBool operator!=(const GridLength& gridLength) const;
    //@}

    /// Creates a string representation of this thickness structure
    /// The string has the following form: "left,top,right,bottom" or "left,top" or "left"
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Converts a string into the equivalent thickness structure
    static GridLength Parse(const NsChar* str);
    static NsBool TryParse(const NsChar* str, GridLength& result);

private:
    GridUnitType mGridUnitType;
    NsFloat32 mValue;

    NS_DECLARE_REFLECTION(GridLength, Core::NoParent)
};

}
}

#endif
