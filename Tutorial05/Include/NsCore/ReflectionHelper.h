////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1316]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_REFLECTIONHELPER_H__
#define __CORE_REFLECTIONHELPER_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/Symbol.h>
#include <NsCore/Ptr.h>
#include <NsCore/CompilerTools.h>


namespace Noesis
{
namespace Core
{

// Forward declarations
//@{
class Type;
class TypeClass;
class TypeMetaData;
class TypeProperty;
class FunctionInvoker;
class BaseComponent;
class MetaData;
//@}

namespace Reflection
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a metadata of a specific type class
////////////////////////////////////////////////////////////////////////////////////////////////////
struct TypeClassMetaData
{
    const TypeClass* typeClass;
    const TypeMetaData* metaData;

    inline TypeClassMetaData(const TypeClass* tc, const TypeMetaData* m);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a property of a specific type class
////////////////////////////////////////////////////////////////////////////////////////////////////
struct TypeClassProperty
{
    const TypeClass* typeClass;
    const TypeProperty* property;

    inline TypeClassProperty(const TypeClass* tc, const TypeProperty* p);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Wraps a reflection property value. It can be used to get property name, type, metadata and
/// value (via its getter/setter functions)
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API Property
{
public:
    /// Default constructor
    Property();

    /// Constructor traverses property path until final property is reached. If the property is not
    /// found an error is raised
    //@{
    static Property Get(const Ptr<BaseComponent>& object, const NsChar* path = "");
    static Property Get(const TypeClass* typeClass, const void* instance, 
        const NsChar* path = "");
    //@}

    /// Constructor traverses property path until final property is reached. If the property is not
    /// found the function returns false.
    //@{
    static NsBool Find(const Ptr<BaseComponent>& object, const NsChar* path, Property& prop);
    static NsBool Find(const TypeClass* typeClass, const void* instance, const NsChar* path,
        Property& prop);
    //@}

    /// Indicates whether property value is null
    NsBool IsNull() const;

    /// Gets property name
    NsSymbol GetName() const;

    /// Gets property type
    const Type* GetType() const;

    /// Dereferences pointers and Ptr types
    const Type* DerefType() const;

    /// Gets or sets property value
    //@{
    template<class T>
    typename Param<T>::Type Get() const;

    template<class T>
    void Set(typename Param<T>::Type value) const;
    //@}

private:
    class TypeClassPropertyIterator;
    class TypeCollectionPropertyIterator;
    class NullPropertyIterator;

    Property(const Type* type, const TypeProperty* typeProperty, const void* instance,
        NsSymbol name);

    NsBool Init(const TypeClass* typeClass, const void* instance, const NsChar* path, 
        NsBool raiseError);

private:
    const Type* mType;
    const TypeProperty* mTypeProperty;
    const void* mInstance;
    NsSymbol mName;
};

/// Get first metadata found in the passed class hierarchy that matches the metadata type
/// \param typeClass The type of the class to start looking for the metadata
/// \param metadata The type of metadata to look for
/// \return If found, returns the pointer to metadata and the class where the metadata was found
NS_CORE_KERNEL_API TypeClassMetaData FindMetaData(const TypeClass* typeClass,
    const TypeClass* metadata);

/// Get first property found in the passed class hierarchy that match the property name
/// \param typeClass The type of the class to start looking for
/// \param propId The property to look for
/// \return  If found, returns the typeProperty and the typeClass where the property was found
NS_CORE_KERNEL_API TypeClassProperty FindProperty(const TypeClass* typeClass, NsSymbol propId);

}
}
}

#include <NsCore/ReflectionHelper.inl>


#endif
