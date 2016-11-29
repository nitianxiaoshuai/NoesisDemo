////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_NAMESCOPEPROPERTYMETADATA_H__
#define __GUI_NAMESCOPEPROPERTYMETADATA_H__


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
/// The component that contains this metadata can be registered into a NameScope using the value of
/// the property specified by the metadata
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API NameScopePropertyMetaData: public Core::TypeMetaData
{
public:
    NameScopePropertyMetaData(const NsChar* nameScopeProperty);
    NameScopePropertyMetaData(NsSymbol nameScopeProperty);
    ~NameScopePropertyMetaData();

    NsSymbol GetNameScopeProperty() const;

private:
    NsSymbol mNameScopeProperty;

    NS_DECLARE_REFLECTION(NameScopePropertyMetaData, Core::TypeMetaData)
};

}
}


#endif
