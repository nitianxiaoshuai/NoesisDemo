////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1051]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_AMBIENTSTACK_H__
#define __GUI_AMBIENTSTACK_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/Ptr.h>
#include <NsCore/Map.h>
#include <NsCore/Stack.h>


namespace Noesis
{
// Forward declarations
//@{
namespace Core
{
class BaseComponent;
class TypeClass;
class Symbol;
}
//@}
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// AmbientStack. Provides a multistack to store values indexed by Class.Property pairs
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API AmbientStack
{
public:
    /// Constructor
    AmbientStack();
    
    // Destructor
    ~AmbientStack();

    /// Adds a value for the typeClass.property passed
    void PushValue(const Core::TypeClass* typeClass, Core::Symbol property, 
        const Ptr<Core::BaseComponent>& value);
    
    /// Pops the latest added value for typeClass.property from the stack
    void PopValue(const Core::TypeClass* typeClass, Core::Symbol property);
    
    /// Get the lastest added value for typeClass.property without removing from the stack
    const Ptr<Core::BaseComponent>& GetValue(const Core::TypeClass* typeClass, 
        Core::Symbol property) const;
    
    /// Checks if there is a value for typeClass.property in the stack
    NsBool HasValue(const Core::TypeClass* typeClass, Core::Symbol property) const;

    /// Returns the number of ambient properties stored. Only for debug use
    NsSize GetNumAmbients() const;

private:
    // NOTE: Can't use multimap because the order in which duplicate values are retrieved is not 
    // guaranteed
    typedef Core::nstl::pair<const Core::TypeClass*, Core::Symbol> Key;
    typedef NsStack<Ptr<Core::BaseComponent> > Values;
    typedef NsMap<Key, Values> Ambients;
    Ambients mAmbients;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
