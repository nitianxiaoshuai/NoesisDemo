////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_IVALUECONVERTER_H__
#define __CORE_IVALUECONVERTER_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
template<class T> class Ptr;
class BaseComponent;
}
using Core::Ptr;
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IValueConverter. Provides a way to apply custom logic to a binding. 
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IValueConverter: public Core::Interface
{
    /// The data binding engine calls this method when it propagates a value from the binding 
    /// source to the binding target
    /// \param value The value produced by the binding source
    /// \param targetType The type of the binding target property
    /// \param parameter The converter parameter to use
    virtual Ptr<Core::BaseComponent> Convert(Core::BaseComponent* value, 
        const Core::Type* targetType, Core::BaseComponent* parameter) = 0;

    /// Safe function to convert from the binding source to the binding target.
    virtual NsBool TryConvert(Core::BaseComponent* value, 
        const Core::Type* targetType, Core::BaseComponent* parameter, 
        Ptr<Core::BaseComponent>& result) = 0;
        
    /// The data binding engine calls this method when it propagates a value from the binding 
    /// target to the binding source
    /// \param value The value that is produced by the binding target
    /// \param targetType The type to convert to
    /// \param parameter The converter parameter to use
    virtual Ptr<Core::BaseComponent> ConvertBack(Core::BaseComponent* value, 
        const Core::Type* targetType, Core::BaseComponent* parameter) = 0;

    /// Safe function to convert from the binding target to the binding source. If the conversion
    /// cannot be done, a null Ptr is returned
    virtual NsBool TryConvertBack(Core::BaseComponent* value, 
        const Core::Type* targetType, Core::BaseComponent* parameter, 
        Ptr<Core::BaseComponent>& result) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IValueConverter, Core::Interface)
};

}
}


#endif
