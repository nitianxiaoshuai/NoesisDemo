////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
inline NsMap<Key, T, Compare, Allocator>::NsMap(const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
inline NsMap<Key, T, Compare, Allocator>::NsMap(
    const Compare& compare, 
    const allocator_type& allocator) :
    BaseType(compare, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
inline NsMap<Key, T, Compare, Allocator>::NsMap(const ThisType& x) :
    BaseType(x)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
template <typename Iterator>
inline NsMap<Key, T, Compare, Allocator>::NsMap(Iterator itBegin, Iterator itEnd) :
    BaseType(itBegin, itEnd)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
inline NsMultimap<Key, T, Compare, Allocator>::NsMultimap(const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
inline NsMultimap<Key, T, Compare, Allocator>::NsMultimap(
    const Compare& compare, 
    const allocator_type& allocator) : 
    BaseType(compare, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
inline NsMultimap<Key, T, Compare, Allocator>::NsMultimap(const ThisType& x) :
    BaseType(x)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
template <typename Iterator>
inline NsMultimap<Key, T, Compare, Allocator>::NsMultimap(Iterator itBegin, Iterator itEnd) :
    BaseType(itBegin, itEnd)
{
}

