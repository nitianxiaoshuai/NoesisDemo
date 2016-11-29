////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1362]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_NULLABLECONVERTER_H__
#define __CORE_NULLABLECONVERTER_H__


#include <Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/BasicConverters.h>
#include <NsCore/Converter.h>
#include <NsCore/Nullable.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeConverter for nullable NsBool type
////////////////////////////////////////////////////////////////////////////////////////////////////
class NullableBooleanConverter: public BooleanConverter
{
public:
    /// From ITypeConverter
    //@{
    NsBool CanConvertFrom(const Type* type) const;
    NsBool CanConvertTo(const Type* type) const;
    NsBool TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const;
    NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    NsBool TryConvertTo(BaseComponent* object, const Type* type, Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}

    NS_DECLARE_REFLECTION(NullableBooleanConverter, BooleanConverter)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeConverter template for all nullable integer and float types
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class NullableNumericConverter: public NumericConverter<T>
{
public:
    /// From ITypeConverter
    //@{
    NsBool CanConvertFrom(const Type* type) const;
    NsBool CanConvertTo(const Type* type) const;
    NsBool TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const;
    NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    NsBool TryConvertTo(BaseComponent* object, const Type* type,
        Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION(NullableNumericConverter, NumericConverter<T>)
    {
        NsMeta<TypeId>(IdOf<Nullable<T> >("Converter"));
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class to create TypeConverters for nullable classes that implement the method:
///     (type) Parse(const NsChar* str)
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class NullableConverter: public Converter<T>
{
public:
    /// From ITypeConverter
    //@{
    NsBool CanConvertFrom(const Type* type) const;
    NsBool CanConvertTo(const Type* type) const;
    NsBool TryConvertFrom(BaseComponent* object,  Ptr<BaseComponent>& result) const;
    NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    NsBool TryConvertTo(BaseComponent* object, const Type* type, Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}
    
    NS_IMPLEMENT_INLINE_REFLECTION(NullableConverter, Converter<T>)
    {
        NsMeta<TypeId>(IdOf<Nullable<T> >("Converter"));
    }
};

}
}

#include "NullableConverter.inl"


#endif
