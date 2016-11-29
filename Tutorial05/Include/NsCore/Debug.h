////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #464]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_DEBUG_H__
#define __CORE_DEBUG_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>


#ifdef NS_PLATFORM_WINDOWS
struct _EXCEPTION_POINTERS;
#endif


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Debugging tools
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Debug
{
    /// Returns a stack trace from the calling point. The stack is returned as an array
    /// of pointers terminated with a null value.
    /// \param buffer destination buffer where stack trace pointers will be stored
    /// \param bufferSize size of buffer (in NsInt64 units)
    /// \param skipCount Number of positions to skip when calculating the stack trace
    NS_CORE_KERNEL_API void GetStack(void** buffer, NsSize bufferSize, NsSize skipCount = 0);

    /// Gets debugging information from a given address
    /// \param addr pointer to the address
    /// \buffer where the description will be stored
    /// \bufferSize size of buffer (in NsChar units)
    /// \index If a number is given here, the description will start with that index.
    ///        For example. Index=1, will generate the description "[1] ..."
    NS_CORE_KERNEL_API void GetInfoFromAddr(void* addr, NsChar* buffer, NsSize bufferSize, 
        NsInt index = -1);

    /// Creates a minidump from the calling point
    /// \param filename name of the minidump file
    NS_CORE_KERNEL_API void CreateMiniDump(const NsChar* filename);
    
    /// Unload all the symbols previously loaded
    NS_CORE_KERNEL_API void UnloadSymbols();

    /// This function must be invoked whenever new dynamic libraries are added to the current
    /// process.
    NS_CORE_KERNEL_API void ReloadSymbols();

    /// Sets the name of the caller thread
    NS_CORE_KERNEL_API void SetThreadName(const NsChar* name);

    /// \return If the current process is running in the context of a debugger
    NS_CORE_KERNEL_API NsBool IsDebuggerPresent();

#ifdef NS_PLATFORM_WINDOWS
    namespace Windows
    {
        NS_CORE_KERNEL_API void CreateMiniDump(const NsChar* filename,
            const _EXCEPTION_POINTERS* exceptInfo);
    }
#endif
}
}
}


#endif
