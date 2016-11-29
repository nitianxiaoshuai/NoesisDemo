////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_REFLECTIONIMPLEMENT_H__
#define __CORE_REFLECTIONIMPLEMENT_H__


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Shortcuts for defining reflection members
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{

#ifdef _MSC_VER
    // VisualStudio (one more time) does not follow the standard with the .template keyword

    /// Adds metadatas
    #define NsMeta helper.Meta

    /// Indicates that type implements an interface
    #define NsImpl __Rebind__(helper).Impl

    /// Adds properties
    #define NsProp __Rebind__(helper).Prop

    /// Defines a value for an enum
    #define NsVal helper.Val
#else
    /// Adds metadatas
    #define NsMeta helper.Meta

    /// Indicates that type implements an interface
    #define NsImpl __Rebind__(helper).template Impl

    /// Adds properties
    #define NsProp __Rebind__(helper).template Prop

    /// Defines a value for an enum
    #define NsVal helper.Val
#endif
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements reflection for a class outside class definition
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_IMPLEMENT_REFLECTION(classType) \
const Noesis::Core::TypeClass* classType::StaticGetClassType(Noesis::Core::T2T<classType>*)\
{\
    static const Noesis::Core::TypeClass* type;\
\
    if (type == 0)\
    {\
        type = static_cast<const Noesis::Core::TypeClass*>(Noesis::Core::TypeCreate::Create(\
            NS_TYPEID(classType),\
            Noesis::Core::TypeClassCreator::Create<SelfClass>,\
            Noesis::Core::TypeClassCreator::Fill<SelfClass, ParentClass>));\
    }\
\
    return type;\
}\
\
const Noesis::Core::TypeClass* classType::GetClassType() const\
{\
    return StaticGetClassType();\
}\
\
Noesis::Core::BaseObject* classType::GetBaseObject() const\
{\
    return Noesis::Core::ReflectionFunctions::GetBaseObject<SelfClass>(this,\
        Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
            SelfClass, Noesis::Core::BaseObject>::Result>());\
}\
\
NsInt32 classType::AddReference() const\
{\
    return Noesis::Core::ReflectionFunctions::AddReference<SelfClass>(this,\
        Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
            SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
}\
\
NsInt32 classType::Release() const\
{\
    return Noesis::Core::ReflectionFunctions::Release<SelfClass>(this,\
        Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
            SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
}\
\
NsInt32 classType::GetNumReferences() const\
{\
    return Noesis::Core::ReflectionFunctions::GetNumReferences<SelfClass>(this,\
        Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
            SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
}\
\
struct classType::__Rebind__ \
{ \
    __Rebind__(Noesis::Core::TypeClassCreator& _helper): helper(_helper) {} \
\
    template<class _InterfaceType> \
    void Impl() \
    { \
        helper.Impl<classType, _InterfaceType>(); \
    } \
\
    template<class _PropertyType> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        _PropertyType classType::* prop) \
    { \
        return helper.Prop<classType, _PropertyType>(name, prop); \
    } \
\
    template<class _PropertyType, NsSize _ArraySize> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        _PropertyType (classType::* prop)[_ArraySize]) \
    { \
        return helper.Prop<classType, _PropertyType, _ArraySize>(name, prop); \
    } \
\
    template<class _PropertyType, NsSize _ArraySize> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        _PropertyType (classType::* prop)[_ArraySize], NsSize index) \
    { \
        return helper.Prop<classType, _PropertyType, _ArraySize>(name, prop, index); \
    } \
\
    template<class GetterT, class SetterT> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        GetterT getter, SetterT setter) \
    { \
        return helper.Prop(name, getter, setter); \
    } \
\
    template<class _PropertyType> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        _PropertyType (classType::*getter)() const) \
    { \
        return helper.Prop(name, getter); \
    } \
\
private: \
    __Rebind__(const __Rebind__&); \
    __Rebind__& operator=(const __Rebind__&); \
\
    Noesis::Core::TypeClassCreator& helper; \
}; \
\
template <class _DummyType> \
void classType::StaticFillClassType(Noesis::Core::TypeClassCreator& helper)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements reflection for a templated class with one template param outside class definition
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_IMPLEMENT_REFLECTION_T1(classType) \
template<class T1>\
const Noesis::Core::TypeClass* classType<T1>::StaticGetClassType(Noesis::Core::T2T<classType>*)\
{\
    static const Noesis::Core::TypeClass* type;\
\
    if (type == 0)\
    {\
        type = static_cast<const Noesis::Core::TypeClass*>(Noesis::Core::TypeCreate::Create(\
            NS_TYPEID(classType<T1>),\
            Noesis::Core::TypeClassCreator::Create<SelfClass>,\
            Noesis::Core::TypeClassCreator::Fill<SelfClass, ParentClass>));\
    }\
\
    return type;\
}\
\
template<class T1>\
const Noesis::Core::TypeClass* classType<T1>::GetClassType() const\
{\
    return StaticGetClassType();\
}\
\
template<class T1>\
Noesis::Core::BaseObject* classType<T1>::GetBaseObject() const\
{\
    return Noesis::Core::ReflectionFunctions::GetBaseObject<SelfClass>(this,\
        Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
            SelfClass, Noesis::Core::BaseObject>::Result>());\
}\
\
template<class T1>\
NsInt32 classType<T1>::AddReference() const\
{\
    return Noesis::Core::ReflectionFunctions::AddReference<SelfClass>(this,\
        Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
            SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
}\
\
template<class T1>\
NsInt32 classType<T1>::Release() const\
{\
    return Noesis::Core::ReflectionFunctions::Release<SelfClass>(this,\
        Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
            SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
}\
\
template<class T1>\
NsInt32 classType<T1>::GetNumReferences() const\
{\
    return Noesis::Core::ReflectionFunctions::GetNumReferences<SelfClass>(this,\
        Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
            SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
}\
\
template<class T1>\
struct classType<T1>::__Rebind__ \
{ \
    __Rebind__(Noesis::Core::TypeClassCreator& _helper): helper(_helper) {} \
\
    template<class _InterfaceType> \
    void Impl() \
    { \
        helper.Impl<classType<T1>, _InterfaceType>(); \
    } \
\
    template<class _PropertyType> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        _PropertyType classType<T1>::* prop) \
    { \
        return helper.Prop<classType<T1>, _PropertyType>(name, prop); \
    } \
\
    template<class _PropertyType, NsInt _ArraySize> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        _PropertyType (classType<T1>::* prop)[_ArraySize]) \
    { \
        return helper.Prop<classType<T1>, _PropertyType, _ArraySize>(name, prop); \
    } \
\
    template<class _PropertyType, NsInt _ArraySize> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        _PropertyType (classType<T1>::* prop)[_ArraySize], NsSize index) \
    { \
        return helper.Prop<classType<T1>, _PropertyType, _ArraySize>(name, prop, index); \
    } \
\
    template<class GetterT, class SetterT> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        GetterT getter, SetterT setter) \
    { \
        return helper.Prop(name, getter, setter); \
    } \
\
    template<class _PropertyType> \
    Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
        _PropertyType (classType<T1>::*getter)() const) \
    { \
        return helper.Prop(name, getter); \
    } \
\
private: \
    __Rebind__(const __Rebind__&); \
    __Rebind__& operator=(const __Rebind__&); \
