////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsVector<T, Allocator>::NsVector() :
    BaseType()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsVector<T, Allocator>::NsVector(const allocator_type& allocator) :
    BaseType(allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsVector<T, Allocator>::NsVector(size_type n, const allocator_type& allocator) :
    BaseType(n, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsVector<T, Allocator>::NsVector(
    size_type n, 
    const value_type& value, 
    const allocator_type& allocator) :
    BaseType(n, value, allocator)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline NsVector<T, Allocator>::NsVector(const ThisType& x) :
    BaseType(x)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
template <typename InputIterator>
inline NsVector<T, Allocator>::NsVector(InputIterator first, InputIterator last) :
    BaseType(first, last)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Allocator>
inline typename NsVector<T, Allocator>::ThisType& NsVector<T, Allocator>::operator=(
    const ThisType& x)
{
    return static_cast<ThisType&>(BaseType::operator=(x));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Visual Studio Debugging
//
// To improve the VS2005 debugging visualization of vector containers, add this to the autoexp.dat 
// file in the [Visualizer] section. Do NOT insert carriage returns or spaces.
//
// ;------------------------------------------------------------------------------
// ; NsVector
// ;------------------------------------------------------------------------------
// NsVector<*,*>|eastl::vector<*,*>{
//     preview 
//     (#(
//         "size=", [$c.mpEnd - $c.mpBegin, u], ", capacity=", [$c.mpCapacity - $c.mpBegin, u], ", free=", [$c.mpCapacity - $c.mpEnd, u]
//     ))
//     children
//     (#(
//         [_raw debug]: [$c,!],
//         #array 
//         (
//             expr: $c.mpBegin[$i],
//             size: $c.mpEnd - $c.mpBegin
//       )
//     ))
// }
////////////////////////////////////////////////////////////////////////////////////////////////////
