
////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RUN_H__
#define __GUI_RUN_H__


#include <Noesis.h>
#include <NsGui/Inline.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An inline-level flow content element intended to contain a run of formatted or unformatted text.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Run : public Inline
{
public:
    Run();
    Run(const NsChar* text);

    /// Gets or sets the unformatted text contents of this text Run.
    //@{
    const NsChar* GetText() const;
    void SetText(const NsChar* text);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* TextProperty;
    //@}

    NS_DECLARE_REFLECTION(Run, Inline)
};

}
}


#endif
