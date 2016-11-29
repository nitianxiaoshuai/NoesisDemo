////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_NSTLPOOLALLOCATOR_H__
#define __CORE_NSTLPOOLALLOCATOR_H__


#include <Noesis.h>
#include <NsCore/FixedAllocator.h>


NS_CFORWARD(Core, MemoryAllocator)


namespace eastl
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// nstl allocator implemented using a fixed allocator.
///  
/// Example:
///
///     typedef NsSet<NsInt32, nstl::less<NsInt32>, nstl::PoolAllocator> MySet;
///     MySet set;
///     set.Init(sizeof(MySet::node_type), 128);
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class PoolAllocator
{
public:
    explicit inline PoolAllocator(const char* name = "");
    inline PoolAllocator(const PoolAllocator& allocator);

    inline PoolAllocator& operator=(const PoolAllocator& allocator);

    inline void Init(Noesis::Core::MemoryAllocator* allocator, NsSize nodeSize, NsSize nodeCount);
    inline void Init(NsSize nodeSize, NsSize nodeCount);

    inline void* allocate(size_t n, int flags = 0);
    inline void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0);
    inline void deallocate(void* p, size_t n);

    inline Noesis::Core::MemoryAllocator* GetMemoryAllocator() const;

private:
    Noesis::Core::FixedAllocator mFixedAllocator;
};

inline NsBool operator==(const PoolAllocator& a, const PoolAllocator& b);
inline NsBool operator!=(const PoolAllocator& a, const PoolAllocator& b);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "NSTLPoolAllocator.inl"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace alias 
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Noesis
{
namespace Core
{
namespace nstl = eastl;
}
}

#endif
