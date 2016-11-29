////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IXAMLCONTEXT_H__
#define __GUI_IXAMLCONTEXT_H__


#include <Noesis.h>
#include <NsCore/Symbol.h>
#include <NsCore/NSTLForwards.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
class BaseComponent;
}
namespace Gui
{
class XamlNode;
class AmbientStack;
NS_INTERFACE IResourceKey;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes the current context of a XAML tree parsing process
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IXamlContext
{
    virtual Core::BaseComponent* GetCurrentInstance() const = 0;
    virtual Core::BaseComponent* FindName(const NsChar* name) const = 0;
    virtual const NsChar* GetFileName() const = 0;
    virtual const AmbientStack& GetAmbient() const = 0;
    virtual const NsChar* GetTypedPrefix(const NsChar* prefix) const = 0;
};

}
}

#endif
