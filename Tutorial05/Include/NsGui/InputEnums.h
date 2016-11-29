////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INPUTENUMS_H__
#define __GUI_INPUTENUMS_H__


#include <Noesis.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum MouseButton
{
    MouseButton_Left,
    MouseButton_Right,
    MouseButton_Middle,
    MouseButton_XButton1,
    MouseButton_XButton2,

    MouseButton_Count
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum MouseButtonState
{
    MouseButtonState_Pressed,
    MouseButtonState_Released
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum Key
{
    Key_None,
    Key_Back,
    Key_Tab,
    Key_Clear,
    Key_Return,
    Key_Pause,

    Key_Shift,
    Key_Control,
    Key_Alt,

    Key_Escape,

    Key_Space,
    Key_Prior,
    Key_Next,
    Key_End,
    Key_Home,
    Key_Left,
    Key_Up,
    Key_Right,
    Key_Down,
    Key_Select,
    Key_Print,
    Key_Execute,
    Key_SnapShot,
    Key_Insert,
    Key_Delete,
    Key_Help,

    Key_0,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,

    Key_Pad0,
    Key_Pad1,
    Key_Pad2,
    Key_Pad3,
    Key_Pad4,
    Key_Pad5,
    Key_Pad6,
    Key_Pad7,
    Key_Pad8,
    Key_Pad9,

    Key_Multiply,
    Key_Add,
    Key_Separator,
    Key_Subtract,
    Key_Decimal,
    Key_Divide,

    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,

    Key_F1,
    Key_F2,
    Key_F3,
    Key_F4,
    Key_F5,
    Key_F6,
    Key_F7,
    Key_F8,
    Key_F9,
    Key_F10,
    Key_F11,
    Key_F12,
    Key_F13,
    Key_F14,
    Key_F15,
    Key_F16,
    Key_F17,
    Key_F18,
    Key_F19,
    Key_F20,
    Key_F21,
    Key_F22,
    Key_F23,
    Key_F24,

    Key_NumLock,
    Key_Scroll,

    Key_Oem1,
    Key_OemSemicolon = Key_Oem1,
    Key_OemPlus,
    Key_OemComma,
    Key_OemMinus,
    Key_OemPeriod,
    Key_Oem2,
    Key_OemQuestion = Key_Oem2,
    Key_Oem3,
    KeyOemTilde = Key_Oem3,
    Key_Oem4,
    Key_OemOpenBrackets = Key_Oem4,
    Key_Oem5,
    Key_OemPipe = Key_Oem5,
    Key_Oem6,
    Key_OemCloseBrackets = Key_Oem6,
    Key_Oem7,
    Key_OemQuotes = Key_Oem7,
    Key_Oem8,
    Key_Oem102,
    Key_OemBackslash = Key_Oem102,

    Key_Count
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum KeyStateFlags
{
    /// The key is not pressed.
    KeyStateFlags_None = 0x00,

    /// The key is pressed.
    KeyStateFlags_Down = 0x01,

    /// The key is toggled.
    KeyStateFlags_Toggled = 0x02
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum ModifierKeys
{
    ModifierKeys_None = 0,
    ModifierKeys_Alt = 1,
    ModifierKeys_Control = 2,
    ModifierKeys_Shift = 4
};

}
}


#endif
