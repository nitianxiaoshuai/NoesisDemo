////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STYLE_H__
#define __GUI_STYLE_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class BaseSetter;
class BaseTrigger;
class ResourceDictionary;
template<class T> class TypedCollection;
class TriggerCollection;
class ResourceKeyType;
class FrameworkElement;
//@}

typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Enables the sharing of properties, resources, and event handlers between instances of a type.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Style: public Core::BaseComponent, public IComponentInitializer,
    public IUITreeNode
{
public:
    Style();
    ~Style();

    /// Gets or sets the type for which this style is intended
    //@{
    ResourceKeyType* GetTargetType() const;
    void SetTargetType(ResourceKeyType* targetType);
    //@}

    /// Gets or sets a defined style that is the basis of the current style
    //@{
    Style* GetBasedOn() const;
    void SetBasedOn(Style* style);
    //@}

    /// Gets or sets the collection of resources that can be used within the scope of this style
    //@{
    ResourceDictionary* GetResources() const;
    void SetResources(ResourceDictionary* resources);
    //@}

    /// Gets a collection of Setter and EventSetter objects
    BaseSetterCollection* GetSetters() const;

    /// Gets a collection of TriggerBase objects that apply property values based on specified
    /// conditions
    TriggerCollection* GetTriggers() const;

    /// From IComponentInitializer
    //@{
    NsBool IsInitialized() const;
    void Init();
    //@}

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

private:
    void FreezeValues();
    void FreezeValues(BaseSetterCollection* setters);
    void EnsureResources() const;
    void EnsureSetters() const;
    void EnsureTriggers() const;

    void CheckTargetType(const Core::TypeClass* elementType) const;

    void Seal();
    void CheckBasedOnType() const;
    void CheckBasedOnCircularity() const;

private:
    friend struct BaseStyleTriggerProvider;
    friend struct BaseStyleSetterProvider;
    friend class DynamicResourceExpression;
    friend class StaticResourceExpression;
    friend class FrameworkElement;

    NsBool mIsInitialized;
    NsBool mIsSealed;
    IUITreeNode* mOwner;
    // TODO [srodriguez] For now the x:Type extension returns a IResourceKey
    // const Core::TypeClass* mTargetType;
    Ptr<ResourceKeyType> mTargetType;
    Ptr<Style> mBasedOn;
    mutable Ptr<ResourceDictionary> mResources;
    mutable Ptr<BaseSetterCollection> mSetters;
    mutable Ptr<TriggerCollection> mTriggers;

    NS_DECLARE_REFLECTION(Style, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}

#endif
