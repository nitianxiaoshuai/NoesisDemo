////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FORMATTEDTEXT_H__
#define __GUI_FORMATTEDTEXT_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Freezable.h>
#include <NsGui/IRenderProxyCreator.h>
#include <NsGui/Enums.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsCore/String.h>
#include <NsCore/Vector.h>
#include <NsCore/Set.h>
#include <NsCore/NSTLPoolAllocator.h>
#include <NsDrawing/Rect.h>


NS_CFORWARD(Gui, Inline)
NS_CFORWARD(Gui, Brush)
NS_CFORWARD(Gui, FontFamily)
NS_CFORWARD(Gui, Font)
NS_SFORWARD(Drawing, TextRun)
NS_IFORWARD(Drawing, IVGLFontFace)
NS_IFORWARD(Drawing, IVGLTextLayout)


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::Inline> InlineCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// FormattedText. Draws an ellipse.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FormattedText: public Core::BaseComponent, public IRenderProxyCreator
{
public:
    /// Constructor
    FormattedText();

    /// Destructor
    ~FormattedText();

    void BuildTextRuns(const NsChar* text, InlineCollection* inlines, FontFamily* fontFamily,
        FontWeight fontWeight, FontStretch fontStretch, FontStyle fontStyle, NsFloat32 fontSize,
        NsFloat32 strokeThickness, Brush* background, Brush* foreground, Brush* stroke);

    Drawing::Size Measure(TextAlignment alignment, TextWrapping wrapping, TextTrimming trimming,
        NsFloat32 maxWidth, NsFloat32 maxHeight);

    void Layout(TextAlignment alignment, TextWrapping wrapping, TextTrimming trimming,
        NsFloat32 maxWidth, NsFloat32 maxHeight);
    void ResetLayout();

    Drawing::Rect GetBounds() const;
    void GetGlyphPosition(NsSize chIndex, NsBool afterChar, NsFloat32& x, NsFloat32& y) const;

    NsBool IsEmpty() const;

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UnregisterRenderer(ViewId viewId);
    //@}

private:
    friend class TextBlock;
    friend class TextContainer;

    void AddRuns(InlineCollection* inlines, FontFamily* fontFamily, FontWeight fontWeight,
        FontStretch fontStretch, FontStyle fontStyle, Drawing::IVGLFontFace* fontFace,
        NsFloat32 fontSize, NsFloat32 strokeThickness, NsInt32 backgroundIndex,
        NsInt32 foregroundIndex, NsInt32 strokeIndex);
    void AddRun(const NsChar* text, Drawing::IVGLFontFace* fontFace, NsFloat32 fontSize,
        NsFloat32 strokeThickness, NsInt32 foregroundIndex, NsInt32 strokeIndex,
        NsInt32 backgroundIndex);
    Drawing::IVGLFontFace* AddFontFace(FontFamily* family, FontWeight weight, FontStretch stretch,
        FontStyle style);
    Drawing::IVGLFontFace* InlineFace(Inline* inl, Drawing::IVGLFontFace* currentFace,
        FontFamily*& family, FontWeight& weight, FontStretch& stretch, FontStyle& style);
    NsFloat32 InlineSize(NsFloat32 currentSize, Inline* inl, const DependencyProperty* dp);
    NsInt32 InlineBrushIndex(NsInt32 currentBrushIndex, Inline* inl, const DependencyProperty* dp);
    NsInt32 BrushIndex(Brush* brush);

    void UnregisterBrushes();

    void RegisterBrush(Brush* brush);
    void UnregisterBrush(Brush* brush);
    void OnBrushChanged(Freezable* sender, FreezableEventReason reason);

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Brushes,
        UpdateFlags_TextLayout
    };

    NsVector<Drawing::TextRun> mTextRuns;
    NsVector<Ptr<Drawing::IVGLFontFace> > mFontFaces;
    NsVector<Ptr<Brush> > mBrushes;

    typedef NsSet<Brush*, Core::nstl::less<Brush*>, Core::nstl::PoolAllocator> RegisteredBrushes;
    RegisteredBrushes mRegisteredBrushes;

    Ptr<Drawing::IVGLTextLayout> mTextLayout;


    NS_DECLARE_REFLECTION(FormattedText, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
