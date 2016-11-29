////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_MEMPROFILER_H__
#define __CORE_MEMPROFILER_H__


#include <Noesis.h>
#include <NsCore/Profiler.h>
#include <NsCore/KernelApi.h>
#include <NsCore/Atomic.h>


namespace Noesis
{
namespace Core
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Profiler for memory usage
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API MemProfilerNode: public ProfilerNode<MemProfilerNode>
{
public:
    MemProfilerNode(NsSymbol sym = NsSymbol(NsUInt32(0)), MemoryAllocator* allocator = 0);

    /// This class is created before the memory manager. So malloc() and free() are used to create
    /// and destroy the instance
    //@{
    static void *operator new(size_t size);
    static void *operator new(size_t size, void* placementPtr);
    static void operator delete(void* ptr);
    static void operator delete(void* ptr, void* placementPtr);
    //@}

    /// \return the root node
    static MemProfilerNode* GetRootNode();
    
    /// \return the current active node
    static MemProfilerNode* GetCurrentNode();
    
    /// Sets the current active node
    static void SetCurrentNode(MemProfilerNode* node);

    NS_FORCEINLINE void Enter();
    NS_FORCEINLINE void Leave();
    
    static void AcquireMutexForAddingChild();
    static void ReleaseMutexForAddingChild();
    static void AcquireMutexForGettingChildren();
    static void ReleaseMutexForGettingChildren();

public:
    // Atomic because they may be incremented / decremented by different threads (a deallocation
    // may occur on a different thread that the allocation)
    // The information given for each node does not include children
    Atomic<NsUInt32> memory;
    Atomic<NsUInt32> allocs;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


#if NS_INSTRUMENTED_ENABLED && !defined(NS_DEBUG_CFG)
    #define NS_PROFILE_MEM(sym) NS_INTERNAL_PROFILE((sym), Core::MemProfilerNode, NS_UNIQUE_NAME(mem))
    #define NS_PROFILE_SYM_MEM(sym) NS_INTERNAL_PROFILE_SYM((sym), Core::MemProfilerNode)
#else
    #define NS_PROFILE_MEM(...) NS_NOOP
    #define NS_PROFILE_SYM_MEM(...) NS_NOOP
#endif

}
}

#include <NsCore/MemProfiler.inl>

#endif