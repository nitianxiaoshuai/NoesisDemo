////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #488]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/TypeOf.h>
#include <NsCore/TypePropertyUtil.h>


namespace Noesis
{
namespace Core
{

#ifdef NS_COMPILER_MSVC
    #pragma warning(push)
    #pragma warning(disable: 4702)  // Unreachable code 
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
TypePropertyOffset<T>::TypePropertyOffset(NsSymbol name, NsSize offset):
    TypeProperty(name, TypeOf<TT>()), mOffset(offset)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void* TypePropertyOffset<T>::GetContent(void* ptr) const
{
    return Reflection::PtrOffset<TT>(ptr, mOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const void* TypePropertyOffset<T>::GetContent(const void* ptr) const
{
    return Reflection::PtrOffset<TT>(ptr, mOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<BaseComponent> TypePropertyOffset<T>::GetComponent(const void* ptr) const
{
    return Reflection::GetComponent<TT>(this, ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void TypePropertyOffset<T>::SetComponent(void* ptr, BaseComponent* value) const
{
    Reflection::SetComponent<TT>(this, ptr, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const void* TypePropertyOffset<T>::InternalGet(const void* ptr) const
{
    return Reflection::PtrOffset<TT>(ptr, mOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void TypePropertyOffset<T>::InternalGet(const void* ptr, void* storage) const
{
    TT* storageT = static_cast<TT*>(storage);
    *storageT = *Reflection::PtrOffset<TT>(ptr, mOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void TypePropertyOffset<T>::InternalSet(void* ptr, const void* value) const
{
    *Reflection::PtrOffset<TT>(ptr, mOffset) = *static_cast<const TT*>(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool TypePropertyOffset<T>::InternalIsReadOnly() const
{
    return IsConst<T>::Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
TypePropertyArray<T,N>::TypePropertyArray(NsSymbol name, NsSize offset):
    TypeProperty(name, TypeOf<T[N]>()), mOffset(offset)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
void* TypePropertyArray<T,N>::GetContent(void* ptr) const
{
    return Reflection::PtrOffset<T>(ptr, mOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
const void* TypePropertyArray<T,N>::GetContent(const void* ptr) const
{
    return Reflection::PtrOffset<T>(ptr, mOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
Ptr<BaseComponent> TypePropertyArray<T,N>::GetComponent(const void*) const
{
    // Array properties can't be boxed
    NS_ASSERT_UNREACHABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
void TypePropertyArray<T,N>::SetComponent(void*, BaseComponent*) const
{
    // Array properties can't be boxed
    NS_ASSERT_UNREACHABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
const void* TypePropertyArray<T,N>::InternalGet(const void* ptr) const
{
    return Reflection::PtrOffset<T>(ptr, mOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
void TypePropertyArray<T,N>::InternalGet(const void*, void*) const
{
    // Can't get array properties by copy
    NS_ASSERT_UNREACHABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
void TypePropertyArray<T,N>::InternalSet(void*, const void*) const
{
    // Can't set an array property
    NS_ASSERT_UNREACHABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
NsBool TypePropertyArray<T,N>::InternalIsReadOnly() const
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
NsBool TypePropertyFunction<C,T>::ByRef::CanGetRef()
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
NsBool TypePropertyFunction<C,T>::ByRef::CanGetCopy()
{
    return false;
}

template<class C, class T>
const void* TypePropertyFunction<C,T>::ByRef::GetRef(GetterFn getter, const void* ptr)
{
    return &(static_cast<const C*>(ptr)->*getter)();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
void TypePropertyFunction<C,T>::ByRef::GetCopy(GetterFn, const void*, void*)
{
    // Should return value by reference
    NS_ASSERT_UNREACHABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
NsBool TypePropertyFunction<C,T>::ByCopy::CanGetRef()
{
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
NsBool TypePropertyFunction<C,T>::ByCopy::CanGetCopy()
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
const void* TypePropertyFunction<C,T>::ByCopy::GetRef(GetterFn, const void*)
{
    // Can't get a reference to an unnamed value
    NS_ASSERT_UNREACHABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
void TypePropertyFunction<C,T>::ByCopy::GetCopy(GetterFn getter, const void* ptr, void* storage)
{
    T* storageT = static_cast<T*>(storage);
    *storageT = (static_cast<const C*>(ptr)->*getter)();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
TypePropertyFunction<C,T>::TypePropertyFunction(NsSymbol name, GetterFn getter, SetterFn setter):
    TypeProperty(name, TypeOf<T>()), mGetter(getter), mSetter(setter)
{
    NS_ASSERT(mGetter);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
void* TypePropertyFunction<C,T>::GetContent(void* ptr) const
{
    return const_cast<void*>(Helper::GetRef(mGetter, ptr));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
const void* TypePropertyFunction<C,T>::GetContent(const void* ptr) const
{
    return Helper::GetRef(mGetter, ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
Ptr<BaseComponent> TypePropertyFunction<C,T>::GetComponent(const void* ptr) const
{
    return Reflection::GetComponent<T>(this, ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
void TypePropertyFunction<C,T>::SetComponent(void* ptr, BaseComponent* value) const
{
    Reflection::SetComponent<T>(this, ptr, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
const void* TypePropertyFunction<C,T>::InternalGet(const void* ptr) const
{
    return Helper::GetRef(mGetter, ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
void TypePropertyFunction<C,T>::InternalGet(const void* ptr, void* storage) const
{
    Helper::GetCopy(mGetter, ptr, storage);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
void TypePropertyFunction<C,T>::InternalSet(void* ptr, const void* value) const
{
    NS_ASSERT(mSetter);
    (static_cast<C*>(ptr)->*mSetter)(*static_cast<const T*>(value));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C, class T>
NsBool TypePropertyFunction<C,T>::InternalIsReadOnly() const
{
    return mSetter == 0;
}

#ifdef NS_COMPILER_MSVC
    #pragma warning(pop)
#endif

}
}
