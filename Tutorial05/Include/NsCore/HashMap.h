////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_HASHMAP_H__
#define __CORE_HASHMAP_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <EASTL/hash_map.h>


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
// NsHashMap, same interface as std::unordered_map with the following improvements:
// - set_max_load_factor() to make the hashtable never rehash
// - bCacheHashCode template parameter to allow the storing of the hash code within the map
// - insert() to insert a default-constructed element
// - find_as() to find using a different type than the template Key type
// - ctor indicating the number of initial buckets
// - bucket_count(), bucket_size() and load_factor() to get information about bucket occupation
// - clear(bool clearBuckets)
// - rehash(size_type nBucketCount)
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Hash, typename Predicate, typename Allocator,
    bool bCacheHashCode>
class NsHashMap:
    public Noesis::Core::nstl::hash_map<Key, T, Hash, Predicate, Allocator, bCacheHashCode>
{
private:
    typedef Noesis::Core::nstl::hash_map<
        Key, T, Hash, Predicate, Allocator, bCacheHashCode> BaseType;

public:
    typedef typename BaseType::allocator_type allocator_type;
    typedef typename BaseType::size_type size_type;

public:
    explicit NsHashMap(const allocator_type& allocator = allocator_type());

    explicit NsHashMap(
        size_type nBucketCount, 
        const Hash& hashFunction = Hash(), 
        const Predicate& predicate = Predicate(), 
        const allocator_type& allocator = allocator_type());

    template <typename ForwardIterator>
    NsHashMap(
        ForwardIterator first, 
        ForwardIterator last, 
        size_type nBucketCount = 0, 
        const Hash& hashFunction = Hash(), 
        const Predicate& predicate = Predicate(), 
        const allocator_type& allocator = allocator_type());
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// NsHashMultimap, same interface as std::unordered_map with the following improvements:
// - set_max_load_factor() to make the hashtable never rehash
// - bCacheHashCode template parameter to allow the storing of the hash code within the map
// - insert() to insert a default-constructed element
// - find_as() to find using a different type than the template Key type
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Hash, typename Predicate, typename Allocator,
    bool bCacheHashCode>
class NsHashMultimap : 
    public Noesis::Core::nstl::hash_multimap<Key, T, Hash, Predicate, Allocator, bCacheHashCode>
{
private:
    typedef Noesis::Core::nstl::hash_multimap<
        Key, T, Hash, Predicate, Allocator, bCacheHashCode> BaseType;

public:
    typedef typename BaseType::allocator_type allocator_type;
    typedef typename BaseType::size_type size_type;

public:
    explicit NsHashMultimap(const allocator_type& allocator = allocator_type());

    explicit NsHashMultimap(
        size_type nBucketCount, 
        const Hash& hashFunction = Hash(), 
        const Predicate& predicate = Predicate(), 
        const allocator_type& allocator = allocator_type());

    template <typename ForwardIterator>
    NsHashMultimap(
        ForwardIterator first, 
        ForwardIterator last, 
        size_type nBucketCount = 0, 
        const Hash& hashFunction = Hash(), 
        const Predicate& predicate = Predicate(), 
        const allocator_type& allocator = allocator_type());
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "HashMap.inl"


#endif 
