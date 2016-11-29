////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEID_H__
#define __CORE_TYPEID_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/Symbol.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metadata used to assign TypeId to types
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_CORE_KERNEL_API TypeId: public TypeMetaData
{
    TypeId(const NsChar* id);
    TypeId(NsSymbol id);

    NsSymbol id;

    NS_DECLARE_REFLECTION(TypeId, TypeMetaData)
};

}
}

#endif
