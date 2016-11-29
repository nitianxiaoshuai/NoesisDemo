////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VISUALTRANSITION_H__
#define __GUI_VISUALTRANSITION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/Duration.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class EasingFunctionBase;
class Storyboard;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the visual behavior that occurs when the control transitions from
/// one state to another.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.visualtransition.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API VisualTransition: public DependencyObject, public IUITreeNode
{
public:
    VisualTransition();
    ~VisualTransition();

    /// Gets or sets the name of the VisualState to transition from
    //@{
    NsSymbol GetFrom() const;
    void SetFrom(NsSymbol from);
    //@}
    
    /// Gets or sets the name of the VisualState to transition to
    //@{
    NsSymbol GetTo() const;
    void SetTo(NsSymbol to);
    //@}
    
    /// Gets or sets the amount of time it takes to move from one state to another
    //@{
    const Duration& GetGeneratedDuration() const;
    void SetGeneratedDuration(const Duration& duration);
    //@}
    
    /// Gets or sets the easing function applied to the generated animations
    //@{
    EasingFunctionBase* GetGeneratedEasingFunction() const;
    void SetGeneratedEasingFunction(EasingFunctionBase* function);
    //@}
    
    /// Gets or sets the Storyboard that occurs when the transition occurs
    //@{
    Storyboard* GetStoryboard() const;
    void SetStoryboard(Storyboard* storyboard);
    //@}
    
    /// If the transition has no From or To, is a default transition
    NsBool IsDefault() const;

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
    NsSymbol mFrom;
    NsSymbol mTo;
    Duration mGeneratedDuration;
    Ptr<EasingFunctionBase> mGeneratedEasingFunction;
    Ptr<Storyboard> mStoryboard;

    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(VisualTransition, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif