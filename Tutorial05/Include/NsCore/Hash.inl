////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>
#include <NsCore/Memory.h>


namespace Noesis
{
namespace Core
{

// MurmurHash2A, by Austin Appleby
// https://github.com/aappleby/smhasher
//
// Doing an incremental implementation is not easy due to memory alignment accesses. There is
// a sample implementation in GitHub (CMurmurHash2A) but it not very efficient and does
// non-alignment reads. The incremental implementation provided here is not 100% strict. If you
// split the same data in different partitionings the hash value you get out will not necessarily
// be the same. But it allow us to have a faster implementation. I have done a minor change in
// MurmurHash2A to ensure same results if using multiple of 4-bytes sizes.


#define MURMUR_M 0x5bd1e995
#define MURMUR_R 24
#define MMIX(h, k) { k *= MURMUR_M; k ^= k >> MURMUR_R; k *= MURMUR_M; h *= MURMUR_M; h ^= k; }

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_FORCEINLINE NsUInt32 MurmurHash2A_Body(const NsByte* data, NsSize size, NsUInt32 seed)
{
    NS_ASSERT(size < 4 || Alignment<NsUInt32>::IsAlignedPtr(data));

    NsUInt32 h = seed;

    while (size >= 4)
    {
        NsUInt32 k = *reinterpret_cast<const NsUInt32*>(data);

        MMIX(h, k);

        data += 4;
        size -= 4;
    }

    NsUInt32 t = 0;

    switch (size)
    {
        case 3: t ^= data[2] << 16;
        case 2: t ^= data[1] << 8;
        case 1: t ^= data[0];
            MMIX(h, t); // This is my modification to the original MurmurHash2A implementation
    };

    return h;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_FORCEINLINE NsUInt32 MurmurHash2A_Tail(NsSize l, NsUInt32 h)
{
    MMIX(h, l);

    h ^= h >> 13;
    h *= MURMUR_M;
    h ^= h >> 15;

    return h;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void IncrementalHasher::Begin()
{
    mHash = 0;
    mLen = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void IncrementalHasher::Add(const void* data, NsSize numBytes)
{
    mHash = MurmurHash2A_Body((const NsByte*)data, numBytes, mHash);
    mLen += numBytes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T> void IncrementalHasher::Add(const T& value)
{
    Add(&value, sizeof(T));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 IncrementalHasher::End()
{
    return MurmurHash2A_Tail(mLen, mHash);
}

#undef MURMUR_M
#undef MURMUR_R
#undef MMIX


}
}
