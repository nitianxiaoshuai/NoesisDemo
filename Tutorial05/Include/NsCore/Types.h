////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPES_H__
#define __CORE_TYPES_H__


#if defined(_MSC_VER) && _MSC_VER < 1600
#include <crtdefs.h>
#else
#include <stdint.h>
#include <cstddef>
#endif


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Fundamental types definition
////////////////////////////////////////////////////////////////////////////////////////////////////

/// Byte
typedef unsigned char Byte;

/// Signed integers
//@{
typedef signed char Int8;
typedef signed short Int16;
typedef signed int Int32;
typedef signed long long Int64;
//@}

/// Unsigned integers
//@{
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef unsigned long long UInt64;
//@}

/// Default integers (optimized for the platform)
//@{
typedef signed int Int;
typedef unsigned int UInt;
//@}


/// This type must be used when applied to anything that represents a size in bytes or an index
/// UInt32 is used instead of size_t to avoid wasting memory
typedef UInt32 Size;

/// This type must be used when applied to pointers that are treated as integers
//@{
typedef intptr_t IntPtr;
typedef uintptr_t UIntPtr;
typedef ptrdiff_t PtrDiff;
//@}

/// Floats
//@{
typedef float Float32;
typedef double Float64;
//@}

/// Characters and strings
//@{
typedef char Char;
//@}

/// Booleans
typedef bool Bool;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used as a placeholder for "no type here".
////////////////////////////////////////////////////////////////////////////////////////////////////
class NullType {};

}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Fundamental types definition
////////////////////////////////////////////////////////////////////////////////////////////////////

/// Byte
typedef Noesis::Core::Byte NsByte;

/// Signed integers
//@{
typedef Noesis::Core::Int8 NsInt8;
typedef Noesis::Core::Int16 NsInt16;
typedef Noesis::Core::Int32 NsInt32;
typedef Noesis::Core::Int64 NsInt64;
//@}

/// Unsigned integers
//@{
typedef Noesis::Core::UInt8 NsUInt8;
typedef Noesis::Core::UInt16 NsUInt16;
typedef Noesis::Core::UInt32 NsUInt32;
typedef Noesis::Core::UInt64 NsUInt64;
//@}

/// Default integers (optimized for the platform)
//@{
typedef Noesis::Core::Int NsInt;
typedef Noesis::Core::UInt NsUInt;
//@}

/// This type must be used when applied to anything that represents a size in bytes or an index
typedef Noesis::Core::Size NsSize;

/// This type must be used when applied to pointers that are treated as integers
//@{
typedef Noesis::Core::IntPtr NsIntPtr;
typedef Noesis::Core::UIntPtr NsUIntPtr;
typedef Noesis::Core::PtrDiff NsPtrDiff;
//@}

/// Floats
//@{
typedef Noesis::Core::Float32 NsFloat32;
typedef Noesis::Core::Float64 NsFloat64;
//@}

/// Characters and strings
//@{
typedef Noesis::Core::Char NsChar;
//@}

/// Booleans
typedef Noesis::Core::Bool NsBool;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used as a placeholder for "no type here".
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::NullType NsNullType;


#endif
