////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>


namespace Noesis
{
namespace Core
{
namespace UTF8
{

////////////////////////////////////////////////////////////////////////////////////////////////////
NsChar* Append(NsUInt32 cp, NsChar* text)
{
    NS_ASSERT(text != 0);

    if (cp < 0x80)
    {
        // one octet
        *(text++) = static_cast<NsChar>(cp);
    }
    else if (cp < 0x800)
    {
        // two octets
        *(text++) = static_cast<NsChar>((cp >> 6) | 0xc0);
        *(text++) = static_cast<NsChar>((cp & 0x3f) | 0x80);
    }
    else if (cp < 0x10000)
    {
        // three octets
        *(text++) = static_cast<NsChar>((cp >> 12) | 0xe0);
        *(text++) = static_cast<NsChar>(((cp >> 6) & 0x3f) | 0x80);
        *(text++) = static_cast<NsChar>((cp & 0x3f) | 0x80);
    }
    else 
    {
        // four octets
        *(text++) = static_cast<NsChar>((cp >> 18) | 0xf0);
        *(text++) = static_cast<NsChar>(((cp >> 12) & 0x3f) | 0x80);
        *(text++) = static_cast<NsChar>(((cp >> 6) & 0x3f) | 0x80);
        *(text++) = static_cast<NsChar>((cp & 0x3f) | 0x80);
    }
    
    return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsUInt8 Mask8(NsChar c)
{
    return static_cast<NsUInt8>(0xff & c);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsUInt16 Mask16(NsUInt16 c)
{
    return static_cast<NsUInt16>(0xffff & c);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsSize SequenceLength(const NsChar* text)
{
    NS_ASSERT(text != 0);
    NsUInt8 lead = Mask8(*text);

    if (lead < 0x80)
    {
        return 1;
    }
    else if ((lead >> 5) == 0x6)
    {
        return 2;
    }
    else if ((lead >> 4) == 0xe)
    {
        return 3;
    }
    else if ((lead >> 3) == 0x1e)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Next(const NsChar*& text)
{
    NS_ASSERT(text != 0);
    NsUInt32 cp = Mask8(*text);

    switch (SequenceLength(text)) 
    {
        case 1:
        {
            break;
        }
        case 2:
        {
            ++text;
            cp = ((cp << 6) & 0x7ff) + ((*text) & 0x3f);
            break;
        }
        case 3:
        {
            ++text; 
            cp = ((cp << 12) & 0xffff) + ((Mask8(*text) << 6) & 0xfff);
            ++text;
            cp += (*text) & 0x3f;
            break;
        }
        case 4:
        {
            ++text;
            cp = ((cp << 18) & 0x1fffff) + ((Mask8(*text) << 12) & 0x3ffff);
            ++text;
            cp += (Mask8(*text) << 6) & 0xfff;
            ++text;
            cp += (*text) & 0x3f; 
            break;
        }
        default:
            NS_ASSERT_UNREACHABLE;
    }

    ++text;
    return cp; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Next(NsChar*& text)
{
    NS_ASSERT(text != 0);
    const NsChar* text_ = text;
    NsUInt32 cp = Next(text_);
    text = const_cast<NsChar*>(text_);
    return cp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Prior(const NsChar*& text)
{
    NS_ASSERT(text != 0);
    while ((Mask8(*(--text)) >> 6) == 0x2) {}
    return Get(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Prior(NsChar*& text)
{
    NS_ASSERT(text != 0);
    const NsChar* text_ = text;
    NsUInt32 cp = Prior(text_);
    text = const_cast<NsChar*>(text_);
    return cp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Get(const NsChar* text)
{
    NS_ASSERT(text != 0);
    return Next(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Advance(const NsChar*& text, NsSize n)
{
    NS_ASSERT(text != 0);
    for (NsSize i = 0; i < n; i++)
    {
        Next(text);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Advance(NsChar*& text, NsSize n)
{
    NS_ASSERT(text != 0);
    const NsChar* text_ = text;
    Advance(text_, n);
    text = const_cast<NsChar*>(text_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsSize Distance(const NsChar* first, const NsChar* last)
{
    NS_ASSERT(first != 0);
    NS_ASSERT(last != 0);

    NsSize len = 0;

    while (first != last)
    {
        first += SequenceLength(first);
        len++;
    }

    return len;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsSize Length(const NsChar* text)
{
    NS_ASSERT(text != 0);

    NsSize len = 0;

    while (*text != 0)
    {
        text += SequenceLength(text);
        len++;
    }

    return len;
}

#define LEAD_SURROGATE_MIN 0xd800u
#define LEAD_SURROGATE_MAX 0xdbffu
#define TRAIL_SURROGATE_MIN 0xdc00u
#define TRAIL_SURROGATE_MAX 0xdfffu
#define LEAD_OFFSET (LEAD_SURROGATE_MIN - (0x10000 >> 10))
#define SURROGATE_OFFSET (0x10000u - (LEAD_SURROGATE_MIN << 10) - TRAIL_SURROGATE_MIN)

////////////////////////////////////////////////////////////////////////////////////////////////////
NsSize UTF8To16(const NsChar* utf8, NsUInt16* utf16, NsSize numUTF16Chars)
{
    NS_ASSERT(utf8 != 0);
    NsSize totalChars = 0;
    NsSize writtenChars = 0;

    for (;;)
    {
        NsUInt32 c = UTF8::Next(utf8);

        if (c <= 0xffff)
        {
            if (totalChars + 1 < numUTF16Chars)
            {
                utf16[totalChars] = static_cast<NsUInt16>(c);
                writtenChars++;
            }

            totalChars++;
        }
        else
        {
            if (totalChars + 2 < numUTF16Chars)
            {
                utf16[totalChars] = static_cast<NsUInt16>((c >> 10) + LEAD_OFFSET);
                utf16[totalChars + 1] = static_cast<NsUInt16>((c & 0x3ff) + TRAIL_SURROGATE_MIN);
                writtenChars += 2;
            }

            totalChars += 2;
        }

        if (c == 0)
        {
            if (writtenChars < numUTF16Chars)
            {
                utf16[writtenChars] = 0;
            }

            return totalChars;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsSize UTF16To8(const NsUInt16* utf16, NsChar* utf8, NsSize numUTF8Chars)
{
    NS_ASSERT(utf16 != 0);
    NsSize totalChars = 0;
    NsSize writtenChars = 0;

    for (;;)
    {
        NsUInt32 c = Mask16(*utf16++);
        NsBool isLeadSurrogate = c >= LEAD_SURROGATE_MIN && c <= LEAD_SURROGATE_MAX;

        if (isLeadSurrogate)
        {
            NsUInt32 trail = Mask16(*utf16++);
            c = (c << 10) + trail + SURROGATE_OFFSET;
        }

        NsSize numOctets = c < 0x80 ? 1 : c < 0x800 ? 2 : c < 0x10000 ? 3 : 4;

        if (totalChars + numOctets + 1 <= numUTF8Chars)
        {
            utf8 = UTF8::Append(c, utf8);
            writtenChars += numOctets;
        }

        totalChars += numOctets;

        if (c == 0)
        {
            if (writtenChars < numUTF8Chars)
            {
                *utf8 = 0;
            }

            return totalChars;
        }
    }
}

#undef LEAD_SURROGATE_MIN
#undef LEAD_SURROGATE_MAX
#undef TRAIL_SURROGATE_MIN
#undef TRAIL_SURROGATE_MAX
#undef LEAD_OFFSET
#undef SURROGATE_OFFSET

}
}
}
