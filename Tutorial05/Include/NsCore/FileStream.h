////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_FILESTREAM_H__
#define __CORE_FILESTREAM_H__


#include <Noesis.h>
#include <NsCore/Stream.h>

#include <stdio.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Stream implementation using a FILE* handle
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API FileStream: public Stream
{
public:
    FileStream(FILE* fp);
    ~FileStream();

    /// From Stream
    //@{
    void SetPosition(NsSize pos);
    NsSize GetPosition() const;
    NsSize GetLength() const;
    NsSize Read(void* buffer, NsSize size);
    //@}

private:
    FILE* mHandle;
};

}
}


#endif