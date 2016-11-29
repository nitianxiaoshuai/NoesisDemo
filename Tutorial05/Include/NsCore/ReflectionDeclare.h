////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_REFLECTIONDECLARE_H__
#define __CORE_REFLECTIONDECLARE_H__


#include <NsCore/Types.h>


/// Forward declarations
//@{
namespace Noesis
{
namespace Core
{
class TypeClass;
class BaseObject;
struct ReflectionFunctions;
class TypeClassCreator;
}
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// This type should be used as a null type when a class has no parent.
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Noesis
{
namespace Core
{
typedef NullType NoParent;
template<class T> struct T2T;
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Declares reflection for a class (interface, component or simple class/struct)
/// Note: StaticFillClassType is templatized but always instanced with the type void. This way
/// we can use always the .template keyword in gcc when T is indistinctly dependent or not
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_DECLARE_REFLECTION(classType, parentType) \
public:\
    static const Noesis::Core::TypeClass* StaticGetClassType(Noesis::Core::T2T<classType>* = 0);\
    const Noesis::Core::TypeClass* GetClassType() const;\
    Noesis::Core::BaseObject* GetBaseObject() const;\
\
    NsInt32 AddReference() const;\
    NsInt32 Release() const;\
    NsInt32 GetNumReferences() const;\
\
private:\
    typedef classType SelfClass;\
    typedef parentType ParentClass;\
\
    friend class Noesis::Core::TypeClassCreator;\
    friend struct Noesis::Core::ReflectionFunctions;\
    struct __Rebind__;\
\
    template<class _T> \
    static void StaticFillClassType(Noesis::Core::TypeClassCreator& helper);


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Declares static reflection functions for a class
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_DECLARE_STATIC_REFLECTION(classType, parentType) \
public:\
    static const Noesis::Core::TypeClass* StaticGetClassType(Noesis::Core::T2T<classType>* = 0);\
\
private:\
    typedef classType SelfClass;\
    typedef parentType ParentClass;

#endif
