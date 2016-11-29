////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef __GUI_PROVIDERVALUE_H__
#define __GUI_PROVIDERVALUE_H__


#include <Noesis.h> 
#include <NsCore/Ptr.h>
#include <NsGui/DependencySystemApi.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
class BaseComponent;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

struct NS_GUI_DEPENDENCYSYSTEM_API ProviderValue
{
    ProviderValue();

    // Return values can be a boxed value or a raw value
    //@{
    // TODO: This can be changed to a BaseComponent* because providers doesn't create elements
    // TODO: Put into a union
    Ptr<Core::BaseComponent> boxed;
    const void* rawValue;
    //@}

    /// Priority of the provider which returned the values
    NsUInt8 providerPriority;
    
    // Indicates which of the above fields is valid. If its a raw value, the caching can be avoided
    // TODO [srodriguez] This will dissapear and the condition to not cache an element will be
    // comparing priority with InheritedValueProviderPriority or DefaultValueProviderPriority
    NsBool isRawValueAndNonCached;
    
    // Use 8 bits to store provider priority (256 possible providers)
    // User providers can't utilize LocalProviderPriority nor DefaultValueProviderPriority,
    // so there can be 254 max user providers
    static const NsUInt8 LocalProviderPriority = 0;
    static const NsUInt8 InheritedValueProviderPriority = 0xFE;
    static const NsUInt8 DefaultValueProviderPriority = 0xFF;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
