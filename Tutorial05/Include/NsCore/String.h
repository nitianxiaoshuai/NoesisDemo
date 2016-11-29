////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_STRING_H__
#define __CORE_STRING_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLSafeAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <NsCore/Functional.h>
#include <EASTL/string.h>


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
// NsString, same interface as std::string with the following improvements:
//  - Constructor with printf like parameters (NsString(NsString::CtorSprintf(), format, ...)
//  - Appending with printf like parameters (append_sprintf)
//  - comparei, make_lower, make_upper functions
//  - Trimming functions: ltrim, rtrim, trim
//  - Formatting the string with printf like parameters
//  - set_capacity() to avoid the classical (but obfuscated) swap-trick
//  - force_size() which unilaterally moves the string  end position (mpEnd) to the given location.
//    Useful for when the user writes into the string via some extenal means such as C strcpy
////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
class NsBasicString: public Noesis::Core::nstl::basic_string<T, Allocator>
{
private:
    typedef NsBasicString<T, Allocator> ThisType;
    typedef Noesis::Core::nstl::basic_string<T, Allocator> ParentType;
    typedef Noesis::Core::nstl::basic_string<T, Allocator> BaseType;

public:
    typedef typename BaseType::value_type value_type;
    typedef typename BaseType::allocator_type allocator_type;
    typedef typename BaseType::size_type size_type;
    typedef typename BaseType::CtorDoNotInitialize CtorDoNotInitialize;
    typedef typename BaseType::CtorSprintf CtorSprintf;
    using BaseType::npos;

public:
    NsBasicString();
    explicit NsBasicString(const allocator_type& allocator);
    NsBasicString(const ThisType& x, size_type position, size_type n = npos);
    NsBasicString(const ParentType& x, size_type position, size_type n = npos);
    NsBasicString(const value_type* p, size_type n, const allocator_type&  = allocator_type());
    EASTL_STRING_EXPLICIT NsBasicString(const value_type* p, const allocator_type& allocator = 
        allocator_type());
    NsBasicString(size_type n, value_type c, const allocator_type& allocator = allocator_type());
    NsBasicString(const ThisType& x);
    NsBasicString(const ParentType& x);
    NsBasicString(const value_type* pBegin, const value_type* pEnd,
        const allocator_type& allocator = allocator_type());
    NsBasicString(CtorDoNotInitialize ctorDoNotInitialize, size_type n, 
        const allocator_type& allocator = allocator_type());
    NsBasicString(CtorSprintf ctorSprintf, _Printf_format_string_ const NsChar* format, ...) NS_FORMAT_PRINTF(3,4);

    static ThisType Format(_Printf_format_string_ const NsChar* format, ...) NS_FORMAT_PRINTF(1,2);

    ThisType& operator=(const ThisType& x);
    ThisType& operator=(const value_type* p);
    ThisType& operator=(value_type c);
};

// TODO[jsantos]: this should be done with ALL functions that returns an eastl::basic_string
// For now, this is only a test
template <typename T, typename Allocator>
NsBasicString<T, Allocator> operator+(const NsBasicString<T, Allocator>& a, const NsBasicString<T, Allocator>& b)
{
    return NsBasicString<T, Allocator>((eastl::basic_string<T, Allocator>)a + (eastl::basic_string<T, Allocator>)b);
}

template <typename T, typename Allocator>
NsBasicString<T, Allocator> operator+(const NsBasicString<T, Allocator>& a, const typename NsBasicString<T, Allocator>::value_type* p)
{
    return NsBasicString<T, Allocator>((eastl::basic_string<T, Allocator>)a + p);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
#include "String.inl"


////////////////////////////////////////////////////////////////////////////////////////////////////
// Hashes for string
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace eastl
{
template<> struct hash<NsString>
{
    size_t operator()(const NsString& str) const
    {
        return Noesis::Core::nstl::string_hash<NsString>()(str);
    }
};
}


#endif 
