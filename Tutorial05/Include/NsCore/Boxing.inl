////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #785]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/String.h>
#include <NsCore/DynamicCast.h>
#include <NsCore/TypeOfForward.h>
#include <NsCore/ValueHelper.h>
#include <NsCore/IdOf.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>


namespace Noesis
{
namespace Core
{

namespace Boxing
{
NS_CORE_KERNEL_API void* BoxingAllocate(size_t size);
NS_CORE_KERNEL_API void BoxingDeallocate(void* ptr, size_t size);
void Init();
void Shutdown();
void InitThread();
void ShutdownThread();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class Boxed: public BoxedValue
{
public:
    Boxed() {}
    Boxed(const T& value): mValue(value) {}

    /// From BaseObject
    //@{
    NsString ToString() const
    {
        return Core::ToString(mValue);
    }

    NsBool Equals(BaseObject* object) const
    {
        if (this == object)
        {
            return true;
        }

        Boxed<T>* value = NsDynamicCast<Boxed<T>*>(object);
        if (value != 0)
        {
            return value->mValue == mValue;
        }

        return false;
    }

    NsUInt32 GetHashCode() const
    {
        return Core::GetHashCode(mValue);
    }
    //@}

    /// From BoxedValue
    //@{
    const Type* GetValueType() const
    {
        return TypeOf<T>();
    }

    const void* GetValuePtr() const
    {
        return &mValue;
    }
    //@}

    static void* operator new(size_t size)
    {
        return Boxing::BoxingAllocate(size);
    }
    
    static void operator delete(void* ptr, size_t size)
    {
        Boxing::BoxingDeallocate(ptr, size);
    }

public:
    T mValue;

private:
    NS_IMPLEMENT_INLINE_REFLECTION(Boxed, BoxedValue)
    {
        NsMeta<TypeId>(IdOf<T>("Boxed"));
    }
};

namespace Boxing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> Ptr< Boxed<T> > Box(typename Param<T>::Type value)
{
    NS_STATIC_ASSERT(IsRefCounted<T>::Result == 0, _BOXED_VALUES_CANNOT_BE_COMPONENTS_);
    NS_STATIC_ASSERT(IsPtr<T>::Result == 0, _BOXED_VALUES_CANNOT_BE_COMPONENTS_);

    return *new Boxed<T>(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr< Boxed<NsString> > Box(const NsChar* text)
{
    Ptr< Boxed<NsString> > boxed = *new Boxed<NsString>;
    boxed->mValue = text;
    return boxed;
}

extern NS_CORE_KERNEL_API Ptr< Boxed<NsBool> > boxedTrue;
extern NS_CORE_KERNEL_API Ptr< Boxed<NsBool> > boxedFalse;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> Ptr< Boxed<NsBool> > inline Box<NsBool>(NsBool value)
{
    return value ? boxedTrue : boxedFalse;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> NsBool CanUnbox(BaseComponent* object)
{
    return object->GetClassType() == TypeOf< Boxed<T> >();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> const T& Unbox(BaseComponent* object)
{
    Boxed<T>* boxed = NsStaticCast<Boxed<T>*>(object);
    return boxed->mValue;
}

}
}
}
