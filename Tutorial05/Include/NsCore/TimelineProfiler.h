////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TIMELINEPROFILER_H__
#define __CORE_TIMELINEPROFILER_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/Symbol.h>
#include <NsCore/NSTLMemoryAllocator.h>
#include <NsCore/Vector.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
template<class T> class Delegate;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Timeline profiler tracks jobs processed on each thread. For each thread a sorted list of
/// events are given
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TimelineProfilerNode
{
public:
    /// Use this function to create additional timelines that are not associated to OS threads.
    /// The created timeline will be automatically destroyed at the end of the running application
    static void* CreateTimeline(const NsChar* name);

    /// Returns the next node global identifier
    static NsUInt32 GetNextGID();

    static void Open(NsSymbol sym, NsUInt32 gid = 0);
    static void Open(void* timeline, NsUInt64 timeUs, NsSymbol sym, NsUInt32 gid = 0);
    static void Close(NsSymbol sym, NsUInt32 gid = 0);
    static void Close(void* timeline, NsUInt64 timeUs, NsSymbol sym, NsUInt32 gid = 0);
    static void EnqueueMark(NsUInt32 gid);
    static void BeginIdle();
    static void EndIdle();

    static void SetThreadName(NsSymbol sym);

    enum Flags
    {
        Flags_Open,
        Flags_Close,
        Flags_Enqueue,
        Flags_BeginIdle,
        Flags_EndIdle
    };
    
    struct CpuNode
    {
        NsUInt32 firstChildrenIndex;
        NsUInt32 numChildren;
        
        NsSymbol id;
        NsUInt32 hits;
        NsUInt32 memory;
        NsUInt64 cycles;
    };
    
    struct Event
    {
        // Global Unique Identifier
        NsUInt32 gid;
        
        NsSymbol id;
        Flags flags;
        
        // Information about where the cpu cycles where spent on this timeline event. This is
        // a snapshot of the current cpu node tree
        typedef nstl::MemoryAllocator Allocator;
        typedef NsVector<CpuNode, Allocator> CpuNodes;
        CpuNodes* cpuNodes;
        
        // Time in microseconds, being 0 the start of the application 
        NsUInt64 time;
        
        // Time stamp measured in cycles. Only valid when cpuNodes != 0
        NsUInt64 cyclesTimeStamp;
    };
    
    // Mask must be 2^n - 1
    const static NsSize Mask = 255;
    typedef Event Events[Mask + 1];
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// NodeOpenClose. RAII class for automatic opening/closing timeline sections
////////////////////////////////////////////////////////////////////////////////////////////////////
class NodeOpenClose
{
public:
    inline NodeOpenClose(NsSymbol sym);
    inline ~NodeOpenClose();

private:
    NodeOpenClose(const NodeOpenClose&);
    NodeOpenClose& operator=(const NodeOpenClose&);

    Symbol mSym;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Macros
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_INTERNAL_PROFILE_TIMELINE(sym) \
    static NsUInt32 profilerTimelineSym; \
    if (profilerTimelineSym == 0) \
    { \
        profilerTimelineSym = NsSymbol(sym); \
    } \
    Noesis::Core::NodeOpenClose timelineSection(static_cast<NsSymbol>(profilerTimelineSym))
    
#define NS_INTERNAL_PROFILE_SYM_TIMELINE(sym)\
    Noesis::Core::NodeOpenClose timelineSection(sym)

#if NS_INSTRUMENTED_ENABLED && !defined(NS_DEBUG_CFG)
    #define NS_PROFILE_TIMELINE(sym) NS_INTERNAL_PROFILE_TIMELINE(sym)
    #define NS_PROFILE_SYM_TIMELINE(sym) NS_INTERNAL_PROFILE_SYM_TIMELINE(sym)
#else
    #define NS_PROFILE_TIMELINE(...) NS_NOOP
    #define NS_PROFILE_SYM_TIMELINE(...) NS_NOOP
#endif

}
}

#include <NsCore/TimelineProfiler.inl>

#endif
