////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #710]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPECONVERTER_H__
#define __CORE_TYPECONVERTER_H__


#include <Noesis.h>
#include <NsCore/TypeConverterApi.h>
#include <NsCore/ITypeConverter.h>


namespace Noesis
{
namespace Core
{
namespace TypeConverter
{

/// Returns the converter registered for the given type
NS_CORE_TYPECONVERTER_API Ptr<ITypeConverter> Create(const Type* type);

/// Checks if there is a converter registered for the given type
NS_CORE_TYPECONVERTER_API NsBool HasConverter(const Type* type);

/// Returns a friendly name to be used for displaying errors about the given converter
NS_CORE_TYPECONVERTER_API NsString DebugName(ITypeConverter const * const converter);

}
}
}


#endif