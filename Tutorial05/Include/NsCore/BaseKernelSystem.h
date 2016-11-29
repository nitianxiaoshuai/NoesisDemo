////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #931]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_BASEKERNELSYSTEM_H__
#define __CORE_BASEKERNELSYSTEM_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/NSTLForwards.h>
#include <NsCore/Symbol.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for kernel systems
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API BaseKernelSystem: public BaseComponent
{
public:
    BaseKernelSystem();
    ~BaseKernelSystem();

    /// Indicates if system is initialized
    NsBool IsInitialized() const;

    /// Initializes the system
    virtual void Init();

    /// Shuts down the system
    virtual void Shutdown();

    /// Systems with higher priority are initialized first
    virtual NsSize GetPriority() const;

private:
    NsBool mInitialized;

    NS_DECLARE_REFLECTION(BaseKernelSystem, BaseComponent)
};

}
}


#endif
