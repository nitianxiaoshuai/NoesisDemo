////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ANIMATIONTIMELINE_H__
#define __GUI_ANIMATIONTIMELINE_H__


#include <Noesis.h>
#include <NsGui/Timeline.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/HandoffBehavior.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class Clock;
class AnimationClock;
NS_INTERFACE ITimeManager;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a segment of time over which output values are produced. These values are used to
/// animate a target property.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.animationtimeline.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API AnimationTimeline: public Timeline
{
public:
    AnimationTimeline();
    virtual ~AnimationTimeline() = 0;

    /// Calculates the current animated value depending on current clock state
    virtual Ptr<BaseComponent> GetAnimatedValue(BaseComponent* defaultOrigin,
        BaseComponent* defaultDestination, AnimationClock* clock) = 0;

    /// Begins the animation timeline creating a compatible clock
    void Start(DependencyObject* target, const DependencyProperty* dp, ITimeManager* timeManager,
        HandoffBehavior handoff = HandoffBehavior_SnapshotAndReplace);

    /// Identifies the IsAdditive dependency property.
    //@{
    NsBool GetIsAdditive() const;
    void SetIsAdditive(NsBool value);
    //@}

    /// Identifies the IsCumulative dependency property. 
    //@{
    NsBool GetIsCumulative() const;
    void SetIsCumulative(NsBool value);
    //@}

    /// Returns a new timeline used as transition (used by VisualStateManager)
    //@{
    virtual Ptr<AnimationTimeline> CreateTransitionFrom() const = 0;
    virtual Ptr<AnimationTimeline> CreateTransitionTo() const = 0;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* IsAdditiveProperty;
    static const DependencyProperty* IsCumulativeProperty;
    //@}
    
protected:
    /// From Timeline
    //@{
    Ptr<Clock> CreateClockCore(TimeManager* timeManager, NsBool hasControllableRoot);
    Duration GetNaturalDuration(Clock* clock) const;
    Duration GetEffectiveDuration() const;
    //@}

    NS_DECLARE_REFLECTION(AnimationTimeline, Timeline)
};

}
}


#endif
