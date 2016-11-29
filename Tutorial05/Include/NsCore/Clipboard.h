////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_CLIPBOARD_H__
#define __CORE_CLIPBOARD_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/String.h>


namespace Noesis
{
namespace Core
{
namespace Clipboard
{

/// Stores text data on the Clipboard
NS_CORE_KERNEL_API void Set(const NsChar* text);

/// Returns a string containing text data on the Clipboard
NS_CORE_KERNEL_API NsString Get();

}
}
}


#endif
