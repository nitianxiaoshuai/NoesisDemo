////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_XAMLREADERPROVIDER_H__
#define __GUI_XAMLREADERPROVIDER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ValueTargetProvider.h>
#include <NsCore/Symbol.h>


namespace Noesis
{
namespace Gui
{

// Forward declaration
//@{
NS_INTERFACE IXamlContext;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// XamlReaderProvider
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API XamlReaderProvider: public ValueTargetProvider
{
public:
    XamlReaderProvider(Core::BaseComponent* targetObject, NsSymbol targetProperty, 
        const Core::TypeClass* propertyOwner, const IXamlContext* context);

    const IXamlContext* GetContext() const;
    NsSymbol GetPropertyName() const;
    const Core::TypeClass* GetPropertyOwner() const;

private:
    const IXamlContext* mContext;
    NsSymbol mTargetPropertyName;
    const Core::TypeClass* mPropertyOwner;
};

}
}

#endif
