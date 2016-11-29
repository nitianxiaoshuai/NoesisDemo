////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_SYSTEMID_H__
#define __CORE_SYSTEMID_H__


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
/// Id for kernel system. If this metadata is not found, TypeId is used
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_CORE_KERNEL_API SystemId: public TypeMetaData
{
    SystemId(const NsChar* id);
    SystemId(NsSymbol id);

    NsSymbol id;
    
    NS_DECLARE_REFLECTION(SystemId, TypeMetaData)
};

}
}

#endif
