////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_KEYBINDING_H__
#define __GUI_KEYBINDING_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/InputBinding.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class KeyGesture;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Binds a KeyGesture to a Command.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.input.keybinding.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API KeyBinding: public InputBinding
{
public:
    /// Constructor
    KeyBinding();

    /// Constructor for code
    KeyBinding(ICommand* command, KeyGesture* gesture);

    /// Destructor
    ~KeyBinding();

    /// Gets the Key of the KeyGesture associated with this KeyBinding
    NsUInt32 GetKey() const;

    /// Gets the modifier keys (one or more Alt, Ctrl, Shift) of the associated KeyGesture
    NsUInt32 GetModifiers() const;

protected:
    /// From InputBinding
    //@{
    void OnGestureChanged(InputGesture* oldGesture, InputGesture* newGesture);
    //@}

private:
    void UpdateKeyAndModifers(KeyGesture* keyGesture);

private:
    NsUInt32 mKey;
    NsUInt32 mModifiers;

    NS_DECLARE_REFLECTION(KeyBinding, InputBinding)
};

}
}


#endif
