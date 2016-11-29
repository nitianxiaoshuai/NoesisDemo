////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPE_H__
#define __CORE_TYPE_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/BaseObject.h>
#include <NsCore/TypeInfo.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Core
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Root class for the type hierarchy. Type holds information about a run-time type
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API Type: public BaseObject
{
public:
    /// Constructor
    Type(const TypeInfo& typeInfo);

    /// Destructor
    virtual ~Type();

    /// \return a string identifying this type
    const NsChar* GetName() const;

    /// \return a string with a compiler representation of the type
    const NsChar* GetRawName() const;

private:
    TypeInfo mTypeInfo;

    NS_DECLARE_REFLECTION(Type, NoParent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
