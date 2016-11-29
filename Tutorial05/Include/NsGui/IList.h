////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ILIST_H__
#define __GUI_ILIST_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
template<class T> class Ptr;
class BaseComponent;
}
using Core::Ptr;
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IList. Represents a generic collection of objects that can be individually accessed by index.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IList: public Core::Interface
{
    /// Gets the number of items in the collection
    virtual NsSize Count() const = 0;

    /// Gets or sets the item at the specified index
    //@{
    virtual Core::BaseComponent* Get(NsSize index) const = 0;
    virtual void Set(NsSize index, Core::BaseComponent* item) = 0;
    virtual void Set(NsSize index, const NsChar* item) = 0;
    //@}

    /// Adds an item to the collection
    /// \return It returns the insertion position in the collection
    virtual NsSize Add(Core::BaseComponent* item) = 0;
    virtual NsSize Add(const NsChar* item) = 0;

    /// Removes all elements from the collection
    virtual void Clear() = 0;

    /// Determines whether the collection contains a specific item
    virtual NsBool Contains(Core::BaseComponent* item) const = 0;

    /// Determines the index of a specific item in the collection
    /// \return It returns -1 if the item is not found
    virtual NsInt IndexOf(Core::BaseComponent* item) const = 0;

    /// Inserts an item to the collection at the specified index
    virtual void Insert(NsSize index, Core::BaseComponent* item) = 0;
    virtual void Insert(NsSize index, const NsChar* item) = 0;

    /// Removes the first occurrence of a specific item from the collection
    virtual void Remove(Core::BaseComponent* item) = 0;

    /// Removes the collection item at the specified index
    virtual void RemoveAt(NsSize index) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IList, Core::Interface)
};

}
}


#endif
