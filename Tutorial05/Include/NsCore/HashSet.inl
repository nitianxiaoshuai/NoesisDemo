////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Value, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
NsHashSet<Value, Hash, Predicate, Allocator, bCacheHashCode>::NsHashSet(
    const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Value, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
NsHashSet<Value, Hash, Predicate, Allocator, bCacheHashCode>::NsHashSet(
    size_type nBucketCount, 
    const Hash& hashFunction, 
    const Predicate& predicate, 
    const allocator_type& allocator) :
    BaseType(nBucketCount, hashFunction, predicate, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Value, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
template <typename FowardIterator>
NsHashSet<Value, Hash, Predicate, Allocator, bCacheHashCode>::NsHashSet(
    FowardIterator first, 
    FowardIterator last, 
    size_type nBucketCount, 
    const Hash& hashFunction, 
    const Predicate& predicate, 
    const allocator_type& allocator) :
    BaseType(first, last, nBucketCount, hashFunction, predicate, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Value, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
NsHashMultiset<Value, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMultiset(
    const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Value, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
NsHashMultiset<Value, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMultiset(
    size_type nBucketCount, 
    const Hash& hashFunction, 
    const Predicate& predicate, 
    const allocator_type& allocator) :
    BaseType(nBucketCount, hashFunction, predicate, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Value, typename Hash, typename Predicate, typename Allocator, bool bCacheHashCode>
template <typename FowardIterator>
NsHashMultiset<Value, Hash, Predicate, Allocator, bCacheHashCode>::NsHashMultiset(
    FowardIterator first, 
    FowardIterator last, 
    size_type nBucketCount, 
    const Hash& hashFunction, 
    const Predicate& predicate, 
    const allocator_type& allocator) :
    BaseType(first, last, nBucketCount, hashFunction, predicate, allocator)
{
}
