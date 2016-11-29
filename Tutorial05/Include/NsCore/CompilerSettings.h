////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_COMPILERSETTINGS_H__
#define __CORE_COMPILERSETTINGS_H__


// To suppress warnings about unused variables
#define NS_UNUSED(...) (void)(true ? (void)0 : ((void)(__VA_ARGS__)))

// Macro for generating unique variable names inside a cpp file.
#define NS_UNIQUE_NAME(prefix) NS_UNIQUE_NAME_INTERNAL0(prefix, __COUNTER__)
#define NS_UNIQUE_NAME_INTERNAL0(a, b) NS_UNIQUE_NAME_INTERNAL1(a, b)
#define NS_UNIQUE_NAME_INTERNAL1(a, b) a##b

#define NS_STRINGIFY(x) #x
#define NS_TOSTRING(x) NS_STRINGIFY(x)
#define NS_CONFIG_NAME NS_TOSTRING(NS_CONFIG)

/// Paranoid macro to activate extra level of debugging
/// Level0 is the default for debug and release. No extra checks are done
/// Level1 activates extra checkings decreasing a bit the program execution speed
/// Level2 activates more extra checking that drastically alters the program execution speed 
/// Level3 activates all the paranoids. Every things is slow here. Your last chance for that bug
#ifndef NS_PARANOID_LEVEL
    #define NS_PARANOID_LEVEL 0
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Compiler dependant settings. Unifies the differences between compilers
////////////////////////////////////////////////////////////////////////////////////////////////////

// Microsoft VC++
#if defined(_MSC_VER) && _MSC_VER >= 1400
    #define NS_COMPILER_MSVC
    #define NS_COMPILER_VERSION _MSC_VER
    #define NS_COMPILER_NAME "Microsoft Visual C++"

    #define NS_MACRO_BLOCK_BEGIN \
        __pragma(warning(push)) \
        __pragma(warning(disable:4127)) \
        do {
    #define NS_MACRO_BLOCK_END \
        } while(false) \
        __pragma(warning(pop))
    #define NS_NOOP __noop
    #define NS_DEBUG_BREAK __debugbreak()
    #define NS_NORETURN __declspec(noreturn)
    #define NS_FORCEINLINE __forceinline
    #define NS_NOINLINE __declspec(noinline)
    #define NS_UNUSED_FUNC
    #define NS_MSVC_WARNING_PUSH __pragma(warning(push))
    #define NS_MSVC_WARNING_DISABLE(n) __pragma(warning(disable:n))
    #define NS_MSVC_WARNING_SUPPRESS(n) __pragma(warning(suppress:n))
    #define NS_MSVC_WARNING_POP __pragma(warning(pop))
    #define NS_GCC_WARNING_PUSH
    #define NS_GCC_WARNING_DISABLE(x)
    #define NS_GCC_WARNING_POP
    #define NS_DLL_EXPORT __declspec(dllexport)
    #define NS_DLL_IMPORT __declspec(dllimport)
    #define NS_ALIGN(_x) __declspec(align(_x))
    #define NS_EXTERN_TEMPLATE template
    #define NS_INTERFACE struct __declspec(novtable)
    #define NS_ASSUME(cond) __assume(cond)
    #define NS_UNREACHABLE __assume(false)
    #define NS_FORMAT_PRINTF(m,n)
    #define NS_COUNTOF(_x) _countof(_x)

    #ifndef PATH_MAX
        #define PATH_MAX 260
    #endif

    #if _MSC_VER >= 1500
        #include <sal.h>
    #else
        #define _Printf_format_string_
    #endif

