////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPECLASSBUILDERPROXY_H__
#define __CORE_TYPECLASSBUILDERPROXY_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/StaticAssert.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
class Symbol;
class TypeInfo;
class Type;
class TypeClass;
class TypeClassBuilder;
class TypeMetaData;
class TypeProperty;
class ParamStack;
class FunctionInvoker;
//@}

NS_CORE_KERNEL_API Type* CreateTypeClass(const TypeInfo& typeInfo, NsBool isInterface);
NS_CORE_KERNEL_API void AddBase(TypeClassBuilder* typeClass, const TypeClass* baseType);
NS_CORE_KERNEL_API void AddMetaData(TypeClassBuilder* typeClass, TypeMetaData* metaData);
NS_CORE_KERNEL_API void AddInterface(TypeClassBuilder* typeClass, const TypeClass* interfaceType,
    NsSize offset);
NS_CORE_KERNEL_API void AddProperty(TypeClassBuilder* typeClass, TypeProperty* prop);

/// Calculates the offset between a class and a parent class
/// \remarks It checks at compile time that class inherits from the parent class
template<class Class, class Parent> NsSize CalculateParentOffset()
{
    NS_STATIC_ASSERT((IsDerived<Class, Parent>::Result), CLASS_MUST_INHERIT_FROM_PARENT);

    // First we define a pointer to the Class, then we cast to the Parent class, and finally we
    // calculate the offset from the Class pointer to the Parent class pointer
    Class* ptr = reinterpret_cast<Class*>(-1);
    NsByte* classPtr = reinterpret_cast<NsByte*>(ptr);
    NsByte* parentPtr = reinterpret_cast<NsByte*>(static_cast<Parent*>(ptr));

    return static_cast<NsSize>(parentPtr - classPtr);
}


}
}


#endif
