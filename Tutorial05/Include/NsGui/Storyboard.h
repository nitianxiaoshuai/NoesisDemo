////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STORYBOARD_H__
#define __GUI_STORYBOARD_H__


#include <Noesis.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/ParallelTimeline.h>
#include <NsGui/IStoryboard.h>
#include <NsGui/TimeSpan.h>
#include <NsGui/Clock.h>
#include <NsGui/HandoffBehavior.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/Vector.h>
#include <NsCore/Map.h>

#include <EASTL/fixed_vector.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class PropertyPath;
struct PathElement;
class FrameworkElement;
class AnimationClock;
class AnimationTimeline;
struct AnimationTarget;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
struct AnimationTarget
{
    inline NsBool operator==(const AnimationTarget& other) const
    {
        return object == other.object && dp == other.dp;
    }
    
    DependencyObject* object;
    const DependencyProperty* dp;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A container timeline that provides object and property targeting information for its 
/// child animations. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.storyboard.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API Storyboard: public ParallelTimeline, public IStoryboard
{
public:
    Storyboard();
    ~Storyboard();

    /// Retrieves the TargetName value of the specified Timeline.
    static const NsChar* GetTargetName(const DependencyObject* element);

    /// Makes the specified Timeline target the dependency object with the specified name.
    static void SetTargetName(DependencyObject* element, const NsChar* name);
    
    /// Retrieves the TargetProperty value of the specified Timeline.
    static PropertyPath* GetTargetProperty(const DependencyObject* element);
    
    /// Makes the specified Timeline target the specified dependency property.
    static void SetTargetProperty(DependencyObject* element, PropertyPath* path);

    /// Retrieves the Target value of the specified Timeline.
    static DependencyObject* GetTarget(const DependencyObject* element);
    
    /// Makes the specified Timeline target the dependency object.
    static void SetTarget(DependencyObject* element, DependencyObject* target);

    /// From IStoryboard
    //@{
    void Begin();
    void Begin(FrameworkElement* target);
    void Begin(FrameworkElement* target, NsBool isControllable);
    void Begin(FrameworkElement* target, HandoffBehavior handoffBehavior);
    void Begin(FrameworkElement* target, HandoffBehavior handoffBehavior, NsBool isControllable);
    void Begin(FrameworkElement* target, FrameworkElement* nameScope);
    void Begin(FrameworkElement* target, FrameworkElement* nameScope, NsBool isControllable);
    void Begin(FrameworkElement* target, FrameworkElement* nameScope,
        HandoffBehavior handoffBehavior);
    void Begin(FrameworkElement* target, FrameworkElement* nameScope,
        HandoffBehavior handoffBehavior, NsBool isControllable);
    void Pause();
    void Pause(FrameworkElement* target);
    void Resume();
    void Resume(FrameworkElement* target);
    void Stop();
    void Stop(FrameworkElement* target);
    void Remove();
    void Remove(FrameworkElement* target);
    NsBool IsPlaying() const;
    NsBool IsPlaying(FrameworkElement* target) const;
    NsBool IsPaused() const;
    NsBool IsPaused(FrameworkElement* target) const;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* TargetNameProperty; // Attached
    static const DependencyProperty* TargetProperty; // Attached
    static const DependencyProperty* TargetPropertyProperty; // Attached
    //@}

protected:
    /// From Timeline
    //@{
    void OnClockDestroyed(const Clock* clock);
    //@}

private:
    void InternalBegin(FrameworkElement* target, FrameworkElement* nameScope,
        HandoffBehavior handoffBehavior, NsBool isControllable);
    void InternalPause(FrameworkElement* target);
    void InternalResume(FrameworkElement* target);
    void InternalRemove(FrameworkElement* target);

    NsBool InternalIsPlaying(FrameworkElement* target) const;
    NsBool InternalIsPaused(FrameworkElement* target) const;

    friend class TimeManager;
    void RegisterControllableClock(FrameworkElement* target, Clock* clock);
    void UnregisterControllableClock(FrameworkElement* target, NsBool removeClock);

    typedef NsMap<FrameworkElement*, Clock*> Controllables;

    void UnregisterControllableClock(Controllables::iterator it, NsBool removeClock);

    void OnTargetDestroyed(DependencyObject* object);

    FrameworkElement* FindTarget() const;

    struct Animation
    {
        DependencyObject* target;
        const DependencyProperty* dp;
        AnimationClock* clock;
    };

    typedef eastl::fixed_vector<Animation, 64> Animations;

    void ResolveTargets(FrameworkElement* fe, FrameworkElement* ns, Clock* clock,
        Animations& targets) const;

    AnimationTarget ResolveTarget(Timeline* timeline, FrameworkElement* fe,
        FrameworkElement* ns = 0) const;

    void AddPathElement(const PathElement& pathElement, void* context) const;

private:
    // NOTE: There is no CloneCommonCore because mControllables are not transferred to the
    //       cloned Storyboard

    Controllables mControllables;

    NS_DECLARE_REFLECTION(Storyboard, ParallelTimeline)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
