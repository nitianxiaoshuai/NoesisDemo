////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_AMBIENTPROPERTYMETADATA_H__
#define __GUI_AMBIENTPROPERTYMETADATA_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/TypeMetaData.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// AmbientPropertyMetaData. Makes the value of the property available in the parser context to 
/// objects that exist as child objects in an object tree.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API AmbientPropertyMetaData: public Core::TypeMetaData
{
private:
    NS_DECLARE_REFLECTION(AmbientPropertyMetaData, Core::TypeMetaData)
};

}
}


#endif
