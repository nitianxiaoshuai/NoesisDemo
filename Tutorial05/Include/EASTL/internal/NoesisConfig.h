////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __NOESISCONFIG_H__
#define __NOESISCONFIG_H__


#ifdef ANDROID
    #include <stdint.h>
#elif defined(__linux__) || (defined(__APPLE__) && __APPLE__)
    #include <cstddef>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && _MSC_VER >= 1400
    #define __NS_DLL_EXPORT__ __declspec(dllexport)
    #define __NS_DLL_IMPORT__ __declspec(dllimport)
    #define __NS_DEBUG_BREAK__ __debugbreak()
    #if _MSC_VER >= 1500
        #include <sal.h>
    #else
        #define _Printf_format_string_
    #endif
#elif defined(__GNUG__) && __GNUG__ >= 4
    #define __NS_DLL_EXPORT__ __attribute__ ((visibility("default")))
    #define __NS_DLL_IMPORT__ __attribute__ ((visibility("default")))
    #ifdef __i386__
        #define __NS_DEBUG_BREAK__ __asm__("int $0x03");
    #else
        #define __NS_DEBUG_BREAK__ __builtin_trap()
    #endif
    #define _Printf_format_string_
#else
    #error Compiler not supported
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Only bindings are exported in Unity/NET API
#if defined(NS_UNITY3D) || defined(NS_NETSDK)
    #undef __NS_DLL_EXPORT__
    #define __NS_DLL_EXPORT__
    #undef __NS_DLL_IMPORT__
    #define __NS_DLL_IMPORT__
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(EASTL_API)
    #if !defined(NS_CORE_KERNEL_EXPORTS)
        #define EASTL_API __NS_DLL_IMPORT__
    #else
        #define EASTL_API __NS_DLL_EXPORT__
    #endif
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NS_CORE_KERNEL_EXPORTS
    #define __NS_CORE_KERNEL_API__ __NS_DLL_EXPORT__
#else
    #define __NS_CORE_KERNEL_API__ __NS_DLL_IMPORT__
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
#define EASTL_NAME_ENABLED 0
#define EASTL_EXCEPTIONS_ENABLED 0
#define EASTL_RTTI_ENABLED 0
#define EASTL_DEBUGPARAMS_LEVEL 0
#define EASTL_USER_DEFINED_ALLOCATOR
#define EASTL_SIZE_T unsigned int
#define EASTL_SSIZE_T signed int
#define EASTL_MINMAX_ENABLED 0
#define EASTL_STD_ITERATOR_CATEGORY_ENABLED 0


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Default Allocator
////////////////////////////////////////////////////////////////////////////////////////////////////
__NS_CORE_KERNEL_API__ void* NsAlloc(size_t size);
__NS_CORE_KERNEL_API__ void NsDealloc(void* ptr);


namespace eastl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class NsAllocator
{
public:
    NsAllocator(const char* = 0) {}
    NsAllocator(const NsAllocator&, const char*) {}
    void* allocate(size_t n, int = 0) { return NsAlloc(n); }
    void* allocate(size_t n, size_t, size_t, int = 0) { return NsAlloc(n); }
    void deallocate(void* p, size_t) { NsDealloc(p); }
    const char* get_name() const { return ""; }
    void set_name(const char*) {}
    
    static NsAllocator* GetInstance()
    {
#ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable:4640)
#endif
        static NsAllocator allocator;
        return &allocator;
#ifdef _MSC_VER
        #pragma warning(pop)
#endif
    }
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
#define EASTLAllocatorType eastl::NsAllocator
#define EASTLAllocatorDefault eastl::NsAllocator::GetInstance


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Asserts
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Noesis
{
namespace Core
{
__NS_CORE_KERNEL_API__ bool InvokeAssertHandler(const char* exp, const char* filename, 
    const char* funcName, int line, int& hitCount, _Printf_format_string_ const char* descFormat,
    ...);
}
}

#ifdef ANDROID
    inline void EASTL_DEBUG_BREAK()
    {
        __NS_DEBUG_BREAK__;
    }
#endif

#if NS_ASSERTS_ENABLED
    #define EASTL_ASSERT(expr) \
        { \
            static int hitCount = 0; \
            if (!(expr)) \
            { \
                if (Noesis::Core::InvokeAssertHandler(#expr, __FILE__, __FUNCTION__, __LINE__, \
                    hitCount, 0) == true) \
                { \
                    __NS_DEBUG_BREAK__; \
                } \
            } \
        }
#else
    #define EASTL_ASSERT(expr) ((void)0)
#endif


#if NS_ASSERTS_ENABLED
    #define EASTL_FAIL_MSG(message) \
        { \
            static int hitCount = 0; \
            if (Noesis::Core::InvokeAssertHandler(#message, __FILE__, __FUNCTION__, __LINE__, \
                hitCount, 0) == true) \
            { \
                __NS_DEBUG_BREAK__; \
            } \
        }
#else
    #define EASTL_FAIL_MSG(message) ((void)0)
#endif

#endif 
