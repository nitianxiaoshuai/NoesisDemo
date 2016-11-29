////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DATATEMPLATESELECTOR_H__
#define __GUI_DATATEMPLATESELECTOR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DataTemplate;
class DependencyObject;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a way to choose a DataTemplate based on the data object and the data-bound element.
///
/// https://msdn.microsoft.com/en-us/library/system.windows.controls.datatemplateselector.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DataTemplateSelector: public Core::BaseComponent, public IUITreeNode
{
public:
    DataTemplateSelector();
    virtual ~DataTemplateSelector() = 0;

    /// When overridden in a derived class, returns a DataTemplate based on custom logic
    virtual DataTemplate* SelectTemplate(Core::BaseComponent* item,
        DependencyObject* container) = 0;

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

private:
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(DataTemplateSelector, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
