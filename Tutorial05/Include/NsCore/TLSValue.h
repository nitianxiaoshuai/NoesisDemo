////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TLSVALUE_H__
#define __CORE_TLSVALUE_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>

#if defined(NS_PLATFORM_WINDOWS)
    #include <windows.h>
#else
    #include <pthread.h>
#endif


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Thread-local storage (TLS) encapsulation. With TLS, you can provide unique data for each thread
/// that the process can access. Before using a TLSValue it must be initialized (Alloc()). After
/// that each thread can get access to its own region using the Get() and Set() methods.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TLSValue
{
public:
    /// Constructor
    TLSValue();
    
    /// Initializes the thread local storage. Must be called before using Set and Get functions
    void Alloc();
    
    /// Releases the thread local storage
    void Free();
    
    /// Returns true if the TLS is ready to be used
    inline NsBool IsInitialized() const;
    
    /// Stores a value in the calling thread's thread local storage slot for this value
    inline void Set(void* ptr) const;
    
    /// Retrieves the value in the calling thread's thread local storage slot for this value
    inline void* Get() const;

private:
    TLSValue(const TLSValue& queue);
    TLSValue& operator=(const TLSValue& queue);

private:
#if defined(NS_PLATFORM_WINDOWS)
    DWORD mKey;
    static const DWORD InvalidKey = 0xffffffff;
#else
    pthread_key_t mKey;
    static const pthread_key_t InvalidKey = pthread_key_t(0xffffffff);
#endif
};

}
}

#include <NsCore/TLSValue.inl>

#endif
