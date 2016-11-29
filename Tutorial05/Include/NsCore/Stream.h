////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_STREAM_H__
#define __CORE_STREAM_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a read-only generic view of a sequence of bytes
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API Stream: public BaseComponent
{
public:
    /// Set the current position within the stream
    virtual void SetPosition(NsSize pos) = 0;

    /// Returns the current position within the stream
    virtual NsSize GetPosition() const = 0;

    /// Returns the length of the stream in bytes
    virtual NsSize GetLength() const = 0;

    /// Reads data at the current position and advances it by the number of bytes read
    /// Returns the total number of bytes read. This can be less than the number of bytes requested
    virtual NsSize Read(void* buffer, NsSize size) = 0;
};

}
}


#endif
