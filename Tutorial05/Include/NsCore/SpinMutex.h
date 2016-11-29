////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_SPINMUTEX_H__
#define __CORE_SPINMUTEX_H__


#include <Noesis.h>

#if defined (NS_PLATFORM_WINDOWS)
    #include <windows.h>
#elif defined(NS_PLATFORM_APPLE)
    #include <libkern/OSAtomic.h>
#else
    #include <pthread.h>
#endif


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Non-recursive Spin Lock
////////////////////////////////////////////////////////////////////////////////////////////////////
class SpinMutex
{
public:
    inline SpinMutex();
    inline ~SpinMutex();

    /// Waits for ownership
    inline void Acquire();

    /// Releases ownership
    inline void Release();

    /// Helper class to automatically release the mutex
    class ScopedLock
    {
    public:
        inline ScopedLock(SpinMutex& mutex);
        inline ~ScopedLock();

    private:
        /// non-copyable
        //@{
        ScopedLock(const ScopedLock&);
        ScopedLock& operator=(const ScopedLock&);
        //@}

        SpinMutex& mMutex;
    };

private:
    /// non-copyable
    //@{
    SpinMutex(const SpinMutex&);
    SpinMutex& operator=(const SpinMutex&);
    //@}

#if defined (NS_PLATFORM_WINDOWS)
    SRWLOCK mMutex;
#elif defined(NS_PLATFORM_APPLE)
    OSSpinLock mMutex;
#else
    pthread_spinlock_t mMutex;
#endif
};

}
}

#include <NsCore/SpinMutex.inl>

#endif
