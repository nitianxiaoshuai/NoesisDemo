////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_FILE_H__
#define __CORE_FILE_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/NSTLForwards.h>
#include <NsCore/PtrForward.h>
#include <NsCore/UTF8.h>

#include <stdio.h>


NS_CFORWARD(Core, Stream)


namespace Noesis
{
namespace Core
{

/// utf8 aware version of standard fopen
inline FILE* fopen_utf8(const NsChar* filename, const NsChar* mode)
{
#ifdef NS_PLATFORM_WINDOWS
    NsUInt16 filenameU16[PATH_MAX];
    NsSize numChars = UTF8::UTF8To16(filename, filenameU16, PATH_MAX);
    NS_ASSERT(numChars <= PATH_MAX);

    NsUInt16 modeU16[PATH_MAX];
    numChars = UTF8::UTF8To16(mode, modeU16, PATH_MAX);
    NS_ASSERT(numChars <= PATH_MAX);

    FILE* fp = 0;
    _wfopen_s(&fp, (wchar_t*)filenameU16, (wchar_t*)modeU16);
    return fp;
#else
    return fopen(filename, mode);
#endif
}

namespace File
{

/// Normalize a pathname (case is preserved)
NS_CORE_KERNEL_API NsString Normalize(const NsChar* path);

/// Extract the directory part of a pathname
/// A/picture.tga -> A
NS_CORE_KERNEL_API NsString DirName(const NsChar* path);

/// Extract the base portion of a pathname
/// A/picture.tga -> picture.tga
NS_CORE_KERNEL_API NsString BaseName(const NsChar* path);

/// Creates all the directories in the specified path
NS_CORE_KERNEL_API void CreateDirectories(const NsChar* directory);

/// Return a normalized absolutized version of the pathname path
NS_CORE_KERNEL_API NsString AbsPath(const NsChar* path);

/// Return a relative filepath to path from a start directory. This is a path computation: the
/// filesystem is not accessed to confirm the existence or nature of path or start
NS_CORE_KERNEL_API NsString RelPath(const NsChar* path, const NsChar* start);

/// Determines if the given path is a directory
NS_CORE_KERNEL_API NsBool IsDirectory(const NsChar* filename);

/// Determines if the given is an existing regular file
NS_CORE_KERNEL_API NsBool IsFile(const NsChar* filename);

/// ReadWrite directory where temporal archives, like logs, can be saved
NS_CORE_KERNEL_API const NsChar* GetTempStoragePath();

/// Returns a stream from given filename
NS_CORE_KERNEL_API Ptr<Stream> OpenStream(const NsChar* filename);

}
}
}

#endif
