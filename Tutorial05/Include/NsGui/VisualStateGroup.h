////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VISUALSTATEGROUP_H__
#define __GUI_VISUALSTATEGROUP_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/AnimationApi.h>
#include <NsCore/String.h>
#include <NsCore/Map.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
struct VisualStateChangedEventArgs;
class FrameworkElement;
class Storyboard;
class VisualStateManager;
class VisualState;
class VisualTransition;
template<class T> class TypedCollection;
//@}

typedef Noesis::Gui::TypedCollection<Noesis::Gui::VisualState> VisualStateCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::VisualTransition> VisualTransitionCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Contains mutually exclusive VisualState objects and VisualTransition objects that are used
/// to go from one state to another.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.visualstategroup.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API VisualStateGroup: public DependencyObject, public IUITreeNode
{
public:
    VisualStateGroup();
    ~VisualStateGroup();

    /// Gets the name of the VisualStateGroup.
    const NsChar* GetName() const;

    /// Gets the collection of mutually exclusive VisualState objects
    VisualStateCollection* GetStates() const;

    /// Gets the collection of VisualTransition objects
    VisualTransitionCollection* GetTransitions() const;

    /// Gets or the state that is currently active
    //@{
    VisualState* GetCurrentState(FrameworkElement* fe) const;
    void SetCurrentState(FrameworkElement* fe, VisualState* state);
    //@}

    /// Finds a matching state with the same name.
    /// \note name can be null or empty
    VisualState* FindState(NsSymbol name) const;

    VisualTransition* FindTransition(VisualState* from, VisualState* to) const;

    /// Occurs after a control transitions into a different state
    //event EventHandler<VisualStateChangedEventArgs> CurrentStateChanged;
    
    /// Occurs when a control begins transitioning into a different state
    //event EventHandler<VisualStateChangedEventArgs> CurrentStateChanging;

    void UpdateAnimations(FrameworkElement* fe, Storyboard* storyboard1,
        Storyboard* storyboard2 = 0);
    
    Ptr<Storyboard> CreateTransitionStoryboard(FrameworkElement* root, 
        VisualState* newState, VisualTransition* transition);

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
    void EnsureStates() const;
    void EnsureTransitions() const;

    void OnObjectDestroyed(DependencyObject* object);

private:
    NsString mName;
    mutable Ptr<VisualStateCollection> mStates;
    mutable Ptr<VisualTransitionCollection> mTransitions;

    struct ElementState
    {
        Ptr<VisualState> state;
        Ptr<Storyboard> storyboards[2];
    };

    typedef NsMap<FrameworkElement*, ElementState> CurrentStates;
    CurrentStates mCurrentStates;

    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(VisualStateGroup, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif