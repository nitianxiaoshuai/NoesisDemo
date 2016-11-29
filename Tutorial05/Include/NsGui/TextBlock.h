////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TEXTBLOCK_H__
#define __GUI_TEXTBLOCK_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/Enums.h>

#include <EASTL/fixed_string.h>


namespace Noesis
{
// Forward declarations
//@{
namespace Gui
{
class FormattedText;
class Brush;
class FontFamily;
class Inline;
template<class T> class TypedCollection;
struct NotifyCollectionChangedEventArgs;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Gui::TypedCollection<Noesis::Gui::Inline> InlineCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a lightweight control for displaying small amounts of text content.
///
/// Example:
///
/// .. code-block:: xml
///
///     <Grid
///       xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///       xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
///         <StackPanel HorizontalAlignment="Center" VerticalAlignment="Center">
///             <TextBlock Text="Normal" FontStyle="Normal" FontWeight="Normal"/>
///             <TextBlock Text="Italic" FontStyle="Italic" FontWeight="Normal"/>
///             <TextBlock Text="Bold" FontStyle="Normal" FontWeight="Bold"/>
///             <TextBlock Text="Bold Italic" FontStyle="Italic" FontWeight="Bold"/>
///         </StackPanel>
///     </Grid>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.textblock.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TextBlock: public FrameworkElement
{
public:
    /// Default constructor
    TextBlock();

    /// Constructor
    TextBlock(const NsChar* text);

    /// Destructor
    ~TextBlock();

    /// Gets or sets the Brush used to fill the background of content area.
    //@{
    Brush* GetBackground() const;
    void SetBackground(Brush* brush);
    //@}

    /// Gets or sets the preferred top-level font family for the TextBlock.
    //@{
    FontFamily* GetFontFamily() const;
    void SetFontFamily(FontFamily* fontFamily);
    //@}
    
    /// Gets or sets the top-level font size for the TextBlock.
    //@{
    NsFloat32 GetFontSize() const;
    void SetFontSize(NsFloat32 size);
    //@}

    /// Gets or sets the top-level font stretch for the TextBlock.
    //@{
    FontStretch GetFontStretch() const;
    void SetFontStretch(FontStretch stretch);
    //@}

    /// Gets or sets the top-level font style for the TextBlock.
    //@{
    FontStyle GetFontStyle() const;
    void SetFontStyle(FontStyle style);
    //@}

    /// Gets or sets the top-level font weight for the TextBlock.
    //@{
    FontWeight GetFontWeight() const;
    void SetFontWeight(FontWeight weight);
    //@}
    
    /// Gets or sets the Brush to apply to the text contents of the TextBlock.
    //@{
    Brush* GetForeground() const;
    void SetForeground(Brush* foreground);
    //@}

    /// Gets an InlineCollection containing the top-level Inline elements that comprise the
    /// contents of the TextBlock
    InlineCollection* GetInlines() const;
    
    /// Gets or sets the height of each line of content
    //@{
    NsFloat32 GetLineHeight() const;
    void SetLineHeight(NsFloat32 value);
    //@}
    
    /// Gets or sets the padding inside a control
    //@{
    const Drawing::Thickness& GetPadding() const;
    void SetPadding(const Drawing::Thickness& padding);
    //@}

    /// Gets or sets the Brush used to stroke the text
    //@{
    Brush* GetStroke() const;
    void SetStroke(Brush* stroke);
    //@}

    /// Gets or sets the width (in pixels) of the text stroke
    //@{
    NsFloat32 GetStrokeThickness() const;
    void SetStrokeThickness(NsFloat32 strokeThickness);
    //@}

    /// Gets or sets text alignment
    //@{
    Gui::TextAlignment GetTextAlignment() const;
    void SetTextAlignment(Gui::TextAlignment textAlign);
    //@}

    /// Gets or sets text string
    //@{
    const NsChar* GetText() const;
    void SetText(const NsChar* text);
    //@}

    /// Gets or sets the text trimming behavior to employ when content overflows the content area
    //@{
    Gui::TextTrimming GetTextTrimming() const;
    void SetTextTrimming(Gui::TextTrimming trimming);
    //@}
    
    /// Gets or sets text wrapping
    //@{
    Gui::TextWrapping GetTextWrapping() const;
    void SetTextWrapping(Gui::TextWrapping textWrap);
    //@}

    /// From BaseObject
    //@{
    NsString ToString() const;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* BackgroundProperty;
    static const DependencyProperty* FontFamilyProperty;
    static const DependencyProperty* FontSizeProperty;
    static const DependencyProperty* FontStretchProperty;
    static const DependencyProperty* FontStyleProperty;
    static const DependencyProperty* FontWeightProperty;
    static const DependencyProperty* ForegroundProperty;
    static const DependencyProperty* LineHeightProperty;
    static const DependencyProperty* PaddingProperty;
    static const DependencyProperty* StrokeProperty;
    static const DependencyProperty* StrokeThicknessProperty;
    static const DependencyProperty* TextAlignmentProperty;
    static const DependencyProperty* TextProperty;
    static const DependencyProperty* TextTrimmingProperty;
    static const DependencyProperty* TextWrappingProperty;
    //@}

protected:
    Ptr<FormattedText> mFormattedText;

protected:
    void UpdateTextRuns();
    void UpdateTextLayout(const Drawing::Size& finalSize);

    void InvalidateTextMeasure();
    void InvalidateTextRuns();
    void InvalidateTextLayout();

    /// From DependencyObject
    //@{
    void OnPostInit();
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnRender(DrawingContext* context);
    //@}

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    void OnTextChanged(const NsChar* newText);
    void OnInlinesChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);

    void EnsureInlines();
    void EnsureFormattedText();

private:
    Ptr<InlineCollection> mInlines;
    Drawing::Size mPreviousConstraint;
    NsUInt32 mTextFlags;

    NS_DECLARE_REFLECTION(TextBlock, FrameworkElement)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
