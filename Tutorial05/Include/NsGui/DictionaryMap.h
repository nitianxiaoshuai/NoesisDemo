////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1215]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DICTIONARYMAP_H__
#define __GUI_DICTIONARYMAP_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>
#include <NsGui/IResourceKey.h>

#include <NsCore/Map.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
// Specialized map for IResourceKey keys
////////////////////////////////////////////////////////////////////////////////////////////////////
struct DictionaryMapLess 
{
    NsBool operator()(const Ptr<IResourceKey>& a, const Ptr<IResourceKey>& b) const 
    {
        NS_ASSERT(a);
        NS_ASSERT(b);

        return a->IsLessThan(b.GetPtr());
    }
};

typedef NsMap<Ptr<IResourceKey>, Ptr<Core::BaseComponent>, DictionaryMapLess> DictionaryMap;

}
}

#endif