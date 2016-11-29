////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMBOBOXITEM_H__
#define __GUI_COMBOBOXITEM_H__


#include <Noesis.h>
#include <NsGui/ListBoxItem.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements a selectable item inside a ComboBox. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.comboboxitem.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ComboBoxItem: public ListBoxItem
{
public:
    ComboBoxItem();
    
    /// Gets a value that indicates whether the item is highlighted.
    NsBool GetIsHighlighted() const;
    
    /// Accesible from ComboBox
    void SetHighlighted(NsBool value);
    
public:
    static const DependencyProperty* IsHighlightedProperty;

protected:
    /// From UIElement
    //@{
    void OnMouseEnter(const MouseEventArgs& e);
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e);
    //@}
    
    /// From ListBoxItem
    //@{
    void OnSelected(const RoutedEventArgs& e);
    const Core::TypeClass* GetOwnerType() const;
    //@}

    NS_DECLARE_REFLECTION(ComboBoxItem, ListBoxItem)
};

}
}

#endif