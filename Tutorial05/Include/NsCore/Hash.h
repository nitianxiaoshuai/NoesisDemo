////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_HASH_H__
#define __CORE_HASH_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An incremental hash function implementation
///
/// Usage:
///
///     IncrementalHasher hasher;
///     hasher.Begin();
///     hasher.Add(v0);
///     hasher.Add(v1);
///     hasher.Add(v2);
///     NsUInt32 hash = hasher.End();
////////////////////////////////////////////////////////////////////////////////////////////////////
class IncrementalHasher
{
public:
    NS_FORCEINLINE void Begin();

    NS_FORCEINLINE void Add(const void* data, NsSize numBytes);
    template<typename T> NS_FORCEINLINE void Add(const T& value);

    NS_FORCEINLINE NsUInt32 End();

private:
    NsUInt32 mHash;
    NsUInt32 mLen;
};

/// Helper function for hashing a memory buffer
NS_CORE_KERNEL_API NsUInt32 Hash(const void* data, NsSize numBytes);

}
}


#include <NsCore/Hash.inl>


#endif
