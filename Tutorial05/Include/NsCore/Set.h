////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_SET_H__
#define __CORE_SET_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <EASTL/set.h>


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
// NsSet, same interface as std::set with the following improvements:
// - find_as() to find using a different type than the template Key type
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
class NsSet : public Noesis::Core::nstl::set<Key, Compare, Allocator>
{
private:
    typedef NsSet<Key, Compare, Allocator> ThisType;
    typedef Noesis::Core::nstl::set<Key, Compare, Allocator> BaseType;

public:
    typedef typename BaseType::allocator_type allocator_type;

public:
    NsSet(const allocator_type& allocator = allocator_type());
    NsSet(const Compare& compare, const allocator_type& allocator = allocator_type());
    NsSet(const ThisType& x);

    template <typename Iterator>
    NsSet(Iterator itBegin, Iterator itEnd);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// NsMultiset, same interface as std::multiset with the following improvements:
// - find_as() to find using a different type than the template Key type
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Compare, typename Allocator>
class NsMultiset : public Noesis::Core::nstl::multiset<Key, Compare, Allocator>
{
private:
    typedef NsSet<Key, Compare, Allocator> ThisType;
    typedef Noesis::Core::nstl::multiset<Key, Compare, Allocator> BaseType;

public:
    typedef typename BaseType::allocator_type allocator_type;

public:
    NsMultiset(const allocator_type& allocator = allocator_type());
    NsMultiset(const Compare& compare, const allocator_type& allocator = allocator_type());
    NsMultiset(const ThisType& x);

    template <typename Iterator>
    NsMultiset(Iterator itBegin, Iterator itEnd);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Set.inl"


#endif 
