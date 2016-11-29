////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #710]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Boxing.h>
#include <NsCore/String.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool Converter<T>::TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const
{
    return TryConvertFromString(str, Int2Type<IsRefCounted<T>::Result>(), result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool Converter<T>::TryConvertToString(BaseComponent* object, NsString& result) const
{
    if (object == 0)
    {
        result = "";
        return true;
    }

    return TryConvertToString(object, Int2Type<IsRefCounted<T>::Result>(), result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool Converter<T>::TryConvertFromString(const NsChar* str, IsStruct,
    Ptr<BaseComponent>& result) const
{
    T obj;
    if (T::TryParse(str, obj))
    {
        result = Boxing::Box<T>(obj);
        return true;
    }
 
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool Converter<T>::TryConvertFromString(const NsChar* str, IsComponent,
    Ptr<BaseComponent>& result) const
{
    return T::TryParse(str, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool Converter<T>::TryConvertToString(BaseComponent* object, IsStruct,
    NsString& result) const
{
    const T& obj = Boxing::Unbox<T>(NsStaticCast<BoxedValue*>(object));
    result = obj.ToString();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool Converter<T>::TryConvertToString(BaseComponent* object, IsComponent,
    NsString& result) const
{
    result = object->ToString();
    return true;
}
}
}