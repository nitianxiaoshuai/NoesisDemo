////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TEMPLATEPARTMETADATA_H__
#define __GUI_TEMPLATEPARTMETADATA_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/String.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TemplatePartMetaData. Represents an attribute that is applied to the class definition to
/// identify the types of the named parts that are used for templating.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TemplatePartMetaData: public Core::TypeMetaData
{
public:
    /// Constructor
    TemplatePartMetaData(const NsChar* name, const Core::TypeClass* type);

    /// Gets the pre-defined name of the part
    const NsChar* GetPartName() const;

    /// Gets the type of the named part this attribute is identifying
    const Core::TypeClass* GetPartType() const;

private:
    NsString mPartName;
    const Core::TypeClass* mPartType;

    NS_DECLARE_REFLECTION(TemplatePartMetaData, Core::TypeMetaData)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
