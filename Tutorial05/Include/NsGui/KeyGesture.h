////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_KEYGESTURE_H__
#define __GUI_KEYGESTURE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/InputGesture.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/NSTLForwards.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a keyboard combination that can be used to invoke a command.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.input.keygesture.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API KeyGesture: public InputGesture
{
public:
    /// Constructor
    KeyGesture();

    /// Constructor for code
    KeyGesture(NsUInt32 key, NsUInt32 modifiers = 0);

    /// Destructor
    ~KeyGesture();

    /// Gets the key associated with this KeyGesture
    NsUInt32 GetKey() const;

    /// Gets the modifier keys associated with this KeyGesture
    NsUInt32 GetModifiers() const;

    /// Gets a string to be displayed in UI
    /// \prop
    NsString GetDisplayString() const;

    /// From InputGesture
    //@{
    NsBool Matches(Core::BaseComponent* target, const RoutedEventArgs& args);
    //@}

private:
    NsBool CheckModifiers(Core::BaseComponent* target) const;

private:
    NsUInt32 mKey;
    NsUInt32 mModifiers;

    NS_DECLARE_REFLECTION(KeyGesture, InputGesture)
};

}
}


#endif
