////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #475]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_COMPONENTFACTORY_H__
#define __CORE_COMPONENTFACTORY_H__


#include <NsCore/Types.h>
#include <NsCore/CompilerSettings.h>
#include <NsCore/PtrForward.h>
#include <EASTL/fixed_vector.h>


NS_CFORWARD(Core, BaseComponent)
NS_CFORWARD(Core, Symbol)


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A factory where components can be registered to later be created. Components are identified
/// using a symbol that represents its ClassId. Different components can be grouped using another
/// identifier for the category.
////////////////////////////////////////////////////////////////////////////////////////////////////
class ComponentFactory
{
public:
    /// Checks if a component is registered in the factory
    virtual NsBool IsComponentRegistered(Symbol classId) const = 0;

    /// Enumerates components belonging to a category
    typedef eastl::fixed_vector<Symbol, 32> Vector;
    virtual void EnumComponents(Symbol category, Vector& v) const = 0;

    /// Creates an instance of a component given its symbol identifier
    virtual Ptr<BaseComponent> CreateComponent(Symbol classId) const = 0;

    /// Registers a component
    typedef BaseComponent* (*CreatorFn)(Symbol classId);
    virtual void RegisterComponent(Symbol classId, Symbol category, CreatorFn creatorFn) = 0;

    /// Unregisters a previously registered component
    virtual void UnregisterComponent(Symbol classId) = 0;

    /// The fallback handler is invoked when requesting a class that is not registered
    typedef void (*FallbackHandler)(Symbol classId, ComponentFactory* factory);
    virtual void SetFallbackHandler(FallbackHandler handler) = 0;
};

}
}


#endif
