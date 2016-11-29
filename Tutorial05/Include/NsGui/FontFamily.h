////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FONTFAMILY_H__
#define __GUI_FONTFAMILY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Enums.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/String.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a family of related fonts.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FontFamily: public Core::BaseComponent
{
public:
    FontFamily();
    FontFamily(const NsChar* source);
    FontFamily(const NsChar* baseUri, const NsChar* source);
    ~FontFamily();

    /// Gets the resource identifier that is used to resolve a font family name
    const NsChar* GetBaseUri() const;

    /// Gets font family name that is used to construct the FontFamily object
    const NsChar* GetSource() const;

    /// Gets FontFamily name
    // TODO: return a collection of family names
    const NsChar* GetName() const;

private:
    friend class UISystem;
    void EnsureName();

private:
    NsString mBaseUri;
    NsString mSource;
    NsString mName;

    NS_DECLARE_REFLECTION(FontFamily, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
