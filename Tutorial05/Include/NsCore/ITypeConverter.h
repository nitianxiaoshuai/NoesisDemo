////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #710]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_ITYPECONVERTER_H__
#define __CORE_ITYPECONVERTER_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsCore/NSTLForwards.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
template<class T> class Ptr;
class BaseComponent;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a unified way of converting types of values to other types, as well as for accessing
/// standard values and subproperties.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE ITypeConverter: public Interface
{
public:
    /// Returns whether this converter can convert from the given type
    virtual NsBool CanConvertFrom(const Type* type) const = 0;

    /// Returns whether this converter can convert to the given type
    virtual NsBool CanConvertTo(const Type* type) const = 0;

    /// Converts the given value to the type of this converter
    virtual Ptr<BaseComponent> ConvertFrom(BaseComponent* object) const = 0;

    /// Safe version of ConvertFrom
    virtual NsBool TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const = 0;

    /// Converts the specified text to an object
    virtual Ptr<BaseComponent> ConvertFromString(const NsChar* str) const = 0;

    /// Safe version of ConvertFromString
    virtual NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const = 0;
    
    /// Converts the given value object to the specified type
    virtual Ptr<BaseComponent> ConvertTo(BaseComponent* object, const Type* type) const = 0;

    /// Safe version of ConvertTo
    virtual NsBool TryConvertTo(BaseComponent* object, const Type* type,
        Ptr<BaseComponent>& result) const = 0;

    /// Converts the specified value to a string representation
    virtual NsString ConvertToString(BaseComponent* object) const = 0;

    /// Safe version of ConvertToString
    virtual NsBool TryConvertToString(BaseComponent* object, NsString& result) const = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(ITypeConverter, Interface)
};

}
}

#endif