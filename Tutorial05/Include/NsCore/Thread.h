////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_THREAD_H__
#define __CORE_THREAD_H__


#include <Noesis.h>


#if defined (NS_PLATFORM_WINDOWS)
    #include <windows.h>
    typedef HANDLE ThreadT;
#else
    #include <pthread.h>
    typedef pthread_t ThreadT;
#endif


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Threads allow multiple pieces of code to run asynchronously and simultaneously
////////////////////////////////////////////////////////////////////////////////////////////////////
class Thread
{
public:
    template<typename T> Thread(T f);
    template<typename T, typename P0> Thread(T f, P0 p0);
    template<typename T, typename P0, typename P1> Thread(T f, P0 p0, P1 p1);

    inline ~Thread();

    /// Waits for the thread to finish its execution 
    inline void Join();

    /// Retrieves the thread identifier of the calling thread
    static inline NsUInt32 GetCurrentThreadId();

private:
    ThreadT mHandle;
};

}
}

#include <NsCore/Thread.inl>

#endif
