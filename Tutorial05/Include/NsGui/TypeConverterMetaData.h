////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TYPECONVERTERMETADATA_H__
#define __GUI_TYPECONVERTERMETADATA_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/Symbol.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeConverterMetaData. Stores information about the proper TypeConverter for an object
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TypeConverterMetaData: public Core::TypeMetaData
{
public:
    /// Constructor
    TypeConverterMetaData(const NsChar* typeId);

    /// Gets converter type Id
    NsSymbol GetTypeId() const;

private:
    NsSymbol mTypeId;

    NS_DECLARE_REFLECTION(TypeConverterMetaData, Core::TypeMetaData)
};

}
}


#endif
