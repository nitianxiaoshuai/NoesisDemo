////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #710]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_ENUMCONVERTER_H__
#define __CORE_ENUMCONVERTER_H__


#include <Noesis.h>
#include <NsCore/TypeConverterApi.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/BaseConverter.h>
#include <NsCore/TypeId.h>
#include <NsCore/IdOf.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_TYPECONVERTER_API BaseEnumConverter: public BaseConverterBothWays
{
public:
    BaseEnumConverter(const TypeEnum* type);

    /// From ITypeConverter
    //@{
    NsBool CanConvertFrom(const Type* type) const;
    NsBool CanConvertTo(const Type* type) const;
    NsBool TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const;
    NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    NsBool TryConvertTo(BaseComponent* object, const Type* type, Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}

private:
    virtual Ptr<BaseComponent> Box(NsUInt32 v) const = 0;
    virtual NsUInt32 Unbox(BaseComponent* value) const = 0;
    virtual NsBool CanUnbox(BaseComponent* value) const = 0;

private:
    const TypeEnum* mType;

    NS_DECLARE_REFLECTION(BaseEnumConverter, BaseConverterBothWays)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// EnumConverter. TypeConverter template for all enum types
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class EnumConverter: public BaseEnumConverter
{
public:
    EnumConverter();

private:
    Ptr<BaseComponent> Box(NsUInt32 v) const;
    NsUInt32 Unbox(BaseComponent* value) const;
    NsBool CanUnbox(BaseComponent* value) const;

private:
    NS_IMPLEMENT_INLINE_REFLECTION(EnumConverter, BaseEnumConverter)
    {
        NsMeta<TypeId>(IdOf<T>("Converter"));
    }
};

}
}

#include <NsCore/EnumConverter.inl>


#endif
