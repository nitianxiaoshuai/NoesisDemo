////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ILISTINDEXER_H__
#define __GUI_ILISTINDEXER_H__


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
/// Represents an indexer object that can be accessed with an integer index.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IListIndexer: public Core::Interface
{
    /// Gets or sets the item at the specified index
    /// \return False if index is out of bounds
    //@{
    virtual NsBool TryGet(NsSize index, Core::BaseComponent*& item) const = 0;
    virtual NsBool TrySet(NsSize index, Core::BaseComponent* item) = 0;
    virtual NsBool TrySet(NsSize index, const NsChar* item) = 0;
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION_(IListIndexer, Core::Interface)
};

}
}


#endif
