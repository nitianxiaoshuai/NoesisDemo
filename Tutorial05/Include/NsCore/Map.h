////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_MAP_H__
#define __CORE_MAP_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <EASTL/map.h>


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
// NsMap, same interface as std::map with the following improvements:
// - insert() to insert a default-constructed element
// - find_as() to find using a different type than the template Key type
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
class NsMap : public Noesis::Core::nstl::map<Key, T, Compare, Allocator>
{
private:
    typedef NsMap<Key, T, Compare, Allocator> ThisType;
    typedef Noesis::Core::nstl::map<Key, T, Compare, Allocator> BaseType;

public:
    typedef typename BaseType::allocator_type allocator_type;

public:
    NsMap(const allocator_type& allocator = allocator_type());
    NsMap(const Compare& compare, const allocator_type& allocator = allocator_type());
    NsMap(const ThisType& x);

    template <typename Iterator>
    NsMap(Iterator itBegin, Iterator itEnd);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// NsMultimap 
// NsMultimap, same interface as std::multimap with the following improvements:
// - insert() to insert a default-constructed element
// - find_as() to find using a different type than the template Key type
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename T, typename Compare, typename Allocator>
class NsMultimap : public Noesis::Core::nstl::multimap<Key, T, Compare, Allocator>
{
private:
    typedef NsMultimap<Key, T, Compare, Allocator> ThisType;
    typedef Noesis::Core::nstl::multimap<Key, T, Compare, Allocator> BaseType;

public:
    typedef typename BaseType::allocator_type allocator_type;

public:
    NsMultimap(const allocator_type& allocator = allocator_type());
    NsMultimap(const Compare& compare, const allocator_type& allocator = allocator_type());
    NsMultimap(const ThisType& x);

    template <typename Iterator>
    NsMultimap(Iterator itBegin, Iterator itEnd);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Map.inl"


#endif 
