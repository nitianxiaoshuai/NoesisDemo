////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONDITION_H__
#define __GUI_CONDITION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/String.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class BaseBinding;
class DependencyProperty;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a condition for the MultiTrigger and the MultiDataTrigger, which apply changes to
/// property values based on a set of conditions.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.condition.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Condition: public Core::BaseComponent, public IComponentInitializer,
    public IUITreeNode
{
public:
    Condition();
    ~Condition();

    /// Gets or sets the binding that produces the property value of the data object.
    //@{
    BaseBinding* GetBinding() const;
    void SetBinding(BaseBinding* binding);
    //@}

    /// Gets or sets the property of the condition. This is only applicable to MultiTrigger objects
    //@{
    const DependencyProperty* GetProperty() const;
    void SetProperty(const DependencyProperty* property);
    //@}

    /// Gets or sets the name of the object with the property that causes the associated setters to 
    /// be applied. This is only applicable to MultiTrigger objects. 
    //@{
    const NsChar* GetSourceName() const;
    void SetSourceName(const NsChar* name);
    //@}

    /// Gets or sets the value of the condition.
    //@{
    Core::BaseComponent* GetValue() const;
    void SetValue(Core::BaseComponent* object);
    //@}

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
    void CheckParentForBinding() const;
    void CheckParentForProperty() const;

private:
    friend class MultiTrigger;

    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    Ptr<BaseBinding> mBinding;
    const DependencyProperty* mProperty;
    Ptr<BaseComponent> mValue;
    NsString mSourceName;

    NS_DECLARE_REFLECTION(Condition, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif