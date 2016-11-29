////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FRAMEWORKTEMPLATE_H__
#define __GUI_FRAMEWORKTEMPLATE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsCore/Delegate.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/INameScope.h>
#include <NsGui/IUITreeNode.h>

namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class Visual;
class FrameworkElement;
class NameScope;
class ResourceDictionary;
class TriggerCollection;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Enables the instantiation of a tree of elements for a template.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.frameworktemplate.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FrameworkTemplate: public Core::BaseComponent, public IComponentInitializer,
    public INameScope, public IUITreeNode
{
public:
    /// Constructor
    FrameworkTemplate();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~FrameworkTemplate() = 0;

    /// Applies current template to the element specified
    Ptr<FrameworkElement> Apply(FrameworkElement* templatedParent,
        BaseComponent* dataContext) const;

    /// Gets or sets the collection of resources that can be used within the scope of 
    /// this template.
    //@{
    ResourceDictionary* GetResources() const;
    void SetResources(ResourceDictionary* resources);
    //@}

    /// Gets or sets the root node of the template.
    //@{
    Visual* GetVisualTree() const;
    void SetVisualTree(Visual* root);
    //@}

    /// Finds the element associated with the specified name defined within this template
    Core::BaseComponent* FindName(const NsChar* name, FrameworkElement* templatedParent);

    /// Gets template triggers if available
    virtual TriggerCollection* GetAvailableTriggers() const;

    /// From IComponentIntializer
    //@{
    NsBool IsInitialized() const;
    void Init();
    //@}

    /// From INameScope
    //@{
    void RegisterName(const NsChar* name, Core::BaseComponent* object);
    void UnregisterName(const NsChar* name);
    void UpdateName(const NsChar* name, Core::BaseComponent* object);
    INameScope::ChangedDelegate& NameScopeChanged();
    //@}

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

protected:
    virtual void OnInit();
    virtual NsBool IsValidTemplatedParent(FrameworkElement* templatedParent,
        BaseComponent* dataContext) const;

    /// From INameScope
    //@{
    // This function can't be used to look for an element of a template that was applied to a
    // control, users should call FrameworkElement.GetTemplateChild(name) or
    // FrameworkTemplate.FindName(name, templatedParent) instead
    Core::BaseComponent* FindName(const NsChar* name) const;
    //@}

private:
    /// Base classes are non-copyable objects
    //@{
    FrameworkTemplate& operator=(const FrameworkTemplate&);
    //@}

    void EnumNameScope(const NsChar* name, BaseComponent* object, void* context) const;
    void EnsureNamescope() const;
    void EnsureResources() const;

private:
    friend class DynamicResourceExpression;
    friend class FrameworkElement;

    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    mutable Ptr<NameScope> mNameScope;
    mutable Ptr<ResourceDictionary> mResources;
    Ptr<Visual> mVisualTree;

    NS_DECLARE_REFLECTION(FrameworkTemplate, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
