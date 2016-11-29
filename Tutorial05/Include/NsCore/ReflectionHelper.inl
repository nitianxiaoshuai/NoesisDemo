////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1316]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/TypeProperty.h>


namespace Noesis
{
namespace Core
{
namespace Reflection
{

////////////////////////////////////////////////////////////////////////////////////////////////////
TypeClassMetaData::TypeClassMetaData(const TypeClass* tc, const TypeMetaData* m):
    typeClass(tc), metaData(m)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TypeClassProperty::TypeClassProperty(const TypeClass* tc, const TypeProperty* p):
    typeClass(tc), property(p)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
typename Param<T>::Type Property::Get() const
{
    if (mTypeProperty)
    {
        return mTypeProperty->Get<T>(mInstance);
    }
    else
    {
        NS_ASSERT(mType);
        NS_ASSERT(mInstance);
        NS_ASSERT(mType == TypeOf<T>());
        return *reinterpret_cast<const T*>(mInstance);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void Property::Set(typename Param<T>::Type value) const
{
    if (mTypeProperty)
    {
        mTypeProperty->Set<T>(const_cast<void*>(mInstance), value);
    }
    else
    {
        NS_ASSERT(mType);
        NS_ASSERT(mInstance);
        NS_ASSERT(mType == TypeOf<T>());
        *const_cast<T*>(reinterpret_cast<const T*>(mInstance)) = value;
    }
}

}
}
}
