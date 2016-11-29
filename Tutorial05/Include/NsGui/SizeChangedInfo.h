////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SIZECHANGEDINFO_H__
#define __GUI_SIZECHANGEDINFO_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/RoutedEvent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsDrawing/Size.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Reports a size change. It is used as a parameter in OnRenderSizeChanged overrides.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct SizeChangedInfo
{
    Drawing::Size newSize;
    Drawing::Size previousSize;
    NsBool widthChanged;
    NsBool heightChanged;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API SizeChangedEventArgs: public RoutedEventArgs
{
    SizeChangedInfo sizeChangedInfo;

    SizeChangedEventArgs(Core::BaseComponent* s, const RoutedEvent* e, 
        const SizeChangedInfo& sizeChangedInfo);
};

}
}


#endif
