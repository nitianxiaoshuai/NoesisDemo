////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool TLSValue::IsInitialized() const
{
    return mKey != InvalidKey;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TLSValue::Set(void* ptr) const
{
    NS_ASSERT(IsInitialized());

#if defined(NS_PLATFORM_WINDOWS_DESKTOP) || defined(NS_PLATFORM_XBOX_ONE)
    if (TlsSetValue(mKey, ptr) == 0)
    {
        HandleWinError("TlsSetValue");
    }
#elif defined(NS_PLATFORM_WINRT) 
    if (FlsSetValue(mKey, ptr) == 0)
    {
        HandleWinError("FlsSetValue");
    }
#else
    int status = pthread_setspecific(mKey, ptr);
    if (status != 0)
    {
        HandleSystemError("pthread_setspecific", status);
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* TLSValue::Get() const
{
    NS_ASSERT(IsInitialized());

#if defined(NS_PLATFORM_WINDOWS_DESKTOP) || defined(NS_PLATFORM_XBOX_ONE)
    return TlsGetValue(mKey);
#elif defined(NS_PLATFORM_WINRT)
    return FlsGetValue(mKey);
#else
    return pthread_getspecific(mKey);
#endif
}

}
}
