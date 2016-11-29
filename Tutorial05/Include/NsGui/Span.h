////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SPAN_H__
#define __GUI_SPAN_H__


#include <Noesis.h>
#include <NsGui/Inline.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Groups other Inline content elements.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Span: public Inline
{
public:
    Span();
    Span(Inline* childInline);
    ~Span();

    /// Gets a collection containing the top-level Inline elements that comprise the Span's contents
    InlineCollection* GetInlines() const;

protected:
    void OnInit();

private:
    void EnsureInlines();
    void OnInlinesChanged(Core::BaseComponent* sender, const NotifyCollectionChangedEventArgs& e);

private:
    Ptr<InlineCollection> mInlines;

    NS_DECLARE_REFLECTION(Span, Inline)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
