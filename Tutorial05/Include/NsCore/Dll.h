////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_DLL_H__
#define __CORE_DLL_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/String.h>


namespace Noesis
{
namespace Core
{
namespace Dll
{

typedef void* Handle;

/// Load dynamic library
NS_CORE_KERNEL_API Handle TryLoad(const NsChar* filename);
NS_CORE_KERNEL_API Handle Load(const NsChar* filename);

/// Unload dynamic library
NS_CORE_KERNEL_API void Unload(Handle handle);

/// Gets the directory of the module that is currently executing the code
NS_CORE_KERNEL_API NsString GetCurrentModulePath();

/// Retrieves the address of an exported function
NS_CORE_KERNEL_API void* TryGetProc(Handle handle, const NsChar* procName);
NS_CORE_KERNEL_API void* GetProc(Handle handle, const NsChar* procName);
template<class T> T TryGetProcT(Handle handle, const NsChar* procName);
template<class T> T GetProcT(Handle handle, const NsChar* procName);

/// Returns the extension associated to dynamic libraries
NS_CORE_KERNEL_API const NsChar* GetDynamicLibraryExtension();

}
}
}

// Inline include
#include <NsCore/Dll.inl>


#endif
