////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_STRINGUTILS_H__
#define __CORE_STRINGUTILS_H__


#include <Noesis.h>

#include <stdarg.h>


namespace Noesis
{
namespace Core
{

enum IgnoreCase
{
    IgnoreCase_False = 0,
    IgnoreCase_True = 1
};

namespace String
{

/// Indicates whether the specified string is null or an empty string
inline NsBool IsNullOrEmpty(const NsChar* str);

/// Returns the length of the C string str
inline NsSize Length(const NsChar* str);

/// Compare two strings
inline int Compare(const NsChar* str1, const NsChar* str2, IgnoreCase ignoreCase =
    IgnoreCase_False);

/// Compare two strings up to n characters
inline int CompareFirst(const NsChar* str1, const NsChar* str2, NsSize n, IgnoreCase ignoreCase =
    IgnoreCase_False);

/// Determines whether the beginning of a string matches the specified string
inline NsBool StartsWith(const NsChar* str, const NsChar* value, IgnoreCase ignoreCase =
    IgnoreCase_False);

/// Determines whether the end of a string matches the specified string
inline NsBool EndsWith(const NsChar* str, const NsChar* value, IgnoreCase ignoreCase =
    IgnoreCase_False);

/// Reports the index of the first occurrence of the specified string
inline int FindFirst(const NsChar* str, const NsChar* value, NsSize offset = 0,
    IgnoreCase ignoreCase = IgnoreCase_False);

/// Reports the index position of the last occurrence of a specified string
inline int FindLast(const NsChar* str, const NsChar* value, NsSize offset = 0,
    IgnoreCase ignoreCase = IgnoreCase_False);

/// Copy characters of one string to another
inline NsChar* Copy(NsChar* dst, NsSize capacity, const NsChar* src, NsSize count = 0xffff);

/// Appends characters of a string
inline NsChar* Append(NsChar* dst, NsSize capacity, const NsChar* src, NsSize count = 0xffff);

/// Replaces all occurrences of a specified characeter
inline NsChar* Replace(NsChar* str, NsChar oldValue, NsChar newValue);

/// Writes formatted data to a string
inline NsChar* FormatBuffer(NsChar* str, NsSize capacity,
    _Printf_format_string_ const NsChar* format, ...) NS_FORMAT_PRINTF(3,4);

/// Writes formatted output using a pointer to a list of arguments
inline NsChar* FormatBufferVA(NsChar* str, NsSize capacity, const NsChar* format, va_list args);

/// Calculates the hash value of a string
inline NsUInt32 Hash(const NsChar* str);

/// Calculates the case-insensitive hash value of a string
inline NsUInt32 CaseHash(const NsChar* str);

}
}
}

/// Inline Include
#include <NsCore/StringUtils.inl>

#endif
