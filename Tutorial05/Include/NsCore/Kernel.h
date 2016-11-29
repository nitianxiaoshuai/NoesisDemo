////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_KERNEL_H__
#define __CORE_KERNEL_H__


#include <NsCore/Types.h>
#include <NsCore/KernelApi.h>
#include <NsCore/NSTLForwards.h>
#include <NsCore/PtrForward.h>
#include <NsCore/DelegateForward.h>


NS_CFORWARD(Core, Logger)
NS_CFORWARD(Core, MemoryManager)
NS_CFORWARD(Core, MemoryAllocator)
NS_CFORWARD(Core, ReflectionRegistry)
NS_CFORWARD(Core, ComponentFactory)
NS_CFORWARD(Core, Symbol)
NS_IFORWARD(Core, IKernelSystem)


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// First initialized object and the last one being shutdown.
/// Acts as a singleton that can be accessed by NsGetKernel()
////////////////////////////////////////////////////////////////////////////////////////////////////
class Kernel
{
public:
    /// Checks if kernel is initialized
    virtual NsBool IsInitialized() const = 0;

    /// Initializes the kernel. An optional memory allocator can be passed to control allocations
    virtual void Init(MemoryAllocator* memoryAllocator, const NsChar* consoleIP) = 0;

    /// Shuts down the kernel
    virtual void Shutdown() = 0;

    /// Returns the thread where the kernel was initialized
    virtual NsUInt GetMainThreadId() const = 0;

    /// Initializes all registered systems. System initialization order is done by dependency
    virtual void InitSystems() = 0;

    /// Access to Kernel Modules
    //@{
    virtual Logger* GetLogger() const = 0;
    virtual MemoryManager* GetMemoryManager() const = 0;
    virtual ReflectionRegistry* GetReflectionRegistry() const = 0;
    virtual ComponentFactory* GetComponentFactory() const = 0;
    //@}

    /// Remote console commands
    typedef Delegate<void (const NsChar* params)> CommandDelegate;
    virtual void RegisterCommand(const NsChar* command, const CommandDelegate& callback) = 0;
};

}
}

/// Returns kernel instance
NS_CORE_KERNEL_API Noesis::Core::Kernel* NsGetKernel();

#if NS_INSTRUMENTED_ENABLED
    #define NS_REGISTER_COMMAND(n, d) NsGetKernel()->RegisterCommand(n, d)
#else
    #define NS_REGISTER_COMMAND(n, d) NS_NOOP
#endif


#endif
