////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VISUALSTATE_H__
#define __GUI_VISUALSTATE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class Storyboard;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the visual appearance of the control when it is in a specific state.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.visualstate.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API VisualState: public DependencyObject, public IUITreeNode
{
public:
    VisualState();

    /// Gets the name of the VisualState
    //@{
    NsSymbol GetName() const;
    void SetName(NsSymbol name);
    //@}
    
    /// Gets or sets a Storyboard that defines the appearance of the control when it is the state 
    /// that is represented by the VisualState
    //@{
    Storyboard* GetStoryboard() const;
    void SetStoryboard(Storyboard* storyBoard);
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
    /// From DependencyObject
    //@{
    void OnInit();
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue);
    //@}

private:
    NsSymbol mName;
    Ptr<Storyboard> mStoryboard;

    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(VisualState, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif