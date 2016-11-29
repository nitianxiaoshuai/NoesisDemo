////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_EVENTTRIGGER_H__
#define __GUI_EVENTTRIGGER_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/BaseTrigger.h>
#include <NsGui/CoreApi.h>
#include <NsCore/String.h>
#include <NsCore/Set.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class TriggerAction;
class RoutedEvent;
class FrameworkElement;
struct RoutedEventArgs;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a trigger that applies a set of actions (animation storyboards)
/// in response to an event.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.eventtrigger.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API EventTrigger: public BaseTrigger
{
public:
    EventTrigger();
    ~EventTrigger();
    
    /// Gets the collection of BeginStoryboard objects that this EventTrigger maintains
    TriggerActionCollection* GetActions() const;

    /// Gets or sets the name of the event that initiates the trigger
    //@{
    const RoutedEvent* GetRoutedEvent() const;
    void SetRoutedEvent(const RoutedEvent* event);
    //@}

    /// Gets or sets the name of the object with the event that activates this trigger. This is 
    /// only used by element triggers or template triggers. 
    //@{
    const NsChar* GetSourceName() const;
    void SetSourceName(const NsChar* name);
    //@}

    /// From BaseTrigger
    //@{
    void RegisterEvents(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipSourceName);
    void UnregisterEvents(FrameworkElement* target, NsBool skipSourceName);
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

private:
    void EnsureActions() const;

private:
    NsString mSourceName;
    const RoutedEvent* mRoutedEvent;
    mutable Ptr<TriggerActionCollection> mActions;

    struct Listener
    {
        EventTrigger* trigger;
        FrameworkElement* target;
        FrameworkElement* nameScope;
        mutable FrameworkElement* source;

        Listener(EventTrigger* et, FrameworkElement* t, FrameworkElement* ns,
            FrameworkElement* s);

        struct Comparer;
        NsBool operator<(const Listener& other) const;
        NsBool operator==(const Listener& other) const;

        void Register() const;
        void Unregister() const;

    private:
        void OnEvent(Core::BaseComponent* source, const RoutedEventArgs& args) const;
        void OnTargetDestroyed(DependencyObject* target);
        void OnSourceDestroyed(DependencyObject* source);
    };

    typedef NsSet<Listener> Listeners;
    Listeners mListeners;

    NS_DECLARE_REFLECTION(EventTrigger, BaseTrigger)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif