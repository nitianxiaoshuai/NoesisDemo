////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PASSWORDBOX_H__
#define __GUI_PASSWORDBOX_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Control.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
class PasswordBoxTextContainer;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control designed for entering and handling passwords.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.passwordbox.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API PasswordBox: public Control
{
public:
    PasswordBox();
    ~PasswordBox();

    /// Gets or sets the brush that is used to paint the caret of the text box (WPF 4.0)
    //@{
    Brush* GetCaretBrush() const;
    void SetCaretBrush(Brush* brush);
    //@}

    /// Gets or sets the maximum length for passwords to be handled by this PasswordBox. 
    //@{
    NsInt GetMaxLength() const;
    void SetMaxLength(NsInt length);
    //@}

    /// Gets or sets the masking character for the PasswordBox.
    //@{
    NsChar GetPasswordChar() const;
    void SetPasswordChar(NsChar value);
    //@}

    /// Gets or sets the password currently held by the PasswordBox.
    //@{
    const NsChar* GetPassword() const;
    void SetPassword(const NsChar* password);
    //@}

    /// Gets or sets the brush that highlights selected text
    //@{
    Brush* GetSelectionBrush() const;
    void SetSelectionBrush(Brush* selectionBrush);
    //@}

    /// Gets or sets the opacity of the SelectionBrush
    /// \remarks If SelectionOpacity is set to 0, the SelectionBrush is transparent and is not
    /// visible. If SelectionOpacity is set to 1.0 or greater, the SelectionBrush is opaque and the
    /// selected text is not visible.
    //@{
    NsFloat32 GetSelectionOpacity() const;
    void SetSelectionOpacity(NsFloat32 selectionOpacity);
    //@}

    /// Occurs when password changes
    UIElement::RoutedEvent_<RoutedEventHandler> PasswordChanged();

public:
    static const DependencyProperty* CaretBrushProperty;
    static const DependencyProperty* MaxLengthProperty;
    static const DependencyProperty* PasswordCharProperty;
    static const DependencyProperty* SelectionBrushProperty;
    static const DependencyProperty* SelectionOpacityProperty;

    static const RoutedEvent* PasswordChangedEvent;

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnKeyDown(const KeyEventArgs& e);
    void OnKeyUp(const KeyEventArgs& e);
    void OnTextInput(const TextCompositionEventArgs& e);
    void OnGotKeyboardFocus(const KeyboardFocusChangedEventArgs& e);
    void OnLostKeyboardFocus(const KeyboardFocusChangedEventArgs& e);
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e);
    void OnMouseMove(const MouseEventArgs& e);
    //@}

    /// From FrameworkElement
    //@{
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    //@}

    /// From Control
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    void OnFontFamilyChanged(FontFamily* fontFamily);
    void OnFontSizeChanged(NsFloat32 fontSize);
    void OnFontStretchChanged(FontStretch fontStretch);
    void OnFontStyleChanged(FontStyle fontStyle);
    void OnFontWeightChanged(FontWeight fontWeight);
    void OnMouseDoubleClick(const MouseButtonEventArgs& e);
    void UpdateVisualStates();
    //@}

private:
    Ptr<FrameworkElement> mContentHost;
    Ptr<PasswordBoxTextContainer> mTextContainer;

    NsString mPassword;

    union
    {
        mutable struct
        {
            NsBool mouseDown:1;
        } mFlags;

        // To quickly set all flags to 0
        mutable NsUInt8 mAllFlags;
    };

    NS_DECLARE_REFLECTION(PasswordBox, Control)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
    