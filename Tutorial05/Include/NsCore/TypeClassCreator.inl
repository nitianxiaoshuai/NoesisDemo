////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Symbol.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/Error.h>
#include <NsCore/Ptr.h>
#include <NsCore/TypeOfForward.h>
#include <NsCore/TypePropertyImpl.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
TypeClassCreator::TypeClassCreator(TypeClassBuilder* typeClass): mTypeClass(typeClass)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT>
Type* TypeClassCreator::Create(const TypeInfo& typeInfo)
{
    return CreateTypeClass(typeInfo, IsInterface<ClassT>::Result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class BaseT> 
void TypeClassCreator::Fill(Type* type)
{
    TypeClassCreator helper((TypeClassBuilder*)(type));
    helper.Base<ClassT, BaseT>(Int2Type<IsSame<BaseT, NoParent>::Result>());

    ClassT::template StaticFillClassType<void>(helper);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<T> TypeClassCreator::Meta()
{
    Ptr<T> metaData = *new T();
    AddMetaData(mTypeClass, metaData.GetPtr());
    return metaData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class T1>
Ptr<T> TypeClassCreator::Meta(T1 t1)
{
    Ptr<T> metaData = *new T(t1);
    AddMetaData(mTypeClass, metaData.GetPtr());
    return metaData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class T1, class T2>
Ptr<T> TypeClassCreator::Meta(T1 t1, T2 t2)
{
    Ptr<T> metaData = *new T(t1, t2);
    AddMetaData(mTypeClass, metaData.GetPtr());
    return metaData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class T1, class T2, class T3>
Ptr<T> TypeClassCreator::Meta(T1 t1, T2 t2, T3 t3)
{
    Ptr<T> metaData = *new T(t1, t2, t3);
    AddMetaData(mTypeClass, metaData.GetPtr());
    return metaData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class T1, class T2, class T3, class T4>
Ptr<T> TypeClassCreator::Meta(T1 t1, T2 t2, T3 t3, T4 t4)
{
    Ptr<T> metaData = *new T(t1, t2, t3, t4);
    AddMetaData(mTypeClass, metaData.GetPtr());
    return metaData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
void TypeClassCreator::Impl()
{
    enum { isDerived = IsDerived<ClassT, T>::Result };
    NS_STATIC_ASSERT(isDerived, __CLASS_DOES_NOT_IMPLEMENT_SPECIFIED_INTERFACE);
    NS_STATIC_ASSERT(IsInterface<T>::Result, __NSIMPL_USED_WITH_NON_INTERFACE_CLASS);

    NsSize offset = CalculateParentOffset<ClassT, T>();
    AddInterface(mTypeClass, T::StaticGetClassType((T2T<T>*)0), offset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T> NsSize OffsetOf(T ClassT::* prop)
{
    return (NsSize)( (ptrdiff_t)&reinterpret_cast<const volatile char&>((((ClassT *)0)->*prop)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T ClassT::* prop)
{
    NsSize offset = OffsetOf(prop);
    TypeProperty* typeProperty = new TypePropertyOffset<T>(NsSymbol(name), offset);
    AddProperty(mTypeClass, typeProperty);
    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T, NsInt N>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T (ClassT::* prop)[N])
{
    NsSize offset = OffsetOf(prop);
    TypeProperty* typeProperty = new TypePropertyArray<T, N>(NsSymbol(name), offset);
    AddProperty(mTypeClass, typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T, NsInt N>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T (ClassT::* prop)[N], NsSize index)
{
    NS_ASSERT(index < N);
    
    NsSize offset = OffsetOf(prop) + (index * sizeof(T));
    TypeProperty* typeProperty = new TypePropertyOffset<T>(NsSymbol(name), offset);
    AddProperty(mTypeClass, typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    NsSize offset)
{
    TypeProperty* typeProperty = new TypePropertyOffset<T>(NsSymbol(name), offset);
    AddProperty(mTypeClass, typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T (ClassT::*getter)() const)
{
    typedef typename IsConst<typename IsReference<T>::NonReferenceType>::NonConstType Type;
    TypeProperty* typeProperty = new TypePropertyFunction<ClassT, Type>(NsSymbol(name), getter, 0);
    AddProperty(mTypeClass, typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T (ClassT::*getter)() const, void (ClassT::*setter)(T))
{
    typedef typename IsConst<typename IsReference<T>::NonReferenceType>::NonConstType Type;
    TypeProperty* typeProperty = new TypePropertyFunction<ClassT, Type>(NsSymbol(name), getter,
        setter);
    AddProperty(mTypeClass, typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
void TypeClassCreator::Base(Int2Type<0>)
{
    enum { isDerived = IsDerived<ClassT, T>::Result };
    NS_STATIC_ASSERT(isDerived, __CLASS_DOES_NOT_DERIVE_FROM_SPECIFIED_BASE);

#if NS_ASSERTS_ENABLED
    NsSize parentOffset = CalculateParentOffset<ClassT, T>();
    NS_ASSERT(parentOffset == 0);
#endif

    AddBase(mTypeClass, TypeOf<T>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
void TypeClassCreator::Base(Int2Type<1>)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TypeClassCreator::TypePropertyCreator::TypePropertyCreator(TypeProperty* typeProperty):
    mTypeProperty(typeProperty)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
typename TypeClassCreator::TypePropertyCreator&
TypeClassCreator::TypePropertyCreator::Meta()
{
    Ptr<T> meta = *new T();
    mTypeProperty->GetMetaData().Add(meta.GetPtr());
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class T1>
typename TypeClassCreator::TypePropertyCreator&
TypeClassCreator::TypePropertyCreator::Meta(T1 t1)
{
    Ptr<T> meta = *new T(t1);
    mTypeProperty->GetMetaData().Add(meta.GetPtr());
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class T1, class T2>
typename TypeClassCreator::TypePropertyCreator&
TypeClassCreator::TypePropertyCreator::Meta(T1 t1, T2 t2)
{
    Ptr<T> meta = *new T(t1, t2);
    mTypeProperty->GetMetaData().Add(meta.GetPtr());
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class T1, class T2, class T3>
typename TypeClassCreator::TypePropertyCreator&
TypeClassCreator::TypePropertyCreator::Meta(T1 t1, T2 t2, T3 t3)
{
    Ptr<T> meta = *new T(t1, t2, t3);
    mTypeProperty->GetMetaData().Add(meta.GetPtr());
    return *this;
}

}
}
