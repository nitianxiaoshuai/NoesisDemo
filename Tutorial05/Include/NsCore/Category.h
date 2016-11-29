////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_CATEGORY_H__
#define __CORE_CATEGORY_H__


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
/// Metadata used to assign Category to types
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_CORE_KERNEL_API Category: public TypeMetaData
{
    Category(const NsChar* category);
    Category(NsSymbol category);

    NsSymbol category;
    
    NS_DECLARE_REFLECTION(Category, TypeMetaData)
};

}
}

#endif
