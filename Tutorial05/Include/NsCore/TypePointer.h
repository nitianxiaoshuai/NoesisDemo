////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #866]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEPOINTER_H__
#define __CORE_TYPEPOINTER_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/Type.h>
#include <NsCore/TypeCollection.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Core
{

// Forward declarations
//@{
class TypeInfo;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeReference. Types for references.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypeReference: public Type
{
public:
    /// Constructor
    TypeReference(const TypeInfo& typeInfo);

    /// Sets reflection static type of reference content
    void SetContentType(const Type* contentType);

    /// Gets reflection type of runtime reference content
    /// \return Runtime reference content's reflection info
    inline const Type* GetContentType() const;

protected:
    const Type* mContentType;

    NS_DECLARE_REFLECTION(TypeReference, Type)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeConst. Types for const objects.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypeConst: public Type
{
public:
    /// Constructor
    TypeConst(const TypeInfo& typeInfo);

    /// Sets reflection static type of const content
    void SetContentType(const Type* contentType);

    /// Gets reflection type of runtime const content
    /// \return Runtime const content's reflection info
    inline const Type* GetContentType() const;

protected:
    const Type* mContentType;

    NS_DECLARE_REFLECTION(TypeConst, Type)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypePointer. Types for pointers.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypePointer: public Type
{
public:
    /// Constructor
    TypePointer(const TypeInfo& typeInfo);

    /// Sets reflection static type of pointer content
    void SetStaticContentType(const Type* contentType);

    /// Gets reflection type of pointer content static type
    /// \return Pointer content type's reflection info
    inline const Type* GetStaticContentType() const;

    /// Gets reflection type of runtime pointer content
    /// \param ptr Address of the pointer object
    /// \return Runtime pointer content's reflection info
    const Type* GetContentType(void* ptr) const;

    /// Gets the address of pointer content
    /// \return Pointer content's address
    void* GetContent(void* ptr) const;

protected:
    const Type* mContentType;

    NS_DECLARE_REFLECTION(TypePointer, Type)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypePtr. Types for Ptr objects.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypePtr: public Type
{
public:
    /// Constructor
    TypePtr(const TypeInfo& typeInfo);

    /// Sets reflection static type of Ptr content
    void SetStaticContentType(const Type* contentType);

    /// Gets reflection type of Ptr content static type
    /// \return Ptr content type's reflection info
    inline const Type* GetStaticContentType() const;

    /// Gets reflection type of runtime Ptr content
    /// \param ptr Address of the Ptr object
    /// \return Runtime Ptr content's reflection info
    const TypeClass* GetContentType(void* ptr) const;

    /// Gets the address of Ptr content
    /// \return Ptr content's address
    void* GetContent(void* ptr) const;

protected:
    const Type* mContentType;

    NS_DECLARE_REFLECTION(TypePtr, Type)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeArray. Defines reflection info for a static array type.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypeArray: public TypeCollection
{
public:
    /// Constructor
    TypeArray(const TypeInfo& typeInfo);

    /// Sets number of elements in the array
    void SetElemCount(NsSize elemCount);

    /// Sets size of the elements in the array
    void SetElemSize(NsSize elemSize);

    /// Gets number of elements of the array
    inline NsSize GetNumElems() const;

    /// From TypeCollection
    //@{
    NsSize GetNumElems(const void* ptr) const;
    const void* Get(const void* ptr, NsSize i) const;
    const NsChar* GetCollectionId() const;
    //@}

protected:
    NsSize mElemCount;
    NsSize mElemSize;

    NS_DECLARE_REFLECTION(TypeArray, TypeCollection)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper function to extract the TypeClass of the component that could be referenced by 'type'
/// if it is a TypePtr or TypePointer.
///
/// For example:
///
///     ExtractComponentType(TypeOf<Ptr<BaseComponent> >()) == TypeOf<BaseComponent>();
///     ExtractComponentType(TypeOf<Ptr<const BaseComponent> >()) == TypeOf<BaseComponent>();
///     ExtractComponentType(TypeOf<Ptr<Interface> >()) == TypeOf<Interface>();
///     ExtractComponentType(TypeOf<Ptr<const Interface> >()) == TypeOf<Interface>();
///     ExtractComponentType(TypeOf<BaseComponent*>()) == TypeOf<BaseComponent>();
///     ExtractComponentType(TypeOf<const BaseComponent*>()) == TypeOf<BaseComponent>();
///     ExtractComponentType(TypeOf<Interface*>()) == TypeOf<Interface>();
///     ExtractComponentType(TypeOf<const Interface*>()) == TypeOf<Interface>();
///     ExtractComponentType(TypeOf<MyStruct*>()) == 0;
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_CORE_KERNEL_API
const TypeClass* ExtractComponentType(const Type* type);

}
}

// Inline Include
#include <NsCore/TypePointer.inl>


#endif