\
    Noesis::Core::TypeClassCreator& helper; \
}; \
\
template<class T1>\
template <class _DummyType> \
void classType<T1>::StaticFillClassType(Noesis::Core::TypeClassCreator& helper)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements reflection for a class inside class definition (templates must use this one)
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_IMPLEMENT_INLINE_REFLECTION(classType, parentType) \
public:\
    static const Noesis::Core::TypeClass* StaticGetClassType(Noesis::Core::T2T<classType>* = 0)\
    {\
        static const Noesis::Core::TypeClass* type;\
\
        if (type == 0)\
        {\
            type = static_cast<const Noesis::Core::TypeClass*>(Noesis::Core::TypeCreate::Create(\
                NS_TYPEID(classType),\
                Noesis::Core::TypeClassCreator::Create<SelfClass>,\
                Noesis::Core::TypeClassCreator::Fill<SelfClass, ParentClass>));\
        }\
\
        return type;\
    }\
\
    const Noesis::Core::TypeClass* GetClassType() const\
    {\
        return StaticGetClassType();\
    }\
\
    Noesis::Core::BaseObject* GetBaseObject() const\
    {\
        return Noesis::Core::ReflectionFunctions::GetBaseObject<SelfClass>(this,\
            Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
                SelfClass, Noesis::Core::BaseObject>::Result>());\
    }\
\
    NsInt32 AddReference() const\
    {\
        return Noesis::Core::ReflectionFunctions::AddReference<SelfClass>(this,\
            Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
                SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
    }\
\
    NsInt32 Release() const\
    {\
        return Noesis::Core::ReflectionFunctions::Release<SelfClass>(this,\
            Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
                SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
    }\
\
    NsInt32 GetNumReferences() const\
    {\
        return Noesis::Core::ReflectionFunctions::GetNumReferences<SelfClass>(this,\
            Noesis::Core::Int2Type<Noesis::Core::IsDerived<\
                SelfClass, Noesis::Core::BaseRefCounted>::Result>());\
    }\
\
private:\
    typedef classType SelfClass;\
    typedef parentType ParentClass;\
\
    friend class Noesis::Core::TypeClassCreator;\
    friend struct Noesis::Core::ReflectionFunctions;\
\
    struct __Rebind__ \
    { \
        __Rebind__(Noesis::Core::TypeClassCreator& _helper): helper(_helper) {} \
\
        template<class _InterfaceType> \
        void Impl() \
        { \
            helper.Impl<classType, _InterfaceType>(); \
        } \
\
        template<class _PropertyType> \
        Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
            _PropertyType classType::* prop) \
        { \
            return helper.Prop<classType, _PropertyType>(name, prop); \
        } \
\
        template<class _PropertyType, NsInt _ArraySize> \
        Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
            _PropertyType (classType::* prop)[_ArraySize]) \
        { \
            return helper.Prop<classType, _PropertyType, _ArraySize>(name, prop); \
        } \
\
        template<class _PropertyType, NsInt _ArraySize> \
        Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
            _PropertyType (classType::* prop)[_ArraySize], NsSize index) \
        { \
            return helper.Prop<classType, _PropertyType, _ArraySize>(name, prop, index); \
        } \
\
        template<class GetterT, class SetterT> \
        Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
            GetterT getter, SetterT setter) \
        { \
            return helper.Prop(name, getter, setter); \
        } \
\
        template<class _PropertyType> \
        Noesis::Core::TypeClassCreator::TypePropertyCreator Prop(const NsChar* name, \
            _PropertyType (classType::*getter)() const) \
        { \
            return helper.Prop(name, getter); \
        } \
\
    private: \
        __Rebind__(const __Rebind__&); \
        __Rebind__& operator=(const __Rebind__&); \
\
        Noesis::Core::TypeClassCreator& helper; \
    }; \
\
    template <class _PropertyType> \
    static void StaticFillClassType(Noesis::Core::TypeClassCreator& helper)


////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Noesis
{
namespace Core
{
class BaseObject;
class BaseRefCounted;
}
}

#include <Noesis.h> 
#include <NsCore/ReflectionFunctions.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/TypeCreate.h>
#include <NsCore/TypeClassCreator.h>
#include <NsCore/TypeOf.h>

#endif
