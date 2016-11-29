////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #715]
// [CR #750]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_MEMORY_H__
#define __CORE_MEMORY_H__


#include <Noesis.h>
#include <NsCore/Types.h>
#include <NsCore/KernelApi.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// NoesisEngine memory management functions. These functions are shortcuts to the equivalents in 
/// the memory manager. For example:
///
///     void* ptr = NsGetKernel()->GetMemoryManager()->Alloc(128);
///
/// is equivalent to
///
///     void* ptr = NsAlloc(128);
///
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
NS_CORE_KERNEL_API void* NsAlloc(size_t size);
NS_CORE_KERNEL_API void* NsRealloc(void* ptr, size_t size);
NS_CORE_KERNEL_API void NsDealloc(void* ptr);
//@}

/// These functions are normally redirected to (NsAlloc/NsDealloc) but if the kernel has not been
/// initialized they are redirected back to standard ANSI functions (AnsiMalloc/AnsiFree)
//@{ 
NS_CORE_KERNEL_API void* NsSafeAlloc(size_t size);
NS_CORE_KERNEL_API void NsSafeDealloc(void* ptr);
//@}

namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Standard C memory functions
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
NS_CORE_KERNEL_API void* AnsiMalloc(size_t size);
NS_CORE_KERNEL_API void* AnsiCalloc(size_t numElements, size_t elementSize);
NS_CORE_KERNEL_API void* AnsiRealloc(void* ptr, size_t size);
NS_CORE_KERNEL_API void AnsiFree(void* ptr);
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Utility class to align size to the specified type boundaries
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct Alignment
{
    enum { Mask = sizeof(T) - 1 };
    static NsSize Align(NsSize size) { return (size + Mask) & ~Mask; }
    static NsBool IsAligned(NsSize size) { return (size & Mask) == 0; }
    static NsBool IsAlignedPtr(const void* ptr) { return (NsUIntPtr(ptr) & Mask) == 0; }
};

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NS_BUILD

#include <new>

#ifdef NS_COMPILER_MSVC
    #pragma warning(push)
    #pragma warning(disable: 4290 28251)
    #if NS_COMPILER_VERSION >= 1900
        #pragma warning(disable: 4595)
    #endif
#endif

#ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Winline-new-delete"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void* operator new(size_t size) throw(std::bad_alloc)
{
    return NsSafeAlloc(size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void* operator new[](size_t size) throw(std::bad_alloc)
{
    return NsSafeAlloc(size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void operator delete(void* ptr) throw()
{
    return NsSafeDealloc(ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void operator delete[](void* ptr) throw()
{
    return NsSafeDealloc(ptr);
}

#ifdef __clang__
    #pragma clang diagnostic pop
#endif

#ifdef NS_COMPILER_MSVC
    #pragma warning(pop)
#endif

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////


#endif
