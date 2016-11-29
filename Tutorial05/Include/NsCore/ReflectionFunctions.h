////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_REFLECTIONFUNCTIONS_H__
#define __CORE_REFLECTIONFUNCTIONS_H__


#include <NsCore/Types.h>
#include <NsCore/CompilerTools.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
class BaseObject;
//@}

struct ReflectionFunctions
{
    template<class T> static inline BaseObject* GetBaseObject(const T*, Int2Type<0>);
    template<class T> static inline BaseObject* GetBaseObject(const T*, Int2Type<1>);

    template<class T> static inline NsInt32 AddReference(const T*, Int2Type<0>);
    template<class T> static inline NsInt32 AddReference(const T*, Int2Type<1>);

    template<class T> static inline NsInt32 Release(const T*, Int2Type<0>);
    template<class T> static inline NsInt32 Release(const T*, Int2Type<1>);

    template<class T> static inline NsInt32 GetNumReferences(const T*, Int2Type<0>);
    template<class T> static inline NsInt32 GetNumReferences(const T*, Int2Type<1>);
};

}
}

/// Inline include
#include <NsCore/ReflectionFunctions.inl>


#endif
