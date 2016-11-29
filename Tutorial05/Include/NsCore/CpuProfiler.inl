////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/HighResTimer.h>


#ifdef NS_COMPILER_MSVC
    #include <math.h>
    #include <intrin.h>
#endif


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
void CpuProfilerNode::Enter()
{
#ifdef NS_COMPILER_MSVC
    // rdtsc because the QueryPerformanceCounter() is too inefficient for a profiler
    lastEnterTime = __rdtsc();
    hits++;
#else
    lastEnterTime = 0;
    hits++;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CpuProfilerNode::Leave()
{
#ifdef NS_COMPILER_MSVC
    cycles = cycles + __rdtsc() - lastEnterTime;
#endif
}

}
}
