////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_VECTOR_H__
#define __CORE_VECTOR_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <EASTL/vector.h>


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
// NsVector, same interface as std::vector with the following improvements:
//  - set_capacity() to avoid the classical (but obfuscated) swap-trick
//  - push_back() without parameters to insert a default value and return a reference to it
//  - data() for getting a raw pointer to data. It works even with an empty vector
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
class NsVector: public Noesis::Core::nstl::vector<T, Allocator>
{
private:
    typedef NsVector<T, Allocator> ThisType;
    typedef Noesis::Core::nstl::vector<T, Allocator> BaseType;

public:
    typedef typename BaseType::value_type value_type;
    typedef typename BaseType::allocator_type allocator_type;
    typedef typename BaseType::size_type size_type;

public:
    NsVector();
    
    explicit NsVector(const allocator_type& allocator);
    
    explicit NsVector(size_type n, const allocator_type& allocator = allocator_type());
    
    NsVector(size_type n, const value_type& value, const allocator_type& allocator = allocator_type());
    
    NsVector(const ThisType& x);

    template <typename InputIterator>
    NsVector(InputIterator first, InputIterator last);

    ThisType& operator=(const ThisType& x);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Vector.inl"


#endif 
