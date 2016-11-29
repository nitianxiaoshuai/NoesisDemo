////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_LIST_H__
#define __CORE_LIST_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <EASTL/list.h>


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
// NsList, same interface as std::list
//  - push_back() without parameters to insert a default value and return a reference to it
//  - push_front() without parameters to insert a default value and return a reference to it
//  - push_back_uninitialized() & push_front_uninitialized()
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
class NsList : public Noesis::Core::nstl::list<T, Allocator>
{
private:
    typedef NsList<T, Allocator> ThisType;
    typedef Noesis::Core::nstl::list<T, Allocator> BaseType;

public:
    typedef typename BaseType::value_type value_type;
    typedef typename BaseType::allocator_type allocator_type;
    typedef typename BaseType::size_type size_type;

public:
    NsList();

    NsList(const allocator_type& allocator);
    
    explicit NsList(size_type n, const allocator_type& allocator = allocator_type());
    
    NsList(size_type n, const value_type& value, const allocator_type& allocator = allocator_type());
    
    NsList(const ThisType& x);

    template <typename InputIterator>
    NsList(InputIterator first, InputIterator last);

    ThisType& operator=(const ThisType& x);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "List.inl"


#endif 
