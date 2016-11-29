////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_ERROR_H__
#define __CORE_ERROR_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{

class Exception;

#ifdef NS_PLATFORM_WINDOWS
/// Generates an error from the code returned by GetLastError()
NS_CORE_KERNEL_API void HandleWinError(const NsChar* what);
/// Formats an error from the code returned by GetLastError()
NS_CORE_KERNEL_API void FormatWinError(const NsChar* what, NsChar* buffer, NsSize size);
#else
/// Generates an error given a system error
NS_CORE_KERNEL_API void HandleSystemError(const NsChar* what, NsInt errnum);
/// Formats an error given a system error
NS_CORE_KERNEL_API void FormatSystemError(const NsChar* what, NsInt errnum, NsChar* buffer,
    NsSize size);
#endif

/// Typedef for Assert Handler
typedef NsBool (*AssertHandlerFn)(const NsChar* exp, const NsChar* filename,
    const NsChar* funcName, NsInt line, NsInt& hitCount, const NsChar* desc);

/// Returns the current Assert Handler
NS_CORE_KERNEL_API AssertHandlerFn GetAssertHandler();

/// Sets handler and returns the previous one
NS_CORE_KERNEL_API AssertHandlerFn SetAssertHandler(AssertHandlerFn handler);

/// Proxy functions for the NS_ASSERT macro
//@{
NS_CORE_KERNEL_API NsBool InvokeAssertHandler(const NsChar* exp, const NsChar* filename, 
    const NsChar* funcName, NsInt line, NsInt& hitCount,
    _Printf_format_string_ const NsChar* descFormat = 0, ...)
    CLANG_ANALYZER_NORETURN NS_FORMAT_PRINTF(6,7);
//@}

// About Variadic Macros
// The "##" before __VA_ARGS__ is needed to avoid the case of zero params. This is required
// by the standard, but MSVC omits it (although it can still be used)
// http://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
// http://msdn.microsoft.com/en-us/library/ms177415%28VS.80%29.aspx

#define NS_INTERNAL_ASSERT(expr, ...) \
    NS_MACRO_BLOCK_BEGIN \
        static NsInt hitCount = 0; \
        if (!(expr)) \
        { \
            if (Noesis::Core::InvokeAssertHandler(#expr, __FILE__, __FUNCTION__, __LINE__, \
                hitCount, ## __VA_ARGS__) == true) \
            { \
                NS_DEBUG_BREAK; \
            } \
        } \
    NS_MACRO_BLOCK_END

#ifdef _PREFAST_
    #define NS_ASSERT(expr, ...) __analysis_assume(!!(expr))
#elif NS_ASSERTS_ENABLED
    #define NS_ASSERT(expr, ...) NS_INTERNAL_ASSERT((expr), ## __VA_ARGS__)
#else
    #define NS_ASSERT(expr, ...) NS_UNUSED(expr)
#endif

#ifdef _PREFAST_
    #define NS_CHECK(expr, ...) __analysis_assume(!!(expr))
#elif NS_CHECKS_ENABLED
    #define NS_CHECK(expr, ...) NS_INTERNAL_ASSERT((expr), ## __VA_ARGS__)
#else
    #define NS_CHECK(expr, ...) NS_UNUSED(expr)
#endif

#define NS_ASSERT_UNREACHABLE NS_ASSERT(false); NS_UNREACHABLE

/// Typedef for Error Handler
typedef void (*ErrorHandlerFn)(const NsChar* filename, NsInt line, const NsChar* desc);

/// Returns the current error handler
NS_CORE_KERNEL_API ErrorHandlerFn GetErrorHandler();

/// Sets handler and returns the previous one
NS_CORE_KERNEL_API ErrorHandlerFn SetErrorHandler(ErrorHandlerFn handler);

/// Invokes the current error handler
NS_NORETURN NS_CORE_KERNEL_API void InvokeErrorHandler(const NsChar* filename, NsInt line,
    _Printf_format_string_ const NsChar* format, ...) NS_FORMAT_PRINTF(3,4);

#define NS_ERROR(...) Noesis::Core::InvokeErrorHandler(__FILE__, __LINE__, __VA_ARGS__)

/// Returns a valid dump location
NS_CORE_KERNEL_API void GetDumpFilename(NsChar* text, NsSize size);

/// Shows a dialog describing the error
NS_CORE_KERNEL_API void ShowExceptionInfoDialog(const Exception& exception, void* info = 0,
    const NsChar* channel = "General");

/// Refines the description of an already caught exception and rethrow it
NS_NORETURN NS_CORE_KERNEL_API void RefineNoesisError(Exception& exception, 
    const NsChar* format, ...);

}
}


#endif
