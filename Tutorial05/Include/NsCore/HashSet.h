////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_HASHSET_H__
#define __CORE_HASHSET_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <EASTL/hash_set.h>


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

////////////////////////////////////////////////////////////////////////////////////////////////////
// NsHashSet, same interface as std::unordered_map with the following improvements:
// - set_max_load_factor() to make the hashtable never rehash
// - bCacheHashCode template parameter to allow the storing of the hash code within the map
// - insert() to insert a default-constructed element
// - find_as() to find using a different type than the template Key type
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Value, typename Hash, typename Predicate, typename Allocator,
    bool bCacheHashCode>
class NsHashSet : 
    public Noesis::Core::nstl::hash_set<Value, Hash, Predicate, Allocator, bCacheHashCode>
{
private:
    typedef Noesis::Core::nstl::hash_set<
        Value, Hash, Predicate, Allocator, bCacheHashCode> BaseType;

public:
    typedef typename BaseType::allocator_type allocator_type;
    typedef typename BaseType::size_type size_type;

public:
    explicit NsHashSet(const allocator_type& allocator = allocator_type());

    explicit NsHashSet(
        size_type nBucketCount, 
        const Hash& hashFunction = Hash(), 
        const Predicate& predicate = Predicate(), 
        const allocator_type& allocator = allocator_type());

    template <typename FowardIterator>
    NsHashSet(
        FowardIterator first, 
        FowardIterator last, 
        size_type nBucketCount = 0, 
        const Hash& hashFunction = Hash(), 
        const Predicate& predicate = Predicate(), 
        const allocator_type& allocator = allocator_type());
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// NsHashMultiset, same interface as std::unordered_map with the following improvements:
// - set_max_load_factor() to make the hashtable never rehash
// - bCacheHashCode template parameter to allow the storing of the hash code within the map
// - insert() to insert a default-constructed element
// - find_as() to find using a different type than the template Key type
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Value, typename Hash, typename Predicate, typename Allocator,
    bool bCacheHashCode>
class NsHashMultiset : 
    public Noesis::Core::nstl::hash_multiset<Value, Hash, Predicate, Allocator, bCacheHashCode>
{
private:
    typedef Noesis::Core::nstl::hash_multiset<
        Value, Hash, Predicate, Allocator, bCacheHashCode> BaseType;

public:
    typedef typename BaseType::allocator_type allocator_type;
    typedef typename BaseType::size_type size_type;

public:
    explicit NsHashMultiset(const allocator_type& allocator = allocator_type());

    explicit NsHashMultiset(
        size_type nBucketCount, 
        const Hash& hashFunction = Hash(), 
        const Predicate& predicate = Predicate(), 
        const allocator_type& allocator = allocator_type());

    template <typename FowardIterator>
    NsHashMultiset(
        FowardIterator first, 
        FowardIterator last, 
        size_type nBucketCount = 0, 
        const Hash& hashFunction = Hash(), 
        const Predicate& predicate = Predicate(), 
        const allocator_type& allocator = allocator_type());
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "HashSet.inl"


#endif 
