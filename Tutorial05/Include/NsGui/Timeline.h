////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TIMELINE_H__
#define __GUI_TIMELINE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/Animatable.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/Duration.h>
#include <NsGui/Events.h>


namespace Noesis
{
/// Forward Declarations
//@{
namespace Core
{
template<class T> class Nullable;
}
namespace Gui
{
class TimeSpan;
class RepeatBehavior;
class Clock;
class FrameworkElement;
class TimeManager;
}
//@}
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies how a Timeline behaves when it is outside its active period but its parent is 
/// inside its active or hold period
enum FillBehavior
{
    /// After it reaches the end of its active period, the timeline holds its progress until the 
    /// end of its parent's active and hold periods
    FillBehavior_HoldEnd,
    /// The timeline stops if it is outside its active period while its parent is inside its 
    /// active period
    FillBehavior_Stop
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Arguments to be passed in timeline Complete event
////////////////////////////////////////////////////////////////////////////////////////////////////
struct TimelineEventArgs: public EventArgs
{
    DependencyObject* target;

    TimelineEventArgs(DependencyObject* t = 0): target(t) { }
};

typedef Core::Delegate<void (Core::BaseComponent*, const TimelineEventArgs&)> 
    TimelineEventHandler;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a segment of time.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.timeline.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API Timeline: public Animatable
{
public:
    Timeline();
    Timeline(const Core::Nullable<TimeSpan>& beginTime);
    Timeline(const Core::Nullable<TimeSpan>& beginTime, const Duration& duration);
    Timeline(const Core::Nullable<TimeSpan>& beginTime, const Duration& duration,
        const RepeatBehavior& repeatBehavior);
    virtual ~Timeline() = 0;

    /// Gets the desired frame rate for this timeline and its child timelines
    static NsInt GetDesiredFrameRate(const DependencyObject* timeline);

    /// Sets the desired frame rate for this timeline and its child timelines
    static void SetDesiredFrameRate(DependencyObject* timeline, NsInt rate);

    /// Gets or sets a value specifying the percentage of the timeline's Duration spent 
    /// accelerating the passage of time from zero to its maximum rate
    //@{
    NsFloat32 GetAccelerationRatio() const;
    void SetAccelerationRatio(NsFloat32 value);
    //@}

    /// Gets or sets a value that indicates whether the timeline plays in reverse after it 
    /// completes a forward iteration
    //@{
    NsBool GetAutoReverse() const;
    void SetAutoReverse(NsBool value);
    //@}
    
    /// Gets or sets the time at which this Timeline should begin.
    /// A timeline's own SpeedRatio setting does not affect its BeginTime. For example, 
    /// a timeline with a BeginTime of 5 seconds, a SpeedRatio of 2, and a parent timeline
    /// with a SpeedRatio of 1 starts after 5 seconds, not 2.5.
    //@{
    const Core::Nullable<TimeSpan>& GetBeginTime() const;
    void SetBeginTime(const Core::Nullable<TimeSpan>& time);
    //@}

    /// Gets or sets a value specifying the percentage of the timeline's Duration spent 
    /// decelerating the passage of time from its maximum rate to zero
    //@{
    NsFloat32 GetDecelerationRatio() const;
    void SetDecelerationRatio(NsFloat32 value);
    //@}

    /// Gets or sets the length of time for which this timeline plays, not counting repetitions
    //@{
    const Duration& GetDuration() const;
    void SetDuration(const Duration& duration);
    //@}
    
    /// Gets or sets a value that specifies how the animation behaves after it reaches the end of 
    /// its active period
    //@{
    FillBehavior GetFillBehavior() const;
    void SetFillBehavior(FillBehavior behavior);
    //@}
    
    /// Gets or sets the name of this Timeline
    //@{
    const NsChar* GetName() const;
    void SetName(const NsChar* name);
    //@}
    
    /// Gets or sets the repeating behavior of this timeline
    //@{
    const RepeatBehavior& GetRepeatBehavior() const;
    void SetRepeatBehavior(const RepeatBehavior& behavior);
    //@}
    
    /// Gets or sets the rate, relative to its parent, at which time progresses for this Timeline
    //@{
    NsFloat32 GetSpeedRatio() const;
    void SetSpeedRatio(NsFloat32 value);
    //@}

    /// Occurs when the Storyboard object has completed playing
    DelegateEvent_<TimelineEventHandler> Completed();

    /// Creates a new Clock from this Timeline and specifies whether the new Clock is controllable.
    /// If this Timeline has children, a tree of clocks is created with this Timeline as the root.
    Ptr<Clock> CreateClock(TimeManager* timeManager, NsBool hasControllableRoot);

    /// Gets the duration of the timeline when duration is set to automatic
    virtual Duration GetNaturalDuration(Clock* clock) const;

    const Duration& GetSinglePassDuration() const;
    const Duration& GetIterationDuration() const;
    const Duration& GetTotalDuration() const;
    NsBool IsTotalDurationAbsolute() const;

    const Duration& GetNormalizedDuration() const;

    /// Computes the effective durations of the timeline
    void CalculateEffectiveDurations();

    virtual Duration GetEffectiveDuration() const = 0;

    // Called when an owner clock is being destroyed
    virtual void OnClockDestroyed(const Clock* clock);

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* AccelerationRatioProperty;
    static const DependencyProperty* AutoReverseProperty;
    static const DependencyProperty* BeginTimeProperty;
    static const DependencyProperty* DecelerationRatioProperty;
    static const DependencyProperty* DesiredFrameRateProperty;
    static const DependencyProperty* DurationProperty;
    static const DependencyProperty* FillBehaviorProperty;
    static const DependencyProperty* NameProperty;
    static const DependencyProperty* RepeatBehaviorProperty;
    static const DependencyProperty* SpeedRatioProperty;
    //@}

protected:
    /// Creates a Clock for this Timeline
    virtual Ptr<Clock> CreateClockCore(TimeManager* timeManager,
        NsBool hasControllableRoot) = 0;
    
    // From Freezable
    //@{
    void CloneCommonCore(const Freezable* source);
    //@}

private:
    void RaiseCompleted(const TimelineEventArgs& args);

private:
    friend class Storyboard;
    friend class TimeManager;

    /// Duration of a single pass (without the reverse)
    Duration mSinglePassDurationInternal;
    
    /// Duration of a complete pass (with the reverse, if applicable)
    Duration mIterationDurationInternal;
    
    /// Total duration of the animation, with repetitions and autoreverse, but without begintime nor
    /// speedration
    Duration mTotalDurationInternal;
    
    /// Indicates that the total duration is not affected by speedratio
    NsBool mTotalDurationAbsolute;
    
    /// TotalDuration / speedratio + begintime
    Duration mNormalizedDurationInternal;

    /// Handler to be launched at end of timeline
    TimelineEventHandler mCompleted;
    
    NS_DECLARE_REFLECTION(Timeline, Animatable)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

NS_DECLARE_ENUM(NS_GUI_ANIMATION_API, Noesis::Gui::FillBehavior)


#endif
