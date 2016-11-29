////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MOUSESTATE_H__
#define __GUI_MOUSESTATE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/InputEnums.h>
#include <NsDrawing/Point.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API MouseState
{
    Drawing::Point position;
    MouseButtonState leftButton;
    MouseButtonState rightButton;
    MouseButtonState middleButton;
    MouseButtonState xButton1Button;
    MouseButtonState xButton2Button;

    MouseState();

    MouseState(const Drawing::Point& position, MouseButtonState leftButton, 
        MouseButtonState rightButton, MouseButtonState middleButton,
        MouseButtonState xButton1Button, MouseButtonState xButton2Button);
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}


#endif
