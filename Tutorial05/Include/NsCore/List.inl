////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsList<T, Allocator>::NsList() :
    BaseType()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsList<T, Allocator>::NsList(const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsList<T, Allocator>::NsList(size_type n, const allocator_type& allocator) :
    BaseType(n, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsList<T, Allocator>::NsList(
    size_type n, 
    const value_type& value, 
    const allocator_type& allocator) :
    BaseType(n, value, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsList<T, Allocator>::NsList(const ThisType& x) :    
    BaseType(x)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
template <typename InputIterator>
inline NsList<T, Allocator>::NsList(InputIterator first, InputIterator last) :
    BaseType(first, last)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline typename NsList<T, Allocator>::ThisType& NsList<T, Allocator>::operator=(const ThisType& x)
{
    return static_cast<ThisType&>(BaseType::operator=(x));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Visual Studio Debugging
//
// To improve the VS2005 debugging visualization of list containers, add this to the autoexp.dat 
// file in the [Visualizer] section. Do NOT insert carriage returns or spaces.
//
// ;------------------------------------------------------------------------------
// ; NsList
// ;------------------------------------------------------------------------------
// NsList<*,*>|eastl::list<*,*>{
//     children
//     (#(
//         [_raw debug]: [$c,!],
//         #list 
//         (
//             head: $c.mNode,
//             next: mpNext
//         ) : (eastl::ListNode<$T1 > *) &$e
//     ))
// }
////////////////////////////////////////////////////////////////////////////////////////////////////
