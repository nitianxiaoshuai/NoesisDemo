////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #620]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_DYNAMICCAST_H__
#define __CORE_DYNAMICCAST_H__


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Functions for casting between pointers:
///
///    Cube* cube = *new Cube();
///    IRenderable* renderable = NsDynamicCast<IRenderable*>(cube);
///
/// Dynamic cast uses the reflection information stored in Noesis::BaseComponent. When classed
/// are related, a static cast can be used. NsStaticCast is equivalent to static_cast although in
/// debug it is equivalent to NsDynamicCast.
///
/// There are equivalent funtions for Ptr<> pointers:
///
///    Ptr<Cube> cube = *new Cube();
///    Ptr<IRenderable> renderable = NsDynamicCast< Ptr<IRenderable> >(cube);
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <Noesis.h>
#include <NsCore/DynamicCastPointer.h>
#include <NsCore/DynamicCastPtr.h>


#endif
