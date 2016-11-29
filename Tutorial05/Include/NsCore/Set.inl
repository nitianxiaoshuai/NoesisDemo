////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
inline NsSet<Key, Compare, Allocator>::NsSet(const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
inline NsSet<Key, Compare, Allocator>::NsSet(
    const Compare& compare, 
    const allocator_type& allocator) :
    BaseType(compare, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
inline NsSet<Key, Compare, Allocator>::NsSet(const ThisType& x) :
    BaseType(x)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
template <typename Iterator>
inline NsSet<Key, Compare, Allocator>::NsSet(Iterator itBegin, Iterator itEnd) :
    BaseType(itBegin, itEnd)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
inline NsMultiset<Key, Compare, Allocator>::NsMultiset(const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
inline NsMultiset<Key, Compare, Allocator>::NsMultiset(
    const Compare& compare, 
    const allocator_type& allocator) :
    BaseType(compare, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
inline NsMultiset<Key, Compare, Allocator>::NsMultiset(const ThisType& x) :
    BaseType(x)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
template <typename Iterator>
inline NsMultiset<Key, Compare, Allocator>::NsMultiset(Iterator itBegin, Iterator itEnd) :
    BaseType(itBegin, itEnd)
{
}
