////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #710]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_BASICCONVERTERS_H__
#define __CORE_BASICCONVERTERS_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ITypeConverter.h>
#include <NsCore/BaseConverter.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/IdOf.h>
#include <NsCore/TypeId.h>
#include <NsCore/TypeConverterApi.h>
#include <NsCore/ReflectionImplement.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// BooleanConverter. TypeConverter for NsBool type
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_TYPECONVERTER_API BooleanConverter: public BaseConverterBothWays
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

    NsBool TryGetFromString(const NsChar* str, NsBool& result) const;

    NS_DECLARE_REFLECTION(BooleanConverter, BaseConverterBothWays)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeConverter template for all integers and floats.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class NumericConverter: public BaseConverterBothWays
{
public:
    /// From ITypeConverter
    //@{
    inline NsBool CanConvertFrom(const Type* type) const;
    inline NsBool CanConvertTo(const Type* type) const;
    inline NsBool TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const;
    inline NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    inline NsBool TryConvertTo(BaseComponent* object, const Type* type, 
        Ptr<BaseComponent>& result) const;
    inline NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}

    NsBool TryGetFromString(const NsChar* str, T& result) const;

protected:
    using BaseComponent::ToString;
    virtual NsString ToString(T value) const;

    NS_IMPLEMENT_INLINE_REFLECTION(NumericConverter, BaseConverterBothWays)
    {
        NsMeta<TypeId>(IdOf<T>("Converter"));
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// CharConverter. TypeConverter template for char type
////////////////////////////////////////////////////////////////////////////////////////////////////
class CharConverter: public BaseConverterBothWays
{
public:
    /// From ITypeConverter
    //@{
    NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}

    NS_DECLARE_REFLECTION(CharConverter, BaseConverterBothWays)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// StringConverter. TypeConverter template for string type
////////////////////////////////////////////////////////////////////////////////////////////////////
class StringConverter: public BaseConverterBothWays
{
public:
    /// From ITypeConverter
    //@{
    NsBool TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const;
    NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}

    NS_DECLARE_REFLECTION(StringConverter, BaseConverterBothWays)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// StringCharConverter. TypeConverter template for const char* type
////////////////////////////////////////////////////////////////////////////////////////////////////
class StringCharConverter: public StringConverter
{
public:
    NS_DECLARE_REFLECTION(StringCharConverter, StringConverter)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// SymbolConverter. TypeConverter for Symbol type
////////////////////////////////////////////////////////////////////////////////////////////////////
class SymbolConverter: public BaseConverterBothWays
{
public:
    /// From ITypeConverter
    //@{
    NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}

    NS_DECLARE_REFLECTION(SymbolConverter, BaseConverterBothWays)
};

}
}

#include "BasicConverters.inl"


#endif
