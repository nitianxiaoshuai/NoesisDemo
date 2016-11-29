////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #750]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_MEMORYMANAGER_H__
#define __CORE_MEMORYMANAGER_H__


#include <NsCore/Types.h>
#include <NsCore/PlatformSettings.h>
#include <NsCore/MemoryAllocator.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Management and tracking of memory allocations and deallocations.
////////////////////////////////////////////////////////////////////////////////////////////////////
class MemoryManager: public MemoryAllocator
{
public:
    /// Memory manager statistics
    struct Stats
    {
        // Note: all numbers are signed because stats may be negative for thread stats (for example 
        //  doing more deallocations that allocations in a thread)

        // Number of currently total allocated blocks
        NsInt32 allocs;
        // Number of accumulated total blocks since the beginning
        NsInt32 allocsAccum;
        
        // Current memory used (measured in bytes)
        NsInt32 memory;
        // Maximum memory used (measured in bytes) since the beginning
        NsInt32 memoryPeak;
        // Total memory requested since the beginning (measured in bytes)
        NsInt32 memoryAccum;
    };

    /// Gets current global (for all threads) memory manager statistics
    virtual Stats GetStats() const = 0;
    
    /// Gets current memory manager statistics for the calling thread
    virtual const Stats* GetThreadStats() const = 0;
};

}
}


#endif
