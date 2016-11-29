////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <
    typename Key, 
    typename T, 
    typename Hash, 
    typename Predicate, 
    typename Allocator,
    bool bCacheHashCode>
inline NsHashMap<Key, T, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMap(
    const allocator_type& allocator) :
    BaseType(allocator)
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////
template <
typename Key, 
typename T, 
typename Hash, 
typename Predicate, 
typename Allocator,
bool bCacheHashCode>
inline NsHashMap<Key, T, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMap(
    size_type nBucketCount, 
    const Hash& hashFunction, 
    const Predicate& predicate, 
    const allocator_type& allocator) :
    BaseType(nBucketCount, hashFunction, predicate, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <
typename Key, 
typename T, 
typename Hash, 
typename Predicate, 
typename Allocator,
bool bCacheHashCode>
template <typename ForwardIterator>
inline NsHashMap<Key, T, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMap(
    ForwardIterator first, 
    ForwardIterator last, 
    size_type nBucketCount, 
    const Hash& hashFunction, 
    const Predicate& predicate, 
    const allocator_type& allocator) :
    BaseType(first, last, nBucketCount, hashFunction, predicate, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <
    typename Key, 
    typename T, 
    typename Hash, 
    typename Predicate, 
    typename Allocator,
    bool bCacheHashCode>
inline NsHashMultimap<Key, T, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMultimap(
    const allocator_type& allocator) :
    BaseType(allocator)
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////
template <
    typename Key, 
    typename T, 
    typename Hash, 
    typename Predicate, 
    typename Allocator,
    bool bCacheHashCode>
inline NsHashMultimap<Key, T, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMultimap(
    size_type nBucketCount, 
    const Hash& hashFunction, 
    const Predicate& predicate, 
    const allocator_type& allocator) :
    BaseType(nBucketCount, hashFunction, predicate, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <
    typename Key, 
    typename T, 
    typename Hash, 
    typename Predicate, 
    typename Allocator,
    bool bCacheHashCode>
    template <typename ForwardIterator>
inline NsHashMultimap<Key, T, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMultimap(
    ForwardIterator first, 
    ForwardIterator last, 
    size_type nBucketCount, 
    const Hash& hashFunction, 
    const Predicate& predicate, 
    const allocator_type& allocator) :
    BaseType(first, last, nBucketCount, hashFunction, predicate, allocator)
{
}