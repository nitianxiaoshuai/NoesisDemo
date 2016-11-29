////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEENUMIMPL_H__
#define __CORE_TYPEENUMIMPL_H__


#include <Noesis.h>
#include <NsCore/TypeEnum.h>
#include <NsCore/ReflectionImplementEmpty.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implementation of TypeEnum specialized for T
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class TypeEnumImpl: public TypeEnum
{
public:
    TypeEnumImpl(const TypeInfo& typeInfo);

    /// From TypeEnum
    //@{
    Ptr<BoxedValue> GetValueObject(NsSymbol id) const;
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION_(TypeEnumImpl, TypeEnum)
};

}
}

// Inline Include
#include <NsCore/TypeEnumImpl.inl>


#endif
