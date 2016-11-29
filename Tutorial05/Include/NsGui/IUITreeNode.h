////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IUITREENODE_H__
#define __GUI_IUITREENODE_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IUITreeNodeTypes.h>

namespace Noesis
{

/// Forward declarations
//@{
namespace Core
{
class BaseComponent;
}
namespace Gui
{
NS_INTERFACE IResourceKey;
class FrameworkElement;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IUITreeNode. Represents nodes in a UI tree.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IUITreeNode: public Core::Interface
{
    /// Gets or sets node parent
    //@{
    virtual IUITreeNode* GetNodeParent() const = 0;
    virtual void SetNodeParent(IUITreeNode* parent) = 0;
    //@}

    /// Looks for a UI resource upwards in the tree
    /// \return Unset value if resource is not found
    virtual Core::BaseComponent* FindNodeResource(IResourceKey* key,
        NsBool fullElementSearch) const = 0;

    /// Looks for a named node upwards in the tree
    /// \return Null if node is not found
    virtual Core::BaseComponent* FindNodeName(const NsChar* name) const = 0;
    
    /// Looks for a named node upwards in the tree, returning also the scope in which it was found
    /// \return Null in both fields if node is not found
    virtual ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IUITreeNode, Core::Interface)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper function that finds the first FrameworkElement ancestor for the given UI tree node
NS_GUI_CORE_API FrameworkElement* FindTreeElement(IUITreeNode* node);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper function to obtain the root of the UI Tree from the specified node
NS_GUI_CORE_API IUITreeNode* GetNodeRoot(IUITreeNode* node);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper functions to connect/disconnect nodes to/from the UI tree
//@{
NS_GUI_CORE_API void ConnectNode(IUITreeNode* node, const IUITreeNode* parent);
NS_GUI_CORE_API void DisconnectNode(IUITreeNode* node, const IUITreeNode* parent);
//@}

}
}

#endif