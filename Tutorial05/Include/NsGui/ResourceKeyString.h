////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1215]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RESOURCEKEYSTRING_H__
#define __GUI_RESOURCEKEYSTRING_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/String.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IResourceKey.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A string being used as a resource dictionary key.
/// Example:
///     <ResourceDictionary>
///         <SolidColorBrush x:Key="DisabledForegroundBrush" Color="Black"/>
///     </ResourceDictionary>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ResourceKeyString: public Core::BaseComponent, public IResourceKey
{
public:
    ResourceKeyString();
    ~ResourceKeyString();
    
    // Creates a ResourceKeyString with the string passed as parameter
    static Ptr<ResourceKeyString> Create(const NsChar* str);

    /// Safe version of Create function that could return null
    static Ptr<ResourceKeyString> TryCreate(const NsChar* str);
    
    // Converter helper
    static Ptr<ResourceKeyString> Parse(const NsChar* str);
    static NsBool TryParse(const NsChar*, Ptr<BaseComponent>& result);

    /// Gets the resource key string
    const NsChar* Get() const;

    /// From IResourceKey
    //@{
    using BaseComponent::Equals;
    NsBool Equals(const IResourceKey* resourceKey) const;
    NsBool IsLessThan(const IResourceKey* resourceKey) const;
    NsString GetStr() const;
    //@}

protected:
    /// From BaseRefCounted
    //@{
    NsInt32 OnDestroy() const;
    //@}

private:
    const NsString* mString;

    NS_DECLARE_REFLECTION(ResourceKeyString, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif