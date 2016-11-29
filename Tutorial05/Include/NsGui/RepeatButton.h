////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_REPEATBUTTON_H__
#define __GUI_REPEATBUTTON_H__


#include <Noesis.h>
#include <NsGui/BaseButton.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that raises its Click event repeatedly from the time it is
/// pressed until it is released.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.repeatbutton.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RepeatButton: public BaseButton
{
public:
    /// Constructor
    RepeatButton();

    /// Destructor
    ~RepeatButton();

    /// Gets or sets the amount of time, in milliseconds, the RepeatButton waits while it is
    /// pressed before it starts repeating. The value must be non-negative
    //@{
    NsInt32 GetDelay() const;
    void SetDelay(NsInt32 delay);
    //@}

    /// Gets or sets the amount of time, in milliseconds, between repeats once repeating starts.
    /// The value must be non-negative
    //@{
    NsInt32 GetInterval() const;
    void SetInterval(NsInt32 interval);
    //@}

    /// Dependency properties
    //@{
    static const DependencyProperty* DelayProperty;
    static const DependencyProperty* IntervalProperty;
    //@}

protected:
    // From BaseButton
    //@{
    void OnClick();
    //@}

    // From UIElement
    //@{
    //protected override AutomationPeer OnCreateAutomationPeer();
    void OnKeyDown(const KeyEventArgs& e);
    void OnKeyUp(const KeyEventArgs& e);
    void OnLostMouseCapture(const MouseEventArgs& e);
    void OnMouseEnter(const MouseEventArgs& e);
    void OnMouseLeave(const MouseEventArgs& e);
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e);
    //@}
    
    void StartTimer();
    void StopTimer();

    NsUInt32 OnTimerElapsed(void*);

private:
    static NsBool ValidateDelay(const void* value);
    static NsBool ValidateInterval(const void* value);

private:
    NsUInt32 mTimerId;

    NS_DECLARE_REFLECTION(RepeatButton, BaseButton)
};

}
}

#endif
