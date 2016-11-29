////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>

#if defined (NS_PLATFORM_WINDOWS)
    #include <process.h>
#elif defined(NS_PLATFORM_ANDROID)
    #include <unistd.h>
#elif defined(NS_PLATFORM_LINUX)
    #include <unistd.h>
    #include <sys/syscall.h>
#endif


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class ThreadDelegate
{
public:
    virtual void Invoke() = 0;
    virtual ~ThreadDelegate() {};
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class ThreadDelegate0: public ThreadDelegate
{
public:
    ThreadDelegate0(T f): _f(f) {}
    void Invoke() { _f(); }
    T _f;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class P0>
class ThreadDelegate1: public ThreadDelegate
{
public:
    ThreadDelegate1(T f, P0 p0): _f(f), _p0(p0) {}
    void Invoke() { _f(_p0); }
    T _f;
    P0 _p0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class P0, class P1>
class ThreadDelegate2: public ThreadDelegate
{
public:
    ThreadDelegate2(T f, P0 p0, P1 p1): _f(f), _p0(p0), _p1(p1) {}
    void Invoke() { _f(_p0, _p1); }
    T _f;
    P0 _p0;
    P1 _p1;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NS_PLATFORM_WINDOWS
inline unsigned int __stdcall Start(void *arg)
#else
inline void* Start(void* arg)
#endif
{
    ThreadDelegate* d = (ThreadDelegate*)arg;
    d->Invoke();
    delete d;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline ThreadT LaunchThread(ThreadDelegate* d)
{
    ThreadT h;

#ifdef NS_PLATFORM_WINDOWS
    h = (HANDLE)_beginthreadex(0, 0, &Start, d, 0, 0);
    NS_ASSERT(h != 0);
#else
    int status = pthread_create(&h, 0, &Start, d);
    NS_ASSERT(status == 0);
#endif

    return h;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T> Thread::Thread(T f)
{
    mHandle = LaunchThread(new ThreadDelegate0<T>(f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename P0> Thread::Thread(T f, P0 p0)
{
    mHandle = LaunchThread(new ThreadDelegate1<T, P0>(f, p0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename P0, typename P1> Thread::Thread(T f, P0 p0, P1 p1)
{
    mHandle = LaunchThread(new ThreadDelegate2<T, P0, P1>(f, p0, p1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Thread::~Thread()
{
    if (mHandle != 0)
    {
#ifdef NS_PLATFORM_WINDOWS
        BOOL err = CloseHandle(mHandle);
        NS_ASSERT(err != 0);
#else
        int status = pthread_detach(mHandle);
        NS_ASSERT(status == 0);
#endif
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Thread::Join()
{
    if (mHandle != 0)
    {
#ifdef NS_PLATFORM_WINDOWS
        WaitForSingleObject(mHandle, INFINITE);
        BOOL err = CloseHandle(mHandle);
        NS_ASSERT(err != 0);
#else
        int status = pthread_join(mHandle, 0);
        NS_ASSERT(status == 0);
#endif
    }

    mHandle = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Thread::GetCurrentThreadId()
{
#if defined(NS_PLATFORM_WINDOWS)
    return ::GetCurrentThreadId();
#elif defined(NS_PLATFORM_ANDROID)
    return gettid();
#elif defined(NS_PLATFORM_APPLE)
    return pthread_mach_thread_np(pthread_self());
#elif defined(NS_PLATFORM_LINUX)
    return (pid_t)syscall(SYS_gettid);
#endif
}


}
}
