////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CLOCK_H__
#define __GUI_CLOCK_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/Delegate.h>
#include <NsCore/Vector.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/Duration.h>
#include <NsGui/Events.h>

#include <EASTL/fixed_vector.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyObject;
class ClockGroup;
class ClockController;
class Timeline;
class TimeManager;
//@}

enum ClockState
{
    /// The current Clock time changes in direct relation to that of its parent. If the timeline 
    /// is an animation, it is actively affecting targeted properties, so their value may change 
    /// from tick (a sampling point in time) to tick. If the timeline has children, they may be 
    /// ClockState_Active, ClockState_Filling, or ClockState_Stopped
    ClockState_Active,
    /// The clock timing is paused. If the timeline is an animation, targeted properties are not
    /// updated and maintain its last value. If the timeline has children, they may be
    /// ClockState_Active, ClockState_Filling, or ClockState_Paused
    ClockState_Paused,
    /// The Clock timing continues, but does not change in relation to that of its parent. If the 
    /// timeline is an animation, it is actively affecting targeted properties, but its values 
    /// don't change from tick to tick. If the timeline has children, they may be ClockState_Active,
    /// ClockState_Filling, or ClockState_Stopped
    ClockState_Filling,
    /// The Clock timing is halted, making the clock's current time and progress values undefined.
    /// If this timeline is an animation, it no longer affects targeted properties. If this 
    /// timeline has children, they are also ClockState_Stopped
    ClockState_Stopped,
    /// To test if the clock finished completely and the TimeManaged can remove it. This can be done
    /// also launching a Finished event if the TimeManager registers against it
    ClockState_Finished
};

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Maintains run-time timing state for a Timeline. A Timeline, by itself, doesn't actually do
/// anything other than describe a segment of time. It's the timeline's Clock object that does the
/// real work: it maintains timing-related run-time state for the timeline. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.clock.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API Clock: public Core::BaseComponent
{
public:
    Clock(Timeline* timeline, NsBool controllable);
    virtual ~Clock() = 0;
    
    /// Get the current iteration of this clock within its current active period, or -1 if this
    /// clock is stopped.
    NsInt GetCurrentIteration() const;
    
    /// Gets the current progress of Clock within its current iteration. This is a value between
    /// 0.0 and 1.0
    NsFloat32 GetCurrentProgress() const;

    /// Gets this clock's current time within its current iteration. 
    NsFloat64 GetCurrentTime() const;

    /// Gets a value indicating whether the clock is currently Active, Filling or Stopped.
    ClockState GetCurrentState() const;
    
    /// Gets a value that indicates whether this Clock is part of a controllable clock tree.
    NsBool HasControllableRoot() const;

    /// Gets or sets the clock that is the parent of this clock.
    ClockGroup* GetParent() const;

    /// Gets the Timeline from which this Clock was created.
    Timeline* GetTimeline() const;

    /// Occurs when this clock has completely finished playing.
    DelegateEvent_<EventHandler> Completed();

protected:
    virtual NsBool Tick(NsFloat64 time, ClockState parentState);

    virtual void SetOwner(TimeManager* owner);
    virtual void Recycle(TimeManager* owner);
    void Construct(Timeline* timeline, NsBool controllable);

    /// From BaseRefCounted
    //@{
    NsInt32 OnDestroy() const;
    //@}

private:
    void RaiseCompleted(const EventArgs& args);

protected:
    TimeManager* mOwner;
    Ptr<Timeline> mTimeline;

private:
    friend class ClockTest;
    friend class ClockGroup;
    friend class TimeManager;

    ClockGroup* mParent;
    DependencyObject* mTarget;

    NsInt mCurrentIteration;
    NsFloat32 mCurrentProgress;
    NsFloat64 mCurrentTime;

    ClockState mState;

    NsBool mHasControllableRoot;

    /// Handler to be launched at end of clock
    EventHandler mCompleted;

    NS_DECLARE_REFLECTION(Clock, BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

NS_DECLARE_ENUM(NS_GUI_ANIMATION_API, Noesis::Gui::ClockState)


#endif
