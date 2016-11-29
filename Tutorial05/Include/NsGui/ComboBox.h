////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMBOBOX_H__
#define __GUI_COMBOBOX_H__


#include <Noesis.h>
#include <NsGui/Selector.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class TextBox;
class ComboBoxItem;
class Popup;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a selection control with a drop-down list that can be shown or hidden by clicking
/// the arrow on the control. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.combobox.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ComboBox: public Selector
{
public:
    ComboBox();
    ~ComboBox();

    /// Gets or sets a value that indicates whether the drop-down for a combo box is currently open
    //@{
    NsBool GetIsDropDownOpen() const;
    void SetIsDropDownOpen(NsBool value);
    //@}

    /// Gets or sets a value that enables or disables editing of the text in text box of the ComboBox.
    //@{
    NsBool GetIsEditable() const;
    void SetIsEditable(NsBool value);
    //@}

    /// Gets or sets a value that enables selection-only mode, in which the contents of the combo box are selectable but not editable
    //@{
    NsBool GetIsReadOnly() const;
    void SetIsReadOnly(NsBool value);
    //@}

    /// Gets or sets the maximum height for a combo box drop-down.
    //@{
    NsFloat32 GetMaxDropDownHeight() const;
    void SetMaxDropDownHeight(NsFloat32 height);
    //@}
    
    /// Gets the item that is displayed in the selection box
    //@{
    Core::BaseComponent* GetSelectionBoxItem() const;
    //@}

    /// Gets the item template of the selection box content
    //@{
    DataTemplate* GetSelectionBoxItemTemplate() const;
    //@}

    /// Gets or sets whether a ComboBox that is open and displays a drop-down control will remain open when a user clicks the TextBox.
    //@{
    NsBool GetStaysOpenOnEdit() const;
    void SetStaysOpenOnEdit(NsBool value);
    //@}

    /// Gets or sets the text of the currently selected item
    //@{
    const NsChar* GetText() const;
    void SetText(const NsChar* text);
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* IsDropDownOpenProperty;
    static const DependencyProperty* IsEditableProperty;
    static const DependencyProperty* IsReadOnlyProperty;
    static const DependencyProperty* MaxDropDownHeightProperty;
    static const DependencyProperty* SelectionBoxItemProperty;
    //static const DependencyProperty* SelectionBoxItemStringFormatProperty; Not docummented
    static const DependencyProperty* SelectionBoxItemTemplateProperty;
    static const DependencyProperty* StaysOpenOnEditProperty;
    static const DependencyProperty* TextProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnPreviewMouseDown(const MouseButtonEventArgs& e);
    void OnMouseWheel(const MouseWheelEventArgs& e);
    //@}

    /// From FrameworkElement
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    void UpdateVisualStates();
    //@}

    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;
    void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);
    void OnItemTemplateChanged(DataTemplate* oldTemplate, DataTemplate* newTemplate);
    void OnItemTemplateSelectorChanged(DataTemplateSelector* oldSelector,
        DataTemplateSelector* newSelector);
    //@}

    /// From Selector
    //@{
    void OnSelectionChanged(const SelectionChangedEventArgs& e);
    //@}

private:
    void Invalidate();
    void Update();

    void UpdateText(const NsChar* text);
    void UpdateEditableText(const NsChar* text);
    NsString GetSelectedItemText() const;
    void OnEditableTextChanged(Core::BaseComponent* sender, const RoutedEventArgs& e);

    void UpdateSelectionBoxItem();
    void SetSelectionBoxItem(Core::BaseComponent* item);
    void SetSelectionBoxItemTemplate(DataTemplate* itemTemplate);
    DataTemplate* FindItemTemplate(BaseComponent* item);

    void OnIsDropDownChanged(NsBool isDropDown);

    static void StaticIsSelectionActiveChanged(DependencyObject* d,
        const DependencyPropertyChangedEventArgs& e);

    static void StaticOnComboBoxLostMouseCapture(Core::BaseComponent* obj, const EventArgs& e);
    void OnComboBoxLostMouseCapture(const MouseEventArgs& e);

    static void StaticOnComboBoxMouseButtonDown(Core::BaseComponent* obj, const EventArgs& e);
    void OnComboBoxMouseButtonDown(const MouseEventArgs& e);

    static void StaticOnComboBoxPreviewMouseButtonDown(Core::BaseComponent* obj, const EventArgs& e);
    void OnComboBoxPreviewMouseButtonDown(const MouseEventArgs& e);

    static void StaticOnComboBoxGotFocus(Core::BaseComponent* obj, const EventArgs& e);
    void OnComboBoxGotFocus(const RoutedEventArgs& e);

    /// Used by ComboBoxItem implementation
    friend class ComboBoxItem;
    void ItemSelected(ComboBoxItem* lbi);
    void ItemClicked(ComboBoxItem* cbi);
    void ItemEntered(ComboBoxItem* cbi);

private:
    Ptr<TextBox> mEditableTextBox;
    Ptr<ComboBoxItem> mMouseOverElement;

    enum
    {
        NeedsUpdate = Selector::LastFlag * 2,
        UpdatingText = NeedsUpdate * 2,
        UpdatingEditableText = UpdatingText * 2
    };

    NS_DECLARE_REFLECTION(ComboBox, Selector)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif