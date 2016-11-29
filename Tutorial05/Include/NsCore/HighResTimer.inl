////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif


namespace Noesis
{
namespace Core
{
////////////////////////////////////////////////////////////////////////////////////////////////////
NsFloat64 HighResTimer::StartTime()
{
    return sStartTime;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsFloat64 HighResTimer::Frequency()
{
#ifdef _WIN32
    return 1.0 / sSecondsPerCycle;
#else
    return 1000000.0;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsFloat64 HighResTimer::Seconds()
{
    // [jsantos] I took the idea of adding a big number from UnrealEngine. This way imprecisions
    // when casting the time to float should be caught earlier
    
#ifdef _WIN32
    LARGE_INTEGER cycles;
    QueryPerformanceCounter(&cycles);
    return cycles.QuadPart * sSecondsPerCycle + 16777216.0;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    return static_cast<NsFloat64>(tv.tv_sec) + static_cast<NsFloat64>(tv.tv_usec) / 1000000.0 
        + 16777216.0;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt64 HighResTimer::Cycles()
{
#ifdef _WIN32
    LARGE_INTEGER cycles;
    QueryPerformanceCounter(&cycles);
    return cycles.QuadPart;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    
    return static_cast<NsUInt64>(tv.tv_sec) * 1000000L + static_cast<NsUInt64>(tv.tv_usec);
#endif
}

}
}
