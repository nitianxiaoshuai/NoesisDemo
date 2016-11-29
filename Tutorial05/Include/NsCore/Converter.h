////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #710]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_CONVERTER_H__
#define __CORE_CONVERTER_H__


#include <Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/IdOf.h>
#include <NsCore/BaseConverter.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper class to create TypeConverters for classes that implement the method TryParse
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class Converter: public BaseConverterBothWays
{
public:
    /// From ITypeConverter
    //@{
    NsBool TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}
    
private:
    typedef Int2Type<0> IsStruct;
    typedef Int2Type<1> IsComponent;

    NsBool TryConvertFromString(const NsChar* str, IsStruct, Ptr<BaseComponent>& result) const;
    NsBool TryConvertFromString(const NsChar* str, IsComponent, Ptr<BaseComponent>& result) const;

    NsBool TryConvertToString(BaseComponent* object, IsStruct, NsString& result) const;
    NsBool TryConvertToString(BaseComponent* object, IsComponent, NsString& result) const;

    NS_IMPLEMENT_INLINE_REFLECTION(Converter, BaseConverterBothWays)
    {
        NsMeta<TypeId>(IdOf<T>("Converter"));
    }
};

}
}

#include <NsCore/Converter.inl>


#endif
