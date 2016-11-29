////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VISUALSTATEMANAGER_H__
#define __GUI_VISUALSTATEMANAGER_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class FrameworkElement;
class VisualState;
class VisualStateGroup;
class VisualTransition;
template<class T> class TypedCollection;
//@}

typedef Noesis::Gui::TypedCollection<Noesis::Gui::VisualStateGroup> VisualStateGroupCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Manages states and the logic for transitioning between states for controls. The
/// VisualStateManager enables you to specify states for a control, the appearance of a control
/// when it is in a certain state, and when a control changes states.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.visualstatemanager.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API VisualStateManager: public Gui::DependencyObject
{
public:
    VisualStateManager();
    ~VisualStateManager();

    /// Gets the CustomVisualStateManager attached property.
    static VisualStateManager* GetCustomVisualStateManager(const DependencyObject* obj);
    
    /// Sets the CustomVisualStateManager attached property.
    static void SetCustomVisualStateManager(DependencyObject* obj, VisualStateManager* value);

    /// Gets the VisualStateGroupCollection attached property.
    static VisualStateGroupCollection* GetVisualStateGroups(const DependencyObject* obj);
    
    /// Sets the VisualStateGroupCollection attached property.
    static void SetVisualStateGroups(DependencyObject* obj, VisualStateGroupCollection* groups);
    
    /// Transitions the control between two states. Use this method to transition states on control
    /// that has a ControlTemplate.
    /// \param control The control to transition between states
    /// \param stateName The state to transition to
    /// \param useTransitions true to use a VisualTransition to transition between states, 
    ///     otherwise false.
    /// \return true if the control successfully transitioned to the new state, otherwise false.
    static NsBool GoToState(FrameworkElement* control, NsSymbol stateName, NsBool useTransitions);
    
    /// Transitions the element between two states. Use this method to transition states that are 
    /// defined by an application, rather than defined by a control.
    /// \param stateGroupsRoot The root element that contains the VisualStateManager
    /// \param stateName The state to transition to.
    /// \param useTransitions true to use a VisualTransition object to transition between states
    static NsBool GoToElementState(FrameworkElement* root, NsSymbol stateName,
        NsBool useTransitions);

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* CustomVisualStateManagerProperty; // Attached
    static const DependencyProperty* VisualStateGroupsProperty; // Attached
    //@}

private:
    static NsBool GoToStateInternal(FrameworkElement* control, FrameworkElement* root, 
        NsSymbol, NsBool useTransitions);
       
    static VisualTransition* GetTransition(FrameworkElement* fe, VisualStateGroup* group, 
        VisualState* from, VisualState* to);
    
    /// Transitions a control between states
    /// \param control The control to transition between states
    /// \param templateRoot The root element of the control's ControlTemplate
    /// \param stateName The name of the state to transition to
    /// \param group The VisualStateGroup that the state belongs to
    /// \param state The representation of the state to transition to
    /// \param useTransitions true to use a VisualTransition to transition between states;
    ///     otherwise, false
    /// \return true if the control successfully transitioned to the new state; otherwise, false
    virtual NsBool GoToStateCore(const Ptr<FrameworkElement>& control, 
        const Ptr<FrameworkElement>& templateRoot, const NsChar* stateName, 
        const Ptr<VisualStateGroup>& group, const Ptr<VisualState>& state, NsBool useTransitions);

    /// Raises the CurrentStateChanged event on the specified VisualStateGroup
    /// \param stateGroup The object on which the CurrentStateChanging event
    /// \param oldState The state that the control transitioned from
    /// \param newState The state that the control transitioned to
    /// \param control The control that transitioned states
    static void RaiseCurrentStateChanged(const Ptr<VisualStateGroup>& stateGroup, 
        const Ptr<VisualState>& oldState, const Ptr<VisualState>& newState, 
        const Ptr<FrameworkElement>& control);
    
    /// Raises the CurrentStateChanging event on the specified VisualStateGroup
    /// \param stateGroup The object on which the CurrentStateChanging event
    /// \param oldState The state that the control is transitioning from
    /// \param newState The state that the control is transitioning to
    /// \param control The control that is transitioning states
    static void RaiseCurrentStateChanging(const Ptr<VisualStateGroup>& stateGroup, 
        const Ptr<VisualState>& oldState, const Ptr<VisualState>& newState, 
        const Ptr<FrameworkElement>& control);
    
    NS_DECLARE_REFLECTION(VisualStateManager, DependencyObject)
};


}
}

#endif