////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_HANDOFFBEHAVIOR_H__
#define __GUI_HANDOFFBEHAVIOR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclareEnum.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies how new animations interact with any existing ones that are already applied to a 
/// property.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum HandoffBehavior
{
    /// New animations replace any existing animations on the properties to which they are applied.
    HandoffBehavior_SnapshotAndReplace,
    /// New animations are combined with existing animations by appending the new animations to the 
    /// end of the composition chain.
    HandoffBehavior_Compose
};

}
}

NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::HandoffBehavior)


#endif
