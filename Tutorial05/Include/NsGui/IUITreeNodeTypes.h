////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IUITREENODETYPES_H__
#define __GUI_IUITREENODETYPES_H__


#include <Noesis.h>
#include <NsCore/Interface.h>

namespace Noesis
{

/// Forward declarations
//@{
namespace Core
{
class BaseComponent;
}
namespace Gui
{
NS_INTERFACE INameScope;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
struct ObjectWithNameScope
{
    Core::BaseComponent* object;
    INameScope* scope;

    ObjectWithNameScope(Core::BaseComponent* o = 0, INameScope* s = 0) : object(o), scope(s) { }
};

}
}

#endif