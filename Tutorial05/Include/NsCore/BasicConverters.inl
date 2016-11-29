////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #710]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Boxing.h>
#include <NsCore/ValueHelper.h>


namespace Noesis
{
namespace Core
{

namespace BasicConverters
{
NS_CORE_TYPECONVERTER_API NsBool IsNumeric(const Type* type);
NS_CORE_TYPECONVERTER_API NsBool TryNumericConvert(const Type* source, const Type* target,
    BoxedValue* bv, Ptr<BaseComponent>& result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NumericConverter<T>::CanConvertFrom(const Type* type) const
{
    return type == TypeOf<NsString>() || BasicConverters::IsNumeric(type);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NumericConverter<T>::CanConvertTo(const Type* type) const
{
    return type == TypeOf<NsString>() || BasicConverters::IsNumeric(type);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NumericConverter<T>::TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const
{
    BoxedValue* boxed = NsDynamicCast<BoxedValue*>(object);
    if (boxed != 0)
    {
        if (ParentClass::TryConvertFrom_(boxed, result))
        {
            return true;
        }
        else
        {
            const Type* source = boxed->GetValueType();
            return BasicConverters::TryNumericConvert(source, TypeOf<T>(), boxed, result);
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NumericConverter<T>::TryConvertFromString(const NsChar* str, Ptr<BaseComponent>& result) const
{
    T val;
    if (TryGetFromString(str, val))
    {
        result = Boxing::Box<T>(val);
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NumericConverter<T>::TryConvertTo(BaseComponent* object, const Type* type,
    Ptr<BaseComponent>& result) const
{
    if (ParentClass::TryConvertTo(object, type, result))
    {
        return true;
    }
    else
    {
        BoxedValue* boxed = NsDynamicCast<BoxedValue*>(object);
        if (boxed != 0)
        {
            const Type* source = boxed->GetValueType();
            return BasicConverters::TryNumericConvert(source, type, boxed, result);
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NumericConverter<T>::TryConvertToString(BaseComponent* object, NsString& result) const
{
    BoxedValue* boxed = NsDynamicCast<BoxedValue*>(object);
    if (boxed != 0)
    {
        const Type* source = boxed->GetValueType();
        if (source == TypeOf<T>())
        {
            result = ToString(Boxing::Unbox<T>(boxed));
            return true;
        }
    }

    return false;
}

namespace BasicConverters
{
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringI8(const NsChar* str, NsInt8& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringI16(const NsChar* str, NsInt16& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringI32(const NsChar* str, NsInt32& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringI64(const NsChar* str, NsInt64& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringUI8(const NsChar* str, NsUInt8& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringUI16(const NsChar* str, NsUInt16& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringUI32(const NsChar* str, NsUInt32& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringUI64(const NsChar* str, NsUInt64& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringF32(const NsChar* str, NsFloat32& result);
NS_CORE_TYPECONVERTER_API NsBool TryGetFromStringF64(const NsChar* str, NsFloat64& result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class ParserExpression
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsInt8>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsInt8& result)
    {
        return BasicConverters::TryGetFromStringI8(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsInt16>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsInt16& result)
    {
        return BasicConverters::TryGetFromStringI16(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsInt32>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsInt32& result)
    {
        return BasicConverters::TryGetFromStringI32(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsInt64>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsInt64& result)
    {
        return BasicConverters::TryGetFromStringI64(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsUInt8>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsUInt8& result)
    {
        return BasicConverters::TryGetFromStringUI8(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsUInt16>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsUInt16& result)
    {
        return BasicConverters::TryGetFromStringUI16(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsUInt32>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsUInt32& result)
    {
        return BasicConverters::TryGetFromStringUI32(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsUInt64>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsUInt64& result)
    {
        return BasicConverters::TryGetFromStringUI64(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsFloat32>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsFloat32& result)
    {
        return BasicConverters::TryGetFromStringF32(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class ParserExpression<NsFloat64>
{
public:
    static NsBool TryGetFromString(const NsChar* str, NsFloat64& result)
    {
        return BasicConverters::TryGetFromStringF64(str, result);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool NumericConverter<T>::TryGetFromString(const NsChar* str, T& result) const
{
    return ParserExpression<T>::TryGetFromString(str, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsString NumericConverter<T>::ToString(T value) const
{
    return Core::ToString(value);
}


}
}