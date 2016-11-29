////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_REFLECTIONIMPLEMENTENUM_H__
#define __CORE_REFLECTIONIMPLEMENTENUM_H__


#include <Noesis.h> 
#include <NsCore/CompilerTools.h>
#include <NsCore/TypeEnumCreator.h>
#include <NsCore/TypeEnumImpl.h>
#include <NsCore/ReflectionDeclareEnum.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Shortcuts for defining reflection members
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{


#ifdef _MSC_VER
    // VisualStudio (one more time) does not follow the standard with the .template keyword

    /// Adds metadatas
    #define NsMeta helper.Meta

    /// Defines a value for an enum
    #define NsVal helper.Val
#else
    /// Adds metadatas
    #define NsMeta helper.Meta

    /// Defines a value for an enum
    #define NsVal helper.Val
#endif
//@}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements reflection for an enum.
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_IMPLEMENT_ENUM(enumType) \
    void Noesis::Core::TypeEnumFiller<enumType>::Check()\
    {\
        NS_STATIC_ASSERT(Noesis::Core::IsEnum<enumType>::Result, TYPE_IS_NOT_AN_ENUM);\
    }\
    void Noesis::Core::TypeEnumFiller<enumType>::Fill(\
        Noesis::Core::TypeEnumCreator<enumType>& helper)


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements inline the reflection for an enum.
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_IMPLEMENT_INLINE_ENUM(enumType) \
namespace Noesis \
{\
namespace Core \
{\
template<> struct TypeEnumFiller<enumType>\
{\
    inline static void Check()\
    {\
        NS_STATIC_ASSERT(Noesis::Core::IsEnum<enumType>::Result, TYPE_IS_NOT_AN_ENUM);\
    }\
    inline static void Fill(TypeEnumCreator<enumType>& helper);\
};\
}\
}\
\
inline void Noesis::Core::TypeEnumFiller<enumType>::Fill(\
    Noesis::Core::TypeEnumCreator<enumType>& helper)


#endif
