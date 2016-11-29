////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_EXPANDER_H__
#define __GUI_EXPANDER_H__


#include <Noesis.h>
#include <NsGui/HeaderedContentControl.h>
#include <NsCore/ReflectionDeclareEnum.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the control that displays a header that has a collapsible window that
/// displays content.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.expander.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Expander: public HeaderedContentControl
{
public:
    /// Constructor
    Expander();

    /// Gets or sets the direction in which the Expander content window opens
    //@{
    ExpandDirection GetExpandDirection() const;
    void SetExpandDirection(ExpandDirection direction);
    //@}

    /// Gets or sets whether the Expander content window is visible
    //@{
    NsBool GetIsExpanded() const;
    void SetIsExpanded(NsBool isExpanded);
    //@}

    /// Occurs when the content window of an Expander control closes and only the Header is visible
    UIElement::RoutedEvent_<RoutedEventHandler> Collapsed();

    /// Occurs when the content window of an Expander control opens to display both its header
    /// and content
    UIElement::RoutedEvent_<RoutedEventHandler> Expanded();

    /// Dependency properties
    //@{
    static const DependencyProperty* ExpandDirectionProperty;
    static const DependencyProperty* IsExpandedProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* CollapsedEvent;
    static const RoutedEvent* ExpandedEvent;
    //@}
    
protected:
    virtual void OnCollapsed();
    virtual void OnExpanded();
    
    /// From Control
    //@{
    void UpdateVisualStates();
    //@}
    
    /// From UIElement
    //@{
    //AutomationPeer OnCreateAutomationPeer();
    //@}
    
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    NS_DECLARE_REFLECTION(Expander, HeaderedContentControl)
};

}
}


#endif
