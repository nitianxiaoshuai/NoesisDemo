////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ICONTROLLIBRARY_H__
#define __GUI_ICONTROLLIBRARY_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{
namespace Gui
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// IControlLibrary. Manages resources of a control library. UISystem looks for all components
/// registered in the factory with 'ControlLibrary' category and then asks for its resources using
/// this interface.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IControlLibrary: public Core::Interface
{
    /// Gets the location of the specified theme resource file for this control library
    virtual const NsChar* GetResourceFile(const NsChar* themeName) const = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IControlLibrary, Core::Interface)
};

}
}

#endif