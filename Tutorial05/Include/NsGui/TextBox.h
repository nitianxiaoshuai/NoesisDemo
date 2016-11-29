////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TEXTBOX_H__
#define __GUI_TEXTBOX_H__


#include <Noesis.h>
#include <NsGui/BaseTextBox.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/Vector.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class ScrollViewer;
class TextBoxTextContainer;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that can be used to display or edit unformatted text.
/// (Mixed WPF definitions of TextBoxBase and TextBox).
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.textbox.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TextBox: public BaseTextBox
{
public:
    /// Constructor
    TextBox();
    
    /// Destructor
    ~TextBox();

    /// Gets or sets the insertion position index of the caret
    //@{
    NsInt32 GetCaretIndex() const;
    void SetCaretIndex(NsInt32 caretIndex);
    //@}

    /// Gets or sets the maximum number of characters that can be manually entered into the text box
    //@{
    NsInt32 GetMaxLength() const;
    void SetMaxLength(NsInt32 length);
    //@}
    
    /// Gets or sets the maximum number of visible lines.
    //@{
    NsInt32 GetMaxLines() const;
    void SetMaxLines(NsInt32 lines);
    //@}
    
    /// Gets or sets the minimum number of visible lines. 
    //@{
    NsInt32 GetMinLines() const;
    void SetMinLines(NsInt32 lines);
    //@}

    /// Gets or sets the content of the current selection in the text box
    /// \remarks Returned string must be copied becuase it will be invalidated next time you
    /// interact with the text box
    /// \prop
    //@{
    const NsChar* GetSelectedText() const;
    void SetSelectedText(const NsChar* text);
    //@}

    /// Gets or sets a value indicating the number of characters in the current selection in the
    /// text box
    /// \prop
    //@{
    NsInt32 GetSelectionLength() const;
    void SetSelectionLength(NsInt32 len);
    //@}

    /// Gets or sets a character index for the beginning of the current selection
    /// \prop
    //@{
    NsInt32 GetSelectionStart() const;
    void SetSelectionStart(NsInt32 pos);
    //@}

    /// Selects all text
    void SelectAll();

    /// Gets or sets the horizontal alignment of the contents of the text box
    //@{
    TextAlignment GetTextAlignment() const;
    void SetTextAlignment(TextAlignment textAlign);
    //@}
    
    /// Gets or sets the text contents of the text box. 
    //@{
    const NsChar* GetText() const;
    void SetText(const NsChar* text);
    //@}
    
    /// Gets or sets how the text box should wrap text.
    //@{
    TextWrapping GetTextWrapping() const;
    void SetTextWrapping(TextWrapping textWrap);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* MaxLengthProperty;
    static const DependencyProperty* MaxLinesProperty;
    static const DependencyProperty* MinLinesProperty;
    static const DependencyProperty* TextAlignmentProperty;
    static const DependencyProperty* TextProperty;
    static const DependencyProperty* TextWrappingProperty;
    //@}
    
protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From FrameworkElement
    //@{
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
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
    //@}

    /// From BaseTextBox
    //@{
    void OnCaretBrushChanged(Brush* oldBrush, Brush* newBrush);
    void OnSelectionBrushChanged(Brush* oldBrush, Brush* newBrush);
    void OnSelectionOpacityChanged(NsFloat32 oldOpacity, NsFloat32 newOpacity);
    ScrollViewer* GetScrollViewer() const;
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

private:
    friend class ComboBox;
    void ArrangeTextContainer(NsFloat32 arrangeWidth);

    void CopyToClipboard(const NsString& text, NsSize begin, NsSize end);

    void UpdateContentHostHeight();
    void UpdateContentHostHeight(NsFloat32 padding);

    /// Command management
    //@{
    static void StaticOnCanExecuteCopy(Core::BaseComponent* target,
        const CanExecuteRoutedEventArgs& args);
    static void StaticOnExecutedCopy(Core::BaseComponent* target,
        const ExecutedRoutedEventArgs& args);
    static void StaticOnCanExecuteCut(Core::BaseComponent* target,
        const CanExecuteRoutedEventArgs& args);
    static void StaticOnExecutedCut(Core::BaseComponent* target,
        const ExecutedRoutedEventArgs& args);
    static void StaticOnCanExecutePaste(Core::BaseComponent* target,
        const CanExecuteRoutedEventArgs& args);
    static void StaticOnExecutedPaste(Core::BaseComponent* target,
        const ExecutedRoutedEventArgs& args);
    static void StaticOnCanExecuteSelectAll(Core::BaseComponent* target,
        const CanExecuteRoutedEventArgs& args);
    static void StaticOnExecutedSelectAll(Core::BaseComponent* target,
        const ExecutedRoutedEventArgs& args);
    //@}

    void OnCanExecuteCopy(const CanExecuteRoutedEventArgs& args);
    void OnExecuteCopy(const ExecutedRoutedEventArgs& args);
    void OnCanExecuteCut(const CanExecuteRoutedEventArgs& args);
    void OnExecuteCut(const ExecutedRoutedEventArgs& args);
    void OnCanExecutePaste(const CanExecuteRoutedEventArgs& args);
    void OnExecutePaste(const ExecutedRoutedEventArgs& args);
    void OnCanExecuteSelectAll(const CanExecuteRoutedEventArgs& args);
    void OnExecuteSelectAll(const ExecutedRoutedEventArgs& args);

    static NsBool StaticCoerceHorizontalScrollBarVisibility(const DependencyObject* object,
        const void* value, void* coercedValue);

private:
    Ptr<FrameworkElement> mContentHost;
    Ptr<TextBoxTextContainer> mTextContainer;

    union
    {
        mutable struct
        {
            NsBool mouseDown:1;
            NsBool updateContentHostMinMax:1;
        } mFlags;

        // To quickly set all flags to 0
        mutable NsUInt8 mAllFlags;
    };

    NS_DECLARE_REFLECTION(TextBox, BaseTextBox)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
