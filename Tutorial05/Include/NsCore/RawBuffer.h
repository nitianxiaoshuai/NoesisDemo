////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #802]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_RAWBUFFER_H__
#define __CORE_RAWBUFFER_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A buffer for storing raw data. Similar to NsVector<NsByte> but without invoking constructors
/// Internal memory buffer never decreases its size automatically. Trim() must be invoked
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API RawBuffer
{
public:
    /// Creates an empty RawBuffer
    RawBuffer();

    /// Creates an initial buffer with sizeInBytes size
    RawBuffer(NsSize sizeInBytes);

    /// Copy constructor
    RawBuffer(const RawBuffer& rawBuffer);

    /// Destructor
    ~RawBuffer();

    /// Copy operator
    RawBuffer& operator=(const RawBuffer& rawBuffer);
    
    /// Comparison operator. Firstly the size is compared and if the size is the same the content
    /// is compared lexicographically
    NsBool operator<(const RawBuffer& rawBuffer) const;

    /// Returns the size of the internally allocated buffer
    inline NsSize GetCapacity() const;

    /// Returns The size of the buffer returned by GetData()
    inline NsSize GetSize() const;
    
    /// Returns wether the buffer is empty
    inline NsBool IsEmpty() const;

    /// Buffer accessors
    //@{
    inline const void* GetData() const;
    inline void* GetData();
    //@}

    /// Changes the size to a new one. The internal memory is never decreased, only increased.
    /// Previous memory content is always preserved (at least to the size that fits in the new
    /// buffer)
    void Resize(NsSize newSizeInBytes);

    /// Erases all of the elements. The internal memory is never decreased.
    void Clear();

    /// Increases the internal capacity of the reserved memory to sizeInBytes. The size
    /// returned by GetSize() function is not changed
    void Reserve(NsSize sizeInBytes);

    /// Adjust the internal buffer to have the exact requested size (force capacity == size). The
    /// spare memory is freed.
    void Trim();

    /// Append a block
    void Append(const void* data, NsSize sizeInBytes);

private:
    NsSize mCapacity;
    NsSize mSize;
    void* mData;
};

}
}

#include <NsCore/RawBuffer.inl>


#endif