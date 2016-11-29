////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_FIND_H__
#define __CORE_FIND_H__


#include <Noesis.h>


namespace Noesis
{
namespace Core
{

struct FindData
{
    NsBool isDirectory;
    NsChar filename[PATH_MAX];
    NsChar pattern[PATH_MAX];
    void* handle;
};

/// Searches a directory for a file or subdirectory that matches a specific pattern
/// Returns False if no files are found.
inline NsBool FindFirst(const NsChar* directory, const NsChar* pattern, FindData& findData);

/// Continues a file search from a previous call to the FindFirst function
inline NsBool FindNext(FindData& findData);

/// Closes a file search handle opened by the FindFirst function
inline void FindClose(FindData& findData);

}
}


#include "Find.inl"

#endif


