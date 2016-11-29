////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INLINE_H__
#define __GUI_INLINE_H__


#include <Noesis.h>
#include <NsGui/TextElement.h>
#include <NsCore/ReflectionDeclare.h>


NS_CFORWARD(Gui, Inline)
NS_SFORWARD(Gui, NotifyCollectionChangedEventArgs)


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::Inline> InlineCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An abstract class that provides a base for all inline flow content elements.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Inline: public TextElement
{
public:
    Inline();

    /// A collection of Inlines containing this one in its sequential tree. May return null if an
    /// element is not inserted into any tree.
    InlineCollection* GetSiblingInlines() const;

    /// Returns an Inline immediately preceding this one on the same level of siblings
    Inline* GetPreviousInline() const;

    /// Returns an Inline immediately following this one on the same level of siblings
    Inline* GetNextInline() const;

private:
    static void UpdateInlines(InlineCollection* inlines, const NotifyCollectionChangedEventArgs& e);
private:
    friend class TextBlock;
    friend class Span;

    InlineCollection* mSiblingInlines;
    Inline* mPreviousInline;
    Inline* mNextInline;

    NS_DECLARE_REFLECTION(Inline, TextElement)
};

}
}


#endif
