////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_ILAYERMANAGER_H__
#define __CORE_ILAYERMANAGER_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class Visual;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ILayerManager. Mantains a list of visual layers.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE ILayerManager: public Core::Interface
{
    /// Adds a visual to a new layer
    virtual void AddLayer(Visual* layerRoot) = 0;

    /// Removes a visual layer
    virtual void RemoveLayer(Visual* layerRoot) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(ILayerManager, Core::Interface)
};

}
}


#endif
