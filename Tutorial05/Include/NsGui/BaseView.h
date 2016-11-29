////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEVIEW_H__
#define __GUI_BASEVIEW_H__


#include <Noesis.h>
#include <NsGui/ControlsApi.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class ListViewItem;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for views that define the appearance of data in a ListView control.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.viewbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CONTROLS_API BaseView: public DependencyObject, public IUITreeNode
{
public:
    BaseView();
    ~BaseView();
    
    /// Removes all bindings and styling that are set for an item
    virtual void ClearItem(ListViewItem* item);
    
    /// Prepares an item in the view for display, by setting bindings and styles
    virtual void PrepareItem(ListViewItem* item);
    
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
    
    NS_DECLARE_REFLECTION(BaseView, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif