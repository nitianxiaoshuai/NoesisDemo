////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_FIXEDVECTOR_H__
#define __CORE_FIXEDVECTOR_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <EASTL/fixed_vector.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
// A vector which uses a fixed size memory pool. The bEnableOverflow template parameter allows the
// container to resort to heap allocations if the memory pool is exhausted
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, size_t nodeCount, bool bEnableOverflow, typename Allocator>
class NsFixedVector: public eastl::fixed_vector<T, nodeCount, bEnableOverflow, Allocator>
{
};


#endif
