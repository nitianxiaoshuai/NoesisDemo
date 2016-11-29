////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_VALUEHELPER_H__
#define __CORE_VALUEHELPER_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/String.h>


namespace Noesis
{
namespace Core
{

/// Returns a string that represents the passed value
template<class T> NsString ToString(const T& value);

/// Returns a hash code for the passed value
template<class T> NsUInt32 GetHashCode(const T& value);

}
}

// Inline include
#include <NsCore/ValueHelper.inl>


#endif
