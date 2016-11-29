////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_INTERFACE_H__
#define __CORE_INTERFACE_H__


#include <NsCore/Types.h>
#include <NsCore/ReflectionImplementEmpty.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
class TypeClass;
class BaseObject;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Interface. Used as base for all component interfaces.
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SWIG
NS_INTERFACE Interface
{
    /// Gets the object type metadata
    /// \return Type metadata of the object
    virtual const TypeClass* GetClassType() const = 0;

    /// Gets a pointer to the object implementation
    /// \return Object implementation pointer
    virtual BaseObject* GetBaseObject() const = 0;

    /// Increments reference count
    /// \returns Number of references after incrementing one
    virtual NsInt32 AddReference() const = 0;

    /// Decrements reference count, deleting the object when reaches 0
    /// \returns Number of references after releasing one
    virtual NsInt32 Release() const = 0;

    /// Gets current reference count for the object
    /// \return Object number of references
    virtual NsInt32 GetNumReferences() const = 0;

    virtual ~Interface() = 0;

    NS_IMPLEMENT_INLINE_STATIC_REFLECTION_(Interface, NoParent)
};

inline Interface::~Interface() {}

#endif

}
}


#endif
