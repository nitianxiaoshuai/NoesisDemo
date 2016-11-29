////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BUTTON_H__
#define __GUI_BUTTON_H__


#include <Noesis.h>
#include <NsGui/BaseButton.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a push button which reacts to the Click event.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.button.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Button: public BaseButton
{
public:
    /// Constructor
    Button();

    /// Destructor
    ~Button();

    /// Gets or sets a value that indicates whether a Button is a Cancel button. A user can
    /// activate the Cancel button by pressing the ESC key
    //@{
    NsBool GetIsCancel() const;
    void SetIsCancel(NsBool value);
    //@}

    /// Gets or sets a value that indicates whether a Button is the default button. A user invokes
    /// the default button by pressing the ENTER key
    //@{
    NsBool GetIsDefault() const;
    void SetIsDefault(NsBool value);
    //@}

    /// Gets a value that indicates whether a Button is the button that is activated when a user
    /// presses ENTER
    NsBool GetIsDefaulted() const;
    
    /// Dependency properties
    //@{
    static const DependencyProperty* IsCancelProperty;
    static const DependencyProperty* IsDefaultProperty;
    static const DependencyProperty* IsDefaultedProperty;
    //@}
    
protected:
    /// From BaseButton
    //@{
    void OnClick();
    //@}

    NS_DECLARE_REFLECTION(Button, BaseButton)
};

}
}

#endif
