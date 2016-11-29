////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_MEMORYSTREAM_H__
#define __CORE_MEMORYSTREAM_H__


#include <Noesis.h>
#include <NsCore/Stream.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Stream implementation using a memory buffer
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API MemoryStream: public Stream
{
public:
    /// Constructor
    MemoryStream(const void *buffer, NsSize size);

    /// From Stream
    //@{
    void SetPosition(NsSize pos);
    NsSize GetPosition() const;
    NsSize GetLength() const;
    NsSize Read(void* buffer, NsSize size);
    //@}

private:
    const void* const mBuffer;
    const NsSize mSize;
    NsSize mOffset;
};

}
}


#endif
