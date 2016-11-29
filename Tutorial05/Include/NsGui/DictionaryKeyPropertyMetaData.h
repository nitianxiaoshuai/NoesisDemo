////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DICTIONARYKEYPROPERTYMETADATA_H__
#define __GUI_DICTIONARYKEYPROPERTYMETADATA_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/Symbol.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DictionaryKeyPropertyMetaData
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DictionaryKeyPropertyMetaData: public Core::TypeMetaData
{
public:
    /// Constructor
    DictionaryKeyPropertyMetaData(NsSymbol property);

    /// Gets content property
    inline NsSymbol GetProperty() const;

private:
    NsSymbol mProperty;
    
private:
    NS_DECLARE_REFLECTION(DictionaryKeyPropertyMetaData, Core::TypeMetaData)
};

}
}


#include <NsGui/DictionaryKeyPropertyMetaData.inl>


#endif