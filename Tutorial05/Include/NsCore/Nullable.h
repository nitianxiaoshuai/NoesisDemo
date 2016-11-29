////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1336]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_NULLABLE_H__
#define __CORE_NULLABLE_H__


#include <Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/IdOf.h>
#include <NsCore/TypeId.h>
#include <NsCore/NullableApi.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for Nullable objects
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_NULLABLE_API BaseNullable
{
public:
    /// Indicates if a valid value or a null is stored
    inline NsBool HasValue() const;
    
protected:
    /// Constructor
    inline BaseNullable(NsBool hasValue);
    
protected:
    NsBool mHasValue;

    NS_DECLARE_REFLECTION(BaseNullable, Core::NoParent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A nullable type can represent the normal range of values for its underlying value type, plus an 
/// additional null value. For example, Nullable<NsBool> can be assigned a boolean value or it can
/// be assigned the null value (meaning "not assigned")
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class Nullable: public BaseNullable
{
public:
    /// Default constructor
    inline Nullable();
    
    /// Constructor from a simple value
    inline Nullable(typename Param<T>::Type value);

    /// Get the stored value
    /// \remarks This method must be called only if the stored value is non null. This can be
    ///     checked with a previous call to HasValue() method.
    inline typename Param<T>::Type GetValue() const;

    /// Assigns a value from a simple one
    inline Nullable<T>& operator=(typename Param<T>::Type value);
    
    /// Equality and inequality operators
    //@{
    inline NsBool operator==(const Nullable<T>& other) const;
    inline NsBool operator!=(const Nullable<T>& other) const;
    inline NsBool operator==(typename Param<T>::Type value) const;
    inline NsBool operator!=(typename Param<T>::Type value) const;
    //@}

    /// Returns a string that represents the current nullable
    NsString ToString() const;

    /// Returns a hash code for the current nullable
    NsUInt32 GetHashCode() const;

private:
    T mValue;

    NS_IMPLEMENT_INLINE_REFLECTION(Nullable, BaseNullable)
    {
        NsMeta<Core::TypeId>(Core::IdOf<T>("Nullable"));
    }
};

}
}


#include "Nullable.inl"


#endif
