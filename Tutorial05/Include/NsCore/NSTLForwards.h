////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_NSTLFORWARDS_H__
#define __CORE_NSTLFORWARDS_H__


#include <NsCore/DequeHelper.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Forward declarations for all nstl types
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef char NsChar;


namespace eastl
{
class DefaultAllocator;
class SafeAllocator;
template<class T> struct hash;
template<class T> struct equal_to;
template<class T> struct less;
template<class T1, class T2> struct pair;
}

namespace Noesis
{
namespace Core
{
namespace nstl = eastl;
}
}

template<class T, class Allocator = eastl::DefaultAllocator> class NsBasicString;
typedef NsBasicString<NsChar> NsString;
typedef NsBasicString<NsChar, eastl::SafeAllocator>  NsString_;
template <int nodeCount, bool bEnableOverflow = true, typename Allocator = eastl::DefaultAllocator>
    class NsFixedString;

template<size_t N> class NsBitset;

template<class T, class Allocator = eastl::DefaultAllocator,
    size_t kNodeSize = eastl::deque_helper<T>::DefaultSize> class NsDeque;

template<class Key, class T, class Hash = eastl::hash<Key>,
    typename Predicate = eastl::equal_to<Key>, class Allocator = eastl::DefaultAllocator,
    bool bCacheHashCode = false> class NsHashMap;
template<class Key, class T, class Hash = eastl::hash<Key>,
    typename Predicate = eastl::equal_to<Key>, class Allocator = eastl::DefaultAllocator,
    bool bCacheHashCode = false> class NsHashMultimap;
    
template<class Value, class Hash = eastl::hash<Value>,
    typename Predicate = eastl::equal_to<Value>, class Allocator = eastl::DefaultAllocator,
    bool bCacheHashCode = false> class NsHashSet;
template<class Value, class Hash = eastl::hash<Value>,
    typename Predicate = eastl::equal_to<Value>, class Allocator = eastl::DefaultAllocator,
    bool bCacheHashCode = false> class NsHashMultiset;

template<class T, class Allocator = eastl::DefaultAllocator> class NsList;

template<class Key, class T, class Compare = eastl::less<Key>,
    typename Allocator = eastl::DefaultAllocator> class NsMap;
template<class Key, class T, class Compare = eastl::less<Key>,
    typename Allocator = eastl::DefaultAllocator> class NsMultimap;

template<class T, class Container = NsDeque<T> > class NsQueue;

template<class Key, class Compare = eastl::less<Key>,
    typename Allocator = eastl::DefaultAllocator> class NsSet;
template<class Key, class Compare = eastl::less<Key>,
    typename Allocator = eastl::DefaultAllocator> class NsMultiset;

template<class T, class Container = NsDeque<T> > class NsStack;
template<class T, class Allocator = eastl::DefaultAllocator> class NsVector;
template<class T, size_t nodeCount, bool bEnableOverflow = true,
    typename Allocator = eastl::DefaultAllocator> class NsFixedVector;


#endif