// GNU Gcc C++ compiler
#elif defined(__GNUG__) && __GNUG__ >= 4
    #define NS_COMPILER_GCC
    #define NS_COMPILER_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
    #define NS_COMPILER_NAME "GCC"

    #define NS_MACRO_BLOCK_BEGIN do {
    #define NS_MACRO_BLOCK_END } while (false)
    #define NS_NOOP (void)(sizeof(0))
    #if defined(__i386__) || defined(__x86_64__)
        #define NS_DEBUG_BREAK __asm__("int $0x03")
    #elif defined(__arm__)
        #include <assert.h>
        #ifdef ANDROID
            #include <unistd.h>
        #endif
        #define NS_DEBUG_BREAK \
            __asm__ __volatile__ ( \
                "mov r0, %0\n" \
                "mov r1, %1\n" \
                "mov r12, #37\n" \
                "swi 128\n" \
                : : "r" (getpid ()), "r" (SIGINT) : "r12", "r0", "r1", "cc" \
            )
    #else
        #define NS_DEBUG_BREAK __builtin_trap()
    #endif
    
    #define NS_NORETURN __attribute__((noreturn))
    #define NS_FORCEINLINE __attribute__ ((always_inline)) inline
    #define NS_NOINLINE __attribute__ ((noinline))
    #define NS_UNUSED_FUNC __attribute__ ((unused))
    #define NS_MSVC_WARNING_PUSH
    #define NS_MSVC_WARNING_DISABLE(n)
    #define NS_MSVC_WARNING_SUPPRESS(n)
    #define NS_MSVC_WARNING_POP
    #define NS_GCC_WARNING_PUSH _Pragma("GCC diagnostic push")
    #define NS_GCC_WARNING_DISABLE(x) _Pragma(NS_STRINGIFY(GCC diagnostic ignored x))
    #define NS_GCC_WARNING_POP _Pragma("GCC diagnostic pop")

    // http://gcc.gnu.org/wiki/Visibility
    #define NS_DLL_EXPORT __attribute__ ((visibility("default")))
    #define NS_DLL_IMPORT __attribute__ ((visibility("default")))
    #define NS_ALIGN(_x) __attribute__((aligned(_x)))
    #define NS_EXTERN_TEMPLATE extern template
    #define NS_INTERFACE struct
    #define NS_ASSUME(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)
    #define NS_UNREACHABLE __builtin_unreachable()
    #define NS_FORMAT_PRINTF(m,n) __attribute__ ((format (printf, m, n)))
    
    // http://cnicholson.net/2011/01/stupid-c-tricks-a-better-sizeof_array/
    #include <cstddef>
    template<typename T, size_t N> char (&NS_COUNTOF_REQUIRES_ARRAY_ARGUMENT(const T(&)[N]))[N];
    #define NS_COUNTOF(_x) sizeof(NS_COUNTOF_REQUIRES_ARRAY_ARGUMENT(_x))

    // SAL Annotations
    #define _Printf_format_string_

#else
    #error Compiler not supported
#endif

// Only bindings are exported in Unity/NET API
#if defined(NS_UNITY3D) || defined(NS_NETSDK)
    #undef NS_DLL_EXPORT
    #define NS_DLL_EXPORT
    #undef NS_DLL_IMPORT
    #define NS_DLL_IMPORT
#endif

#if defined(__GXX_ABI_VERSION) && defined(__GXX_RTTI)
    #define NS_COMPILER_RTTI
#elif defined(_MSC_VER) && defined(_CPPRTTI)
    #define NS_COMPILER_RTTI
#endif

#ifndef __has_feature
    #define __has_feature(x) 0
#endif

#if __has_feature(attribute_analyzer_noreturn)
    #define CLANG_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
#else
    #define CLANG_ANALYZER_NORETURN
#endif

#ifndef NS_LOGGER_ENABLED
    #define NS_LOGGER_ENABLED 0
#endif

#ifndef NS_ASSERTS_ENABLED
    #define NS_ASSERTS_ENABLED 0
#endif

#ifndef NS_CHECKS_ENABLED
    #define NS_CHECKS_ENABLED 0
#endif

#ifndef NS_INSTRUMENTED_ENABLED
    #define NS_INSTRUMENTED_ENABLED 0
#endif

// GCC on some platforms (e.g. PS3) defines _NO_EX when exceptions are disabled.
#if defined(NS_COMPILER_GCC) && defined(__EXCEPTIONS)
    #define NS_EXCEPTIONS_ENABLED
#elif defined(NS_COMPILER_MSVC) && defined(_CPPUNWIND)
    #define NS_EXCEPTIONS_ENABLED
#endif

// Foward declaration helpers
#define NS_IFORWARD(n, x) namespace Noesis { namespace n { NS_INTERFACE x; } }
#define NS_CFORWARD(n, x) namespace Noesis { namespace n { class x; } }
#define NS_SFORWARD(n, x) namespace Noesis { namespace n { struct x; } }

#endif
