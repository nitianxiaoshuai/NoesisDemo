////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_CPUPROFILER_H__
#define __CORE_CPUPROFILER_H__


#include <Noesis.h>
#include <NsCore/Profiler.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Profiler that tracks CPU cycles usage. Each node holds the time spent on it and the times it
/// has been called. Memory allocations on each node are also stored
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API CpuProfilerNode: public ProfilerNode<CpuProfilerNode>
{
public:
    CpuProfilerNode(NsSymbol sym = NsSymbol(NsUInt32(0)), MemoryAllocator* allocator = 0);

    /// \return the root node
    static CpuProfilerNode* GetRootNode();
    
    /// \return the current active node
    static CpuProfilerNode* GetCurrentNode();
    
    /// Sets the current active node
    static void SetCurrentNode(CpuProfilerNode* node);

    NS_FORCEINLINE void Enter();
    NS_FORCEINLINE void Leave();
    
    static void AcquireMutexForAddingChild();
    static void ReleaseMutexForAddingChild();
    static void AcquireMutexForGettingChildren();
    static void ReleaseMutexForGettingChildren();
    
public:
    // Written always by the same thread. Read by the rest of threads
    NsUInt32 hits;
    NsUInt32 memory;
    NsUInt64 cycles;

private:
    NsUInt64 lastEnterTime;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

#if NS_INSTRUMENTED_ENABLED && !defined(NS_DEBUG_CFG)
    #define NS_PROFILE_CPU(sym) NS_INTERNAL_PROFILE((sym), Core::CpuProfilerNode, NS_UNIQUE_NAME(cpu))
    #define NS_PROFILE_SYM_CPU(sym) NS_INTERNAL_PROFILE_SYM((sym), Core::CpuProfilerNode)
#else
    #define NS_PROFILE_CPU(...) NS_NOOP
    #define NS_PROFILE_SYM_CPU(...) NS_NOOP
#endif

}
}

#include <NsCore/CpuProfiler.inl>

#endif