////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>

#include <string.h>
#include <stdio.h>


namespace Noesis
{
namespace Core
{
namespace String
{

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool IsNullOrEmpty(const NsChar* str)
{
    return str == 0 || *str == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsSize Length(const NsChar* str)
{
    NS_ASSERT(str != 0);
    return static_cast<NsSize>(strlen(str));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int Compare(const NsChar* str1, const NsChar* str2, IgnoreCase ignoreCase)
{
    NS_ASSERT(str1 != 0);
    NS_ASSERT(str2 != 0);

    if (ignoreCase == IgnoreCase_True)
    {
#ifdef NS_PLATFORM_WINDOWS
        return  _stricmp(str1, str2);
#else
        return strcasecmp(str1, str2);
#endif
    }
    else
    {
        return strcmp(str1, str2);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int CompareFirst(const NsChar* str1, const NsChar* str2, NsSize n, IgnoreCase ignoreCase)
{
    NS_ASSERT(str1 != 0);
    NS_ASSERT(str2 != 0);

    if (ignoreCase == IgnoreCase_True)
    {
#ifdef NS_PLATFORM_WINDOWS
        return _strnicmp(str1, str2, n);
#else
        return strncasecmp(str1, str2, n);
#endif
    }
    else
    {
        return strncmp(str1, str2, n);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool StartsWith(const NsChar* str, const NsChar* value, IgnoreCase ignoreCase)
{
    return CompareFirst(str, value, Length(value), ignoreCase) == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool EndsWith(const NsChar* str, const NsChar* value, IgnoreCase ignoreCase)
{
    NS_ASSERT(str != 0);
    NS_ASSERT(value != 0);

    NsSize len = Length(str);
    NsSize valueLen = Length(value);

    if (len >= valueLen)
    {
        return Compare(str + len - valueLen, value, ignoreCase) == 0;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int FindFirst(const NsChar* str, const NsChar* value, NsSize offset, IgnoreCase ignoreCase)
{
    NS_ASSERT(str != 0);
    NS_ASSERT(value != 0);

    NsSize valueLen = Length(value);

    if (valueLen == 0)
    {
        return static_cast<int>(offset);
    }

    NsSize len = Length(str);

    if (offset + valueLen <= len)
    {
        for (NsSize i = offset; i < len; ++i)
        {
            if (CompareFirst(str + i, value, valueLen, ignoreCase) == 0)
            {
                return static_cast<int>(i);
            }
        }
    }

    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int FindLast(const NsChar* str, const NsChar* value, NsSize offset, IgnoreCase ignoreCase)
{
    NS_ASSERT(str != 0);
    NS_ASSERT(value != 0);

    NsSize valueLen = Length(value);

    if (valueLen == 0)
    {
        return static_cast<int>(offset);
    }

    NsSize len = Length(str);

    if (offset + valueLen <= len)
    {
        for (NsSize i = offset + valueLen; i < len; ++i)
        {
            if (CompareFirst(str + len - i, value, valueLen, ignoreCase) == 0)
            {
                return static_cast<int>(len - i);
            }
        }
    }

    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsChar* Copy(NsChar* dst, NsSize capacity, const NsChar* src, NsSize count)
{
    NS_ASSERT(dst != 0);
    NS_ASSERT(src != 0);
    NS_ASSERT(capacity != 0);

    NsSize i = 0;

    while (i < capacity - 1 && i < count && src[i] != 0)
    {
        dst[i] = src[i];
        i++;
    }

    dst[i] = 0;

    return dst;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsChar* Append(NsChar* dst, NsSize capacity, const NsChar* src, NsSize count)
{
    NS_ASSERT(dst != 0);
    NS_ASSERT(src != 0);
    NS_ASSERT(capacity != 0);

    NsSize len = Length(dst);
    NsSize i = 0;

    while (len + i < capacity - 1 && i < count && src[i] != 0)
    {
        dst[len + i] = src[i];
        i++;
    }

    dst[len + i] = 0;

    return dst;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsChar* Replace(NsChar* str, NsChar oldValue, NsChar newValue)
{
    NS_ASSERT(str != 0);

    NsChar* s = str;

    while (*s != 0)
    {
        if (*s == oldValue)
        {
            *s = newValue;
        }

        ++s;
    }

    return str;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsChar* FormatBuffer(NsChar* str, NsSize capacity, _Printf_format_string_ const NsChar* format, ...)
{
    NS_ASSERT(str != 0);
    NS_ASSERT(capacity != 0);
    NS_ASSERT(format != 0);

    va_list vaList;
    va_start(vaList, format);
    NsChar* ret = FormatBufferVA(str, capacity, format, vaList);
    va_end(vaList);

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsChar* FormatBufferVA(NsChar* str, NsSize capacity, const NsChar* format, va_list args)
{
    NS_ASSERT(str != 0);
    NS_ASSERT(capacity != 0);
    NS_ASSERT(format != 0);

#ifdef NS_COMPILER_MSVC
    vsnprintf_s(str, capacity, _TRUNCATE, format, args);
#else
    vsnprintf(str, capacity, format, args);
#endif

    return str;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Hash(const NsChar* str)
{
    NsChar c;
    NsUInt32 result = 2166136261U;

    while ((c = *str++) != 0)
    {
        result = (result * 16777619) ^ c;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 CaseHash(const NsChar* str)
{
    NsChar c;
    NsUInt32 result = 2166136261U;

    while ((c = *str++) != 0)
    {
        result = (result * 16777619) ^ (c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c);
    }

    return result;
}

}
}
}
