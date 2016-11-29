////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/StringUtils.h>
#include <NsCore/UTF8.h>


#ifdef NS_PLATFORM_WINDOWS
    #include <windows.h>
#else
    #include <fnmatch.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <errno.h>
#endif


namespace Noesis
{
namespace Core
{
////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool FindFirst(const NsChar* directory, const NsChar* pattern, FindData& findData)
{
#ifdef NS_PLATFORM_WINDOWS
    NsChar fullPath[PATH_MAX];
    String::Copy(fullPath, sizeof(fullPath), directory);
    String::Append(fullPath, sizeof(fullPath), "/");
    String::Append(fullPath, sizeof(fullPath), pattern);

    NsUInt16 u16str[PATH_MAX];
    NsSize numChars = UTF8::UTF8To16(fullPath, u16str, PATH_MAX);
    NS_ASSERT(numChars <= PATH_MAX);

    WIN32_FIND_DATAW w32FindData;
    HANDLE h = FindFirstFileExW((LPCWSTR)u16str, FindExInfoBasic, &w32FindData,
        FindExSearchNameMatch, 0, 0);
    if (h != INVALID_HANDLE_VALUE)
    {
        findData.isDirectory = (w32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0;
        numChars = UTF8::UTF16To8((NsUInt16*)w32FindData.cFileName, findData.filename, PATH_MAX);
        NS_ASSERT(numChars <= PATH_MAX);
        String::Copy(findData.pattern, sizeof(pattern), pattern);
        findData.handle = h;
        return true;
    }

    return false;

#else
    DIR* dir = opendir(directory);

    if (dir != 0)
    {
       String::Copy(findData.pattern, sizeof(pattern), pattern);
       findData.handle = dir;

        if (FindNext(findData))
        {
            return true;
        }
        else
        {
            FindClose(findData);
            return false;
        }
    }

    return false;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool FindNext(FindData& findData)
{
#ifdef NS_PLATFORM_WINDOWS
    WIN32_FIND_DATAW w32FindData;
    BOOL res = FindNextFileW(findData.handle, &w32FindData);
    
    if (res)
    {
        findData.isDirectory = (w32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0;
        NsSize n = UTF8::UTF16To8((NsUInt16*)w32FindData.cFileName, findData.filename, PATH_MAX);
        NS_ASSERT(n <= PATH_MAX);
        return true;
    }

    return false;

#else
    DIR* dir = (DIR*)findData.handle;

    while (true)
    {
        dirent* entry = readdir(dir);

        if (entry != 0)
        {
            if (fnmatch(findData.pattern, entry->d_name, FNM_FILE_NAME) == 0)
            {
                findData.isDirectory = (entry->d_type & DT_DIR) > 0;
                String::Copy(findData.filename, sizeof(findData.filename), entry->d_name);
                return true;
            }
        }
        else
        {
            return false;
        }
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void FindClose(FindData& findData)
{
#ifdef NS_PLATFORM_WINDOWS
    BOOL r = ::FindClose(findData.handle);
    NS_ASSERT(r != 0);

#else
    DIR* dir = (DIR*)findData.handle;
    int r = closedir(dir);
    NS_ASSERT(r == 0);
#endif
}


}
}
