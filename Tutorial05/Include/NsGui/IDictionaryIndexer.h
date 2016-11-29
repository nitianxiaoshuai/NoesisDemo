////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IDICTIONARYINDEXER_H__
#define __GUI_IDICTIONARYINDEXER_H__


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
/// Represents an indexer object that can be accessed with a string key.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IDictionaryIndexer: public Core::Interface
{
    /// Gets or sets the item associated with the specified key
    /// \return False if index is out of bounds
    //@{
    virtual NsBool TryGet(const NsChar* key, Core::BaseComponent*& item) const = 0;
    virtual NsBool TrySet(const NsChar* key, Core::BaseComponent* item) = 0;
    virtual NsBool TrySet(const NsChar* key, const NsChar* item) = 0;
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION_(IDictionaryIndexer, Core::Interface)
};

}
}


#endif
