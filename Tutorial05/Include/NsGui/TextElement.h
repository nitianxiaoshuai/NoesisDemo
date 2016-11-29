////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TEXTELEMENT_H__
#define __GUI_TEXTELEMENT_H__


#include <Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Enums.h>
#include <NsCore/String.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyObject;
class DependencyProperty;
class UIElement;
class Brush;
class FontFamily;
class Collection;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines text attached properties.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.documents.textelement.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TextElement: public DependencyObject
{
public:
    /// Gets or sets the Brush used to fill the background of the content area
    //@{
    Brush* GetBackground() const;
    void SetBackground(Brush* background);
    //@}

    /// Gets or sets the preferred top-level font family for the content of the element
    //@{
    FontFamily* GetFontFamily() const;
    void SetFontFamily(FontFamily* family);
    //@}

    /// Gets or sets the font size for the content of the element
    //@{
    NsFloat32 GetFontSize() const;
    void SetFontSize(NsFloat32 size);
    //@}

    /// Gets or sets the font stretct for the content of the element
    //@{
    FontStretch GetFontStretch() const;
    void SetFontStretch(FontStretch stretch);
    //@}

    /// Gets or sets the font style for the content of the element
    //@{
    FontStyle GetFontStyle() const;
    void SetFontStyle(FontStyle style);
    //@}

    /// Gets or sets the top-level font weight for the content of the element
    //@{
    FontWeight GetFontWeight() const;
    void SetFontWeight(FontWeight weight);
    //@}

    /// Gets or sets the Brush to apply to the content of the element
    //@{
    Brush* GetForeground() const;
    void SetForeground(Brush* foreground);
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

    // As ATTACHED PROPERTIES

    /// Gets or sets the Brush used to fill the background of the content area
    //@{
    static Brush* GetBackground(const DependencyObject* element);
    static void SetBackground(DependencyObject* element, Brush* background);
    //@}

    /// Gets or sets the preferred top-level font family for the content of the element
    //@{
    static FontFamily* GetFontFamily(const DependencyObject* element);
    static void SetFontFamily(DependencyObject* element, FontFamily* family);
    //@}

    /// Gets or sets the font size for the content of the element
    //@{
    static NsFloat32 GetFontSize(const DependencyObject* element);
    static void SetFontSize(DependencyObject* element, NsFloat32 size);
    //@}

    /// Gets or sets the font stretch for the content of the element
    //@{
    static FontStretch GetFontStretch(const DependencyObject* element);
    static void SetFontStretch(DependencyObject* element, FontStretch stretch);
    //@}

    /// Gets or sets the font style for the content of the element
    //@{
    static FontStyle GetFontStyle(const DependencyObject* element);
    static void SetFontStyle(DependencyObject* element, FontStyle style);
    //@}

    /// Gets or sets the top-level font weight for the content of the element
    //@{
    static FontWeight GetFontWeight(const DependencyObject* element);
    static void SetFontWeight(DependencyObject* element, FontWeight weight);
    //@}

    /// Gets or sets the Brush to apply to the content of the element
    //@{
    static Brush* GetForeground(const DependencyObject* element);
    static void SetForeground(DependencyObject* element, Brush* foreground);
    //@}

    /// Gets or sets the Brush used to stroke the text
    //@{
    static Brush* GetStroke(const DependencyObject* element);
    static void SetStroke(DependencyObject* element, Brush* stroke);
    //@}

    /// Gets or sets the width (in pixels) of the text stroke
    //@{
    static NsFloat32 GetStrokeThickness(const DependencyObject* element);
    static void SetStrokeThickness(DependencyObject* element, NsFloat32 strokeThickness);
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
    static const DependencyProperty* StrokeProperty;
    static const DependencyProperty* StrokeThicknessProperty;
    //@}

private:
    static NsBool ValidateFontSize(const void* value);

    NS_DECLARE_REFLECTION(TextElement, DependencyObject)
};

}
}

#endif
