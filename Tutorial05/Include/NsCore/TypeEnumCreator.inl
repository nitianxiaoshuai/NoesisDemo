////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/TypeEnum.h>
#include <NsCore/TypeEnumImpl.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Core
{

// Forward declarations
//@{
template<class T> class TypeEnumImpl;
template<class T> struct TypeEnumFiller;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
TypeEnumCreator<EnumT>::TypeEnumCreator(TypeEnum* typeEnum): mTypeEnum(typeEnum)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
Type* TypeEnumCreator<EnumT>::Create(const TypeInfo& typeInfo)
{
    return new TypeEnumImpl<EnumT>(typeInfo);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
void TypeEnumCreator<EnumT>::Fill(Type* type)
{
    TypeEnumCreator<EnumT> helper(static_cast<TypeEnum*>(type));
    TypeEnumFiller<EnumT>::Fill(helper);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
template<class T>
void TypeEnumCreator<EnumT>::Meta()
{
    Ptr<TypeMetaData> metaData(*new T());
    mTypeEnum->GetMetaData().Add(metaData.GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
template<class T, class T1>
void TypeEnumCreator<EnumT>::Meta(T1 t1)
{
    Ptr<TypeMetaData> metaData(*new T(t1));
    mTypeEnum->GetMetaData().Add(metaData.GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
template<class T, class T1, class T2>
void TypeEnumCreator<EnumT>::Meta(T1 t1, T2 t2)
{
    Ptr<TypeMetaData> metaData(*new T(t1, t2));
    mTypeEnum->GetMetaData().Add(metaData.GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
template<class T, class T1, class T2, class T3>
void TypeEnumCreator<EnumT>::Meta(T1 t1, T2 t2, T3 t3)
{
    Ptr<TypeMetaData> metaData(*new T(t1, t2, t3));
    mTypeEnum->GetMetaData().Add(metaData.GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
void TypeEnumCreator<EnumT>::Val(const NsChar* name, NsInt value)
{
    mTypeEnum->AddValue(NsSymbol(name), value);
}

}
}
