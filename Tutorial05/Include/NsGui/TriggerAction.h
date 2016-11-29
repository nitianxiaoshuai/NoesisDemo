////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRIGGERACTION_H__
#define __GUI_TRIGGERACTION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{
namespace Gui
{
// Forward declarations
//@{
class FrameworkElement;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes an action to perform for a trigger.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.triggeraction.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TriggerAction: public DependencyObject, public IUITreeNode
{
public:
    TriggerAction();
    virtual ~TriggerAction() = 0;

    /// Performs the action over the supplied element
    virtual void Invoke(FrameworkElement* target, FrameworkElement* nameScope = 0) = 0;

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue);
    //@}

private:
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(TriggerAction, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif