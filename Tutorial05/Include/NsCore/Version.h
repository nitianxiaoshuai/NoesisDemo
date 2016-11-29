////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_VERSION_H__
#define __CORE_VERSION_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{
/// Returns the build version for the current noesis ditribution. A build version is a string
/// of the from XX.XX.XX.XX where the last number correspond to the source code repository revision 
//@{
NS_CORE_KERNEL_API const NsChar* GetBuildVersion();
//@}
}
}

#endif
