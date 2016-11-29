////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ICOMPONENTINITIALIZER_H__
#define __GUI_ICOMPONENTINITIALIZER_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsGui/DependencySystemApi.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IComponentInitializer. Identifies components that can be initialized.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IComponentInitializer: public Core::Interface
{
    /// Indicates if component is already initialized
    virtual NsBool IsInitialized() const = 0;

    /// Initializes the component
    virtual void Init() = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IComponentInitializer, Core::Interface)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void InitComponent(IComponentInitializer* component, NsBool doInit)
{
    if (doInit && component && !component->IsInitialized())
    {
        component->Init();
    }
}

}
}


#endif
