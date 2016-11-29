////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #473]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPECLASS_H__
#define __CORE_TYPECLASS_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/TypeMeta.h>
#include <NsCore/Symbol.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Vector.h>

#include <memory>


namespace Noesis
{
namespace Core
{

/// Forward declarations.
//@{
class FunctionInvoker;
class TypeProperty;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeClass. Defines reflection info for structs and classes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypeClass: public TypeMeta
{
public:
    /// Constructor
    TypeClass(const TypeInfo& typeInfo, NsBool isInterface);

    /// Destructor
    ~TypeClass();

    /// Defines ancestor information
    struct AncestorInfo
    {
        /// reflection type of ancestor class
        const TypeClass* type;

        /// offset from the implementation class pointer to the ancestor
        NsSize offset;

        /// Constructor
        AncestorInfo(const TypeClass* t, NsSize o): type(t), offset(o) { }
    };

    /// Gets base implementation class type
    const TypeClass* GetBase() const;

    /// Gets number of interfaces this class implements
    NsSize GetNumInterfaces() const;

    /// Gets info about an interface implemented by this class
    const AncestorInfo* GetInterface(NsSize index) const;

    /// Determines if this class is a descendant of the specified type.
    /// \param ancestorType Type of the possible ancestor
    /// \param ancestorInfo Storage for the ancestor info relative to this class
    NsBool IsDescendantOf(const TypeClass* ancestorType,
        const AncestorInfo** ancestorInfo = 0) const;

    /// Gets number of properties of this class reflection type
    /// \return Property count
    NsSize GetNumProperties() const;

    /// Gets a property of the reflection type
    /// \param index Index of the selected property
    /// \return The requested property
    const TypeProperty* GetProperty(NsSize index) const;

    /// Gets a property of the reflection type
    /// \param name Name of the selected property
    const TypeProperty* GetProperty(NsSymbol name) const;

    /// Tries to get a property given its name
    /// \param name Name of the selected property
    /// \return If this class type has the property requested then it returns the property,
    ///     else it returns a null pointer. So this function can be used to test if a class
    ///     contains a specific property given its name
    const TypeProperty* TryGetProperty(NsSymbol name) const;

    /// Tells if this type represents an interface
    /// \return True when it is an interface type
    NsBool IsInterface() const;

protected:
    NsBool mIsInterface;

    // Implementation base class
    const TypeClass* mBase;

    // List of interfaces implemented by this class
    typedef NsVector<AncestorInfo> AncestorVector;
    AncestorVector mInterfaces;

    typedef NsVector<TypeProperty*> PropertyVector;
    PropertyVector mProperties;

private:
    void CollapseAncestors() const;
    void CollapseAncestors(const TypeClass* ancestorType, NsSize offset) const;
    void InsertAncestor(const TypeClass* ancestorType, NsSize offset) const;

private:
    // All ancestors collapsed in a unique list to speed up dynamic cast searches
    struct Ancestors;
    mutable std::auto_ptr<Ancestors> mAncestors;

    NS_DECLARE_REFLECTION(TypeClass, TypeMeta)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}


#endif
