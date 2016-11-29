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
SpinMutex::SpinMutex()
{
#if defined(NS_PLATFORM_WINDOWS)
    InitializeSRWLock(&mMutex);
#elif defined(NS_PLATFORM_APPLE)
    mMutex = OS_SPINLOCK_INIT;
#else
    int status = pthread_spin_init(&mMutex, PTHREAD_PROCESS_PRIVATE);
    NS_ASSERT(status == 0);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SpinMutex::~SpinMutex()
{
#if defined(NS_PLATFORM_WINDOWS)
#elif defined(NS_PLATFORM_APPLE)
#else
    int status = pthread_spin_destroy(&mMutex);
    NS_ASSERT(status == 0);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SpinMutex::Acquire()
{
#if defined(NS_PLATFORM_WINDOWS)
    AcquireSRWLockExclusive(&mMutex);
#elif defined(NS_PLATFORM_APPLE)
    OSSpinLockLock(&mMutex);
#else
    int status = pthread_spin_lock(&mMutex);
    NS_ASSERT(status = 0);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SpinMutex::Release()
{
#if defined(NS_PLATFORM_WINDOWS)
    ReleaseSRWLockExclusive(&mMutex);
#elif defined(NS_PLATFORM_APPLE)
    OSSpinLockUnlock(&mMutex);
#else
    int status = pthread_spin_unlock(&mMutex);
    NS_ASSERT(status = 0);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SpinMutex::ScopedLock::ScopedLock(SpinMutex& mutex): mMutex(mutex)
{
    mMutex.Acquire();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SpinMutex::ScopedLock::~ScopedLock()
{
    mMutex.Release();
}

}
}
