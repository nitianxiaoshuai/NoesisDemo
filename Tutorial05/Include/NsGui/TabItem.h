////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TABITEM_H__
#define __GUI_TABITEM_H__


#include <Noesis.h>
#include <NsGui/HeaderedContentControl.h>


namespace Noesis
{
namespace Gui
{

// Forward declaration
enum Dock;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a selectable item inside a TabControl.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.tabitem.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TabItem: public HeaderedContentControl
{
public:
    /// Constructor
    TabItem();

    /// Gets or sets a value that indicates whether the TabItem is selected
    //@{
    NsBool GetIsSelected() const;
    void SetIsSelected(NsBool isSelected);
    //@}

    /// Gets the tab strip placement
    Dock GetTabStripPlacement() const;

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* IsSelectedProperty;
    static const DependencyProperty* TabStripPlacementProperty;
    //@}

protected:
    /// Called to indicate that the IsSelected property has changed to true
    virtual void OnSelected(const RoutedEventArgs& args);

    /// Called to indicate that the IsSelected property has changed to false
    virtual void OnUnselected(const RoutedEventArgs& args);

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnPreviewGotKeyboardFocus(const KeyboardFocusChangedEventArgs& e);
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    //@}
    
    /// From Control
    //@{
    void UpdateVisualStates();
    //@}

    NS_DECLARE_REFLECTION(TabItem, HeaderedContentControl)
};

}
}


#endif
