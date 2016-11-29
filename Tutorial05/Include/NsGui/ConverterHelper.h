////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONVERTERHELPER_H__
#define __GUI_CONVERTERHELPER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/String.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
template<class T> class Ptr;
class TypeClass;
class TypeProperty;
class Symbol;
NS_INTERFACE ITypeConverter;
}
using Core::Ptr;
namespace Gui
{
class DependencyProperty;
}
//@}

namespace Gui
{

/// Gets proper converter for a class. First look in the metadata, and if no converter is specified,
/// try to instance the standard converter based on the type of the class
NS_GUI_CORE_API Ptr<Core::ITypeConverter> TryGetConverter(const Core::TypeClass* typeClass);
NS_GUI_CORE_API Ptr<Core::ITypeConverter> GetConverter(const Core::TypeClass* typeClass);

/// Gets proper converter for a property. First look in the metadata of the property for a custom
/// converter, and if none is found, try to instance the standard converter based on the type of
/// the value stored by the property
NS_GUI_CORE_API Ptr<Core::ITypeConverter> TryGetConverter(const Core::TypeProperty* typeProperty);
NS_GUI_CORE_API Ptr<Core::ITypeConverter> GetConverter(const Core::TypeProperty* typeProperty);

/// Gets proper converter for a dependency property. First look in the metadata of the property for 
/// a custom converter, and if none is found, try to instance the standard converter based on the 
/// type of the property
NS_GUI_CORE_API Ptr<Core::ITypeConverter> TryGetConverter(const DependencyProperty* dp);
NS_GUI_CORE_API Ptr<Core::ITypeConverter> GetConverter(const DependencyProperty* dp);

/// Converts a string to symbol without adding to the symbol table. If the symbol doesn't exist,
/// an exception is thrown
/// \param message To be launched with the exception. It must have a %s to include'str'
NS_GUI_CORE_API Core::Symbol SafeSymbol(const NsChar* str, const NsChar* message);
NS_GUI_CORE_API Core::Symbol SafeSymbol(const NsString& str, const NsChar* message);

NS_GUI_CORE_API NsBool TrySafeSymbol(const NsChar* str, Core::Symbol& result);
NS_GUI_CORE_API NsBool TrySafeSymbol(const NsString& str, Core::Symbol& result);

typedef void (*SymbolFallbackHandler)(const NsChar* str);
NS_GUI_CORE_API void SetSymbolFallbackHandler(SymbolFallbackHandler handler);
}
}


#endif
