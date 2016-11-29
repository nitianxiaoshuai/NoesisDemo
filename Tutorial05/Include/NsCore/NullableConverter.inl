////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1362]
////////////////////////////////////////////////////////////////////////////////////////////////////


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class P>
NsBool CommonCanConvertFrom(const Type* type, const P* pThis)
{
    NS_ASSERT(type);
    return pThis->P::CanConvertFrom(type) || type == TypeOf<T>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class P>
NsBool CommonCanConvertTo(const Type* type, const P* pThis)
{
    NS_ASSERT(type);
    return pThis->P::CanConvertTo(type) || type == TypeOf<T>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class P>
NsBool TryCommonConvertFrom(BaseComponent* object, const P* pThis, Ptr<BaseComponent>& result)
{
    if (!object)
    {
        result = Boxing::Box<Nullable<T> >(Nullable<T>());
        return true;
    }
    
    BoxedValue* bv = NsStaticCast<BoxedValue*>(object);
    if (!bv)
    {
        return false;
    }
    
    if (bv->GetValueType() == TypeOf<T>())
    {
        result = Boxing::Box<Nullable<T> >(Nullable<T>(Boxing::Unbox<T>(NsStaticCast<BoxedValue*>(
            object))));
        return true;
    }
    else
    {
        // ParentClass::Convert from only converts from String and calls ConvertFromString, which
        // returns a boxed nullable
        Ptr<BaseComponent> ret;
        if (!pThis->P::TryConvertFrom(object, ret) ||
            ret->GetClassType() != TypeOf<Boxed<Nullable<T> > >())
        {
            return false;
        }
        result = ret;
        return true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class P>
NsBool TryCommonConvertFromString(const NsChar* str, const P* pThis, Ptr<BaseComponent>& result)
{
    T val;
    if (!pThis->TryGetFromString(str, val))
    {
        return false;
    }

    result = Boxing::Box<Nullable<T> >(val);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class P>
NsBool TryCommonConvertTo(BaseComponent* object, const Type* type, const P* pThis,
    Ptr<BaseComponent>& result)
{
    if (!object)
    {
        return false;
    }

    if (!type)
    {
        return false;
    }
    
    if (type == TypeOf<T>())
    {
        BoxedValue* boxed = NsDynamicCast<BoxedValue*>(object);

        if (!boxed || boxed->GetValueType() != TypeOf<Nullable<T> >())
        {
            return false;
        }

        const Nullable<T>& nullable = Boxing::Unbox<Nullable<T> >(boxed);
        if (!nullable.HasValue())
        {
            return false;
        }
        
        result = Boxing::Box<T>(nullable.GetValue());
        return true;
    }
    else if (type == TypeOf<NsString>())
    {
        result = Boxing::Box<NsString>(pThis->ConvertToString(object));
        return true;
    }
    else
    {
        BoxedValue* boxed = NsDynamicCast<BoxedValue*>(object);

        if (!boxed || boxed->GetValueType() != TypeOf<Nullable<T> >())
        {
            return false;
        } 

        Ptr<BaseComponent> value;
        const Nullable<T>& nullable = Boxing::Unbox<Nullable<T> >(boxed);
        if (nullable.HasValue())
        {
            value = Boxing::Box<T>(nullable.GetValue());
        }

        if (type == TypeOf<BaseComponent>())
        {
            result = value;
            return true;
        }
        else
        {
            return pThis->P::TryConvertTo(value.GetPtr(), type, result);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class P>
NsBool TryCommonConvertToString(BaseComponent* object, const P* pThis, NsString& result)
{
    if (!object)
    {
        return false;
    }

    BoxedValue* boxed = NsDynamicCast<BoxedValue*>(object);

    if (!boxed || boxed->GetValueType() != TypeOf<Nullable<T> >())
    {
        return false;
    }

    const Nullable<T>& value = Boxing::Unbox<Nullable<T> >(boxed);

    if (value.HasValue())
    {
        Ptr<BoxedValue> vv = Boxing::Box<T>(value.GetValue());
        return pThis->P::TryConvertToString(vv.GetPtr(), result);
    }

    result = "";
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableNumericConverter<T>::CanConvertFrom(const Type* type) const
{
    return CommonCanConvertFrom<T, ParentClass>(type, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableNumericConverter<T>::CanConvertTo(const Type* type) const
{
    return CommonCanConvertTo<T, ParentClass>(type, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableNumericConverter<T>::TryConvertFrom(BaseComponent* object,
    Ptr<BaseComponent>& result) const
{
    return TryCommonConvertFrom<T, ParentClass>(object, this, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableNumericConverter<T>::TryConvertFromString(const NsChar* str,
    Ptr<BaseComponent>& result) const
{
    return TryCommonConvertFromString<T, ParentClass>(str, this, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableNumericConverter<T>::TryConvertTo(BaseComponent* object, 
    const Type* type, Ptr<BaseComponent>& result) const
{
    return TryCommonConvertTo<T, ParentClass>(object, type, this, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableNumericConverter<T>::TryConvertToString(BaseComponent* object,
    NsString& result) const
{
    return TryCommonConvertToString<T, ParentClass>(object, this, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableConverter<T>::CanConvertFrom(const Type* type) const
{
    enum { isDerived = IsDerived<T, BaseComponent>::Result };
    NS_STATIC_ASSERT(!isDerived, _NULLABLECONVERTER_NOT_ALLOWED_FOR_COMPONENTS);

    return CommonCanConvertFrom<T, ParentClass>(type, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableConverter<T>::CanConvertTo(const Type* type) const
{
    return CommonCanConvertTo<T, ParentClass>(type, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableConverter<T>::TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const
{
    return TryCommonConvertFrom<T, ParentClass>(object, this, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableConverter<T>::TryConvertFromString(const NsChar* str,
    Ptr<BaseComponent>& result) const
{
    Ptr<BaseComponent> bc;
    if (!ParentClass::TryConvertFromString(str, bc))
    {
        return false;
    }

    result = Boxing::Box<Nullable<T> >(Boxing::Unbox<T>(
        NsStaticCast<BoxedValue*>(bc.GetPtr())));
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableConverter<T>::TryConvertTo(BaseComponent* object, const Type* type,
    Ptr<BaseComponent>& result) const
{
    return TryCommonConvertTo<T, ParentClass>(object, type, this, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NullableConverter<T>::TryConvertToString(BaseComponent* object, NsString& result) const
{
    return TryCommonConvertToString<T, ParentClass>(object, this, result);
}


}
}
