////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1215]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IRESOURCEKEY_H__
#define __GUI_IRESOURCEKEY_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsCore/TypeId.h>
#include <NsCore/ReflectionImplement.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Interface to be implemented by classes that will be used as keys in a resource dictionary map.
/// Examples of classes that implement this interface are ResourceKeyType and ResourceKeyString to
/// support Types and Strings to be used as dictionary keys
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IResourceKey: public Core::Interface
{
    /// Comparison methods
    //@{
    virtual NsBool Equals(const IResourceKey* resourceKey) const = 0;
    virtual NsBool IsLessThan(const IResourceKey* resourceKey) const = 0;
    //@}
    
    /// Gets a string describing the key (useful when notifying errors)
    virtual NsString GetStr() const = 0;

    NS_IMPLEMENT_INLINE_REFLECTION(IResourceKey, Core::Interface)
    {
        // Needed by TypeConverter
        NsMeta<Core::TypeId>("IResourceKey");
    }
};

}
}

#endif