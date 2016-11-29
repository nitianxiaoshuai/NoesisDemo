////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEVALUECONVERTER_H__
#define __GUI_BASEVALUECONVERTER_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IValueConverter.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for converters
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseValueConverter: public Core::BaseComponent, public IValueConverter
{
public:
    BaseValueConverter();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~BaseValueConverter() = 0;

    /// From IValueConverter
    //@{
    Ptr<Core::BaseComponent> Convert(Core::BaseComponent* value, const Core::Type* targetType,
        Core::BaseComponent* parameter);
    NsBool TryConvert(Core::BaseComponent* value, const Core::Type* targetType,
        Core::BaseComponent* parameter, Ptr<Core::BaseComponent>& result);
    Ptr<Core::BaseComponent> ConvertBack(Core::BaseComponent* value, const Core::Type* targetType,
        Core::BaseComponent* parameter);
    NsBool TryConvertBack(Core::BaseComponent* value, const Core::Type* targetType,
        Core::BaseComponent* parameter, Ptr<Core::BaseComponent>& result);
    //@}

private:
    /// Base classes are non-copyable objects
    //@{
    BaseValueConverter(const BaseValueConverter&);
    BaseValueConverter& operator=(const BaseValueConverter&);
    //@}

private:
    NS_DECLARE_REFLECTION(BaseValueConverter, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
