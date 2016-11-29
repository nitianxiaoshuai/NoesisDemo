////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #629]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> 
Ptr<T>::Ptr(): mPtr(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> 
Ptr<T>::Ptr(T* ptr): mPtr(ptr)
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(ptr) != 0xDEADBEEF);
#endif

    if (mPtr != 0)
    {
        mPtr->AddReference();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<T>::Ptr(T& ptr): mPtr(const_cast<T*>(&ptr))
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(&ptr) != 0xDEADBEEF);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<T>::Ptr(const Ptr& ptr): mPtr(ptr.mPtr)
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(ptr.mPtr) != 0xDEADBEEF);
#endif

    if (mPtr != 0)
    {
        mPtr->AddReference();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
template<class S> Ptr<T>::Ptr(const Ptr<S>& ptr): mPtr(ptr.GetPtr())
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(ptr.GetPtr()) != 0xDEADBEEF);
#endif

    if (mPtr != 0)
    {
        mPtr->AddReference();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<T>::~Ptr()
{
    if (mPtr != 0)
    {
        mPtr->Release();
    }

#if NS_PARANOID_LEVEL >= 1
    mPtr = reinterpret_cast<T*>(static_cast<NsUIntPtr>(0xDEADBEEF));
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<T>& Ptr<T>::operator=(const Ptr& ptr)
{
    Reset(ptr.mPtr);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
template<class S> Ptr<T>& Ptr<T>::operator=(const Ptr<S>& ptr)
{
    Reset(ptr.GetPtr());
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<T>& Ptr<T>::operator=(T& ptr)
{
    Reset();
    mPtr = const_cast<T*>(&ptr);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void Ptr<T>::Reset()
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
#endif

    if (mPtr != 0)
    {
        mPtr->Release();
    }

    mPtr = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void Ptr<T>::Reset(T* ptr)
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(ptr) != 0xDEADBEEF);
#endif

    if (mPtr != ptr)
    {
        if (ptr != 0)
        {
            ptr->AddReference();
        }
        
        if (mPtr != 0)
        {
            mPtr->Release();
        }

        mPtr = ptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void Ptr<T>::Destroy()
{
    mPtr = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
T* const Ptr<T>::operator->() const
{
    NS_ASSERT(mPtr != 0, "Dereferencing a null smart pointer");
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
#endif
    return mPtr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
T* const Ptr<T>::GetPtr() const
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
#endif
    return mPtr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<T>::operator NsBool() const
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
#endif
    return mPtr != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
template<class S> NsBool Ptr<T>::operator==(const Ptr<S>& ptr) const
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(ptr.GetPtr()) != 0xDEADBEEF);
#endif
    return mPtr == ptr.GetPtr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
template<class S> NsBool Ptr<T>::operator!=(const Ptr<S>& ptr) const
{
    return !(*this == ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
template<class S> NsBool Ptr<T>::operator<(const Ptr<S>& ptr) const
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(ptr.GetPtr()) != 0xDEADBEEF);
#endif
    return mPtr < ptr.GetPtr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
template<class S> NsBool Ptr<T>::operator==(S* ptr) const
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(ptr) != 0xDEADBEEF);
#endif
    return mPtr == ptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
template<class S> NsBool Ptr<T>::operator!=(S* ptr) const
{
    return !(*this == ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
template<class S> NsBool Ptr<T>::operator<(S* ptr) const
{
#if NS_PARANOID_LEVEL >= 1
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(mPtr) != 0xDEADBEEF);
    NS_ASSERT(reinterpret_cast<NsUIntPtr>(ptr) != 0xDEADBEEF);
#endif
    return mPtr < ptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const Ptr<T>& Ptr<T>::Null()
{
    // Disabled the warning that indicates that statics are not thread safe because in this case 
    // (and thanks to the trivial Ptr constructor) the static preinitialization to null is valid
#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4640)
#endif
    static Ptr<T> null;
#ifdef _MSC_VER
    #pragma warning(pop)
#endif

    return null;
}

}
}
