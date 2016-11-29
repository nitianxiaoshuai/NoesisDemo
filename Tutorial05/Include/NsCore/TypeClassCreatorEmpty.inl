////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/TypeClassBuilderProxy.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/Error.h>


namespace Noesis
{
namespace Core
{

// Forward declarations
//@{
class TypeInfo;
typedef NullType NoParent;
template<class T> struct T2T;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class BaseT>
TypeClassCreatorEmpty<ClassT, BaseT>::TypeClassCreatorEmpty(TypeClassBuilder* typeClass):
    mTypeClass(typeClass)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class BaseT>
Type* TypeClassCreatorEmpty<ClassT, BaseT>::Create(const TypeInfo& typeInfo)
{
    return CreateTypeClass(typeInfo, IsInterface<ClassT>::Result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class BaseT>
void TypeClassCreatorEmpty<ClassT, BaseT>::Fill(Type* type)
{
    TypeClassCreatorEmpty<ClassT, BaseT> helper((TypeClassBuilder*)(type));

    helper.Base<BaseT>(Int2Type<IsSame<BaseT, NoParent>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class BaseT>
template<class T>
void TypeClassCreatorEmpty<ClassT, BaseT>::Base(Int2Type<0>)
{
    enum { isDerived = IsDerived<ClassT, T>::Result };
    NS_STATIC_ASSERT(isDerived, __CLASS_DOES_NOT_DERIVE_FROM_SPECIFIED_BASE);

    NsSize (*CalculateParentOffset_)() = &CalculateParentOffset<ClassT, T>;
    NS_ASSERT(CalculateParentOffset_() == 0);

    AddBase(mTypeClass, T::StaticGetClassType((T2T<T>*)0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class BaseT>
template<class T>
void TypeClassCreatorEmpty<ClassT, BaseT>::Base(Int2Type<1>)
{
}

}
}
