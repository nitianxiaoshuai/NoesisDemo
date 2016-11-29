////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RANGEBASE_H__
#define __GUI_RANGEBASE_H__


#include <Noesis.h>
#include <NsGui/Control.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an element that has a value within a specific range. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.rangebase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RangeBase: public Control
{
public:
    /// Constructor
    RangeBase();
    
    /// Destructor
    virtual ~RangeBase() = 0;
    
    /// Gets or sets a value to be added to or subtracted from the Value of a RangeBase control
    //@{
    NsFloat32 GetLargeChange() const;
    void SetLargeChange(NsFloat32 value);
    //@}
    
    /// Gets or sets the highest possible Value of the range element.
    //@{
    NsFloat32 GetMaximum() const;
    void SetMaximum(NsFloat32 value);
    //@}
    
    /// Gets or sets the Minimum possible Value of the range element. 
    //@{
    NsFloat32 GetMinimum() const;
    void SetMinimum(NsFloat32 value);
    //@}
    
    /// Gets or sets a Value to be added to or subtracted from the Value of a RangeBase control.
    //@{
    NsFloat32 GetSmallChange() const;
    void SetSmallChange(NsFloat32 value);
    //@}
    
    /// Gets or sets the current magnitude of the range control. 
    //@{
    NsFloat32 GetValue() const;
    void SetValue(NsFloat32 value);
    //@}

    /// Occurs when the range value changes. 
    UIElement::RoutedEvent_<RoutedPropertyChangedEventHandler<NsFloat32>::Handler> ValueChanged();

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* LargeChangeProperty;
    static const DependencyProperty* MaximumProperty;
    static const DependencyProperty* MinimumProperty;
    static const DependencyProperty* SmallChangeProperty;
    static const DependencyProperty* ValueProperty;
    //@}
    
    /// Routed Events
    //@{
    static const RoutedEvent* ValueChangedEvent;
    //@}
    
protected:
    virtual void OnMaximumValueChanged(NsFloat32 oldMaximum, NsFloat32 newMaximum);
    virtual void OnMinimumValueChanged(NsFloat32 oldMinimum, NsFloat32 newMinimum);
    virtual void OnValueChanged(NsFloat32 oldValue, NsFloat32 newValue);

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}
    
    /// From Control
    //@{
    void UpdateVisualStates();
    //@}

private:
    static NsBool StaticCoerceMaxValue(const DependencyObject* object, const void* value,
        void* coercedValue);
    static NsBool StaticCoerceValue(const DependencyObject* object, const void* value,
        void* coercedValue);

    NS_DECLARE_REFLECTION(RangeBase, Control)
};

}
}

#endif