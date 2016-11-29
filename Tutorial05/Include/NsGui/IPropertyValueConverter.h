////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IPROPERTYVALUECONVERTER_H__
#define __GUI_IPROPERTYVALUECONVERTER_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyProperty;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// This type of converters use a DependencyProperty to specify the target type
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IPropertyValueConverter: public Core::Interface
{
    virtual const DependencyProperty* GetProperty() const = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IPropertyValueConverter, Core::Interface)
};

}
}

#endif
