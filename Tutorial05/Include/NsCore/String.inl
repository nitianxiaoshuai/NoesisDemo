////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString() :
    BaseType()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(
    const ThisType& x, 
    size_type position, 
    size_type n) :
    BaseType(x, position, n)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(
    const ParentType& x, 
    size_type position, 
    size_type n) :
    BaseType(x, position, n)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(
    const value_type* p, 
    size_type n, 
    const allocator_type& allocator) :
    BaseType(p, n, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(
    const value_type* p, 
    const allocator_type& allocator) :
    BaseType(p, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(
    size_type n, 
    value_type c, 
    const allocator_type& allocator) :
    BaseType(n, c, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(const ThisType& x) :
    BaseType(x)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(const ParentType& x) :
    BaseType(x)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(
    const value_type* pBegin, 
    const value_type* pEnd, 
    const allocator_type& allocator) :
    BaseType(pBegin, pEnd, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsBasicString<T, Allocator>::NsBasicString(CtorDoNotInitialize,  size_type n, 
    const allocator_type& allocator): BaseType(CtorDoNotInitialize(), n, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
NsBasicString<T, Allocator>::NsBasicString(CtorSprintf, _Printf_format_string_
    const NsChar* pFormat, ...): BaseType(CtorDoNotInitialize(),
    size_type(eastl::CharStrlen(pFormat) + 1))
{
    va_list arguments;
    va_start(arguments, pFormat);
    this->append_sprintf_va_list(pFormat, arguments);
    va_end(arguments);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline typename NsBasicString<T, Allocator>::ThisType NsBasicString<T, Allocator>::Format(
    _Printf_format_string_ const NsChar* pFormat, ...)
{
    ThisType ret(CtorDoNotInitialize(), size_type(eastl::CharStrlen(pFormat) + 1));

    va_list arguments;
    va_start(arguments, pFormat);
    ret.append_sprintf_va_list(pFormat, arguments);
    va_end(arguments);

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline typename NsBasicString<T, Allocator>::ThisType& NsBasicString<T, Allocator>::operator=(
    const ThisType& x)
{
    return static_cast<ThisType&>(BaseType::operator=(x));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline typename NsBasicString<T, Allocator>::ThisType& NsBasicString<T, Allocator>::operator=(
    const value_type* p)
{
    return static_cast<ThisType&>(BaseType::operator=(p));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline typename NsBasicString<T, Allocator>::ThisType& NsBasicString<T, Allocator>::operator=(
    value_type c)
{
    return static_cast<ThisType&>(BaseType::operator=(c));
}
