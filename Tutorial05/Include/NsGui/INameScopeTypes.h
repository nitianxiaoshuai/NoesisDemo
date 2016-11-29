////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INAMESCOPETYPES_H__
#define __GUI_INAMESCOPETYPES_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>


namespace Noesis
{

namespace Gui
{

enum NameScopeChangedAction
{
    NameScopeChangedAction_Register,
    NameScopeChangedAction_Unregister,
    NameScopeChangedAction_Update,
    NameScopeChangedAction_Destroy
};

struct NameScopeChangedArgs
{
    NameScopeChangedAction action;
    const NsChar* name;
    Core::BaseComponent* newElement;
    Core::BaseComponent* oldElement;

    NameScopeChangedArgs(): name(0), newElement(0), oldElement(0) { }
};

}
}

#endif
