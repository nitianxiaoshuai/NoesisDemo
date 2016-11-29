////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/CompilerTools.h>
#include <NsCore/TypeOf.h>


namespace Noesis
{
namespace Core
{
namespace Impl
{

NS_CORE_KERNEL_API NsString ToString(NsBool value);
NS_CORE_KERNEL_API NsString ToString(NsChar value);
NS_CORE_KERNEL_API NsString ToString(NsUInt8 value);
NS_CORE_KERNEL_API NsString ToString(NsUInt16 value);
NS_CORE_KERNEL_API NsString ToString(NsUInt32 value);
NS_CORE_KERNEL_API NsString ToString(NsUInt64 value);
NS_CORE_KERNEL_API NsString ToString(NsInt8 value);
NS_CORE_KERNEL_API NsString ToString(NsInt16 value);
NS_CORE_KERNEL_API NsString ToString(NsInt32 value);
NS_CORE_KERNEL_API NsString ToString(NsInt64 value);
NS_CORE_KERNEL_API NsString ToString(NsFloat32 value);
NS_CORE_KERNEL_API NsString ToString(NsFloat64 value);
NS_CORE_KERNEL_API NsString ToString(const NsString& value);
NS_CORE_KERNEL_API NsString ToString(Symbol value);

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsString ToString(const T& value)
{
    return value.ToString();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsString ToString(const T& value, Int2Type<0>)
{ 
    return Impl::ToString(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsString ToString(const T& value, Int2Type<1>)
{ 
    return TypeOf<T>()->GetValue(value).GetStr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsString ToString(const T& value, Int2Type<2>)
{
    return Impl::ToString(*value);
}

NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsBool value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsChar value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsUInt8 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsUInt16 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsUInt32 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsUInt64 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsInt8 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsInt16 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsInt32 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsInt64 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsFloat32 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(NsFloat64 value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(const NsString& value);
NS_CORE_KERNEL_API NsUInt32 GetHashCode(Symbol value);

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsUInt32 GetHashCode(const T& value)
{
    return value.GetHashCode();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsUInt32 GetHashCode(const T& value, Int2Type<0>)
{
    return Impl::GetHashCode(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsUInt32 GetHashCode(const T& value, Int2Type<1>)
{
    return Impl::GetHashCode(NsUInt32(value));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsUInt32 GetHashCode(const T& value, Int2Type<2>)
{
    return Impl::GetHashCode(reinterpret_cast<NsUIntPtr>(value));
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsString ToString(const T& value)
{
    enum { ValueTypeId = IsPointer<T>::Result ? 2 : IsEnum<T>::Result ? 1 : 0 };
    return Impl::ToString(value, Int2Type<ValueTypeId>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsUInt32 GetHashCode(const T& value)
{
    enum { ValueTypeId = IsPointer<T>::Result ? 2 : IsEnum<T>::Result ? 1 : 0 };
    return Impl::GetHashCode(value, Int2Type<ValueTypeId>());
}

}
}
