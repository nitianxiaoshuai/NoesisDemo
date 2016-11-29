////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_REGISTERCOMPONENT_H__
#define __CORE_REGISTERCOMPONENT_H__


#include <NsCore/TypeOf.h>
#include <NsCore/KernelApi.h>
#include <NsCore/ComponentFactory.h>


namespace Noesis
{
namespace Core
{

NS_CORE_KERNEL_API void RegisterComponent(const TypeClass* typeClass,
    ComponentFactory::CreatorFn creatorFn);
NS_CORE_KERNEL_API void UnregisterComponent(const TypeClass* typeClass);

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> Noesis::Core::BaseComponent* NsComponentCreator(Noesis::Core::Symbol)
{
    return new T;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> void NsRegisterComponent()
{
    Noesis::Core::RegisterComponent(Noesis::Core::TypeOf<T>(), NsComponentCreator<T>);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> void NsUnregisterComponent()
{
    Noesis::Core::UnregisterComponent(Noesis::Core::TypeOf<T>());
}

#endif
