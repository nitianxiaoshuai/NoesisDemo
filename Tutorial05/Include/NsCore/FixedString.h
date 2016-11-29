////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_FIXEDSTRING_H__
#define __CORE_FIXEDSTRING_H__


#include <Noesis.h>
#include <NsCore/NSTLDefaultAllocator.h>
#include <NsCore/NSTLForwards.h>
#include <NsCore/Functional.h>
#include <EASTL/fixed_string.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////
template <int N, bool EnableOverflow, typename Allocator>
class NsFixedString: public eastl::fixed_string<NsChar, N, EnableOverflow, Allocator>
{
public:
    NsFixedString() {}
    NsFixedString(const NsChar* p): eastl::fixed_string<NsChar, N, EnableOverflow, Allocator>(p) {}
};


////////////////////////////////////////////////////////////////////////////////////////////////////
// Hashes for string
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace eastl
{
template<int N, bool EnableOverflow, typename Allocator>
struct hash<NsFixedString<N, EnableOverflow, Allocator> >
{
    size_t operator()(const NsFixedString<N, EnableOverflow, Allocator>& str) const
    {
        return Noesis::Core::nstl::string_hash<NsFixedString<N, EnableOverflow, Allocator> >()(str);
    }
};
}


#endif 
