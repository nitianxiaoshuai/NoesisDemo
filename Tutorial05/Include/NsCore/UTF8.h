////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_UTF8_H__
#define __CORE_UTF8_H__


#include <Noesis.h>


namespace Noesis
{
namespace Core
{
namespace UTF8
{

// Appends unicode point to UTF8 encoded string
inline NsChar* Append(NsUInt32 cp, NsChar* text);

/// Returns next unicode point and moves to next position
inline NsUInt32 Next(const NsChar*& text);
inline NsUInt32 Next(NsChar*& text);

/// Decreases the pointer until the beginning of an UTF8 encoded code point and returns it
inline NsUInt32 Prior(const NsChar*& text);
inline NsUInt32 Prior(NsChar*& text);

/// Returns first unicode point of UTF8 encoded string
inline NsUInt32 Get(const NsChar* text);

/// Advances an iterator by the specified number of code points within an UTF-8 sequence
inline void Advance(const NsChar*& text, NsSize n);
inline void Advance(NsChar*& text, NsSize n);

/// Returns the number of code points between two UTF8 pointers
inline NsSize Distance(const NsChar* first, const NsChar* last);

/// Returns the number of characters in an UTF8 encoded string
inline NsSize Length(const NsChar* text);

/// Conversion from UTF8 to UTF16. Returns the numbers of characters needed for the whole text
/// even if they don't fit in the provided buffer.
inline NsSize UTF8To16(const NsChar* utf8, NsUInt16* utf16, NsSize numUTF16Chars);

/// Conversion from UTF16 to UTF8. Returns the numbers of characters needed for the whole text
/// even if they don't fit in the provided buffer.
inline NsSize UTF16To8(const NsUInt16* utf16, NsChar* utf8, NsSize numUTF8Chars);

}
}
}

#include <NsCore/UTF8.inl>

#endif
