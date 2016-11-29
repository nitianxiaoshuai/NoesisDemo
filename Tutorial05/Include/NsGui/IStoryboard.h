////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ISTORYBOARD_H__
#define __GUI_ISTORYBOARD_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsCore/Ptr.h>
#include <NsGui/HandoffBehavior.h>
#include <NsGui/Events.h>


namespace Noesis
{
/// Forward declarations
//@{
namespace Core
{
template<class T> class Delegate;
class Symbol;
}
namespace Gui
{
class DependencyObject;
class FrameworkElement;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Manages playback of a storyboard.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IStoryboard: public Core::Interface
{
    /// Applies the animations associated with this Storyboard to their targets and initiates them
    //@{
    virtual void Begin() = 0;
    virtual void Begin(FrameworkElement* target) = 0;
    virtual void Begin(FrameworkElement* target, NsBool isControllable) = 0;
    virtual void Begin(FrameworkElement* target, HandoffBehavior handoffBehavior) = 0;
    virtual void Begin(FrameworkElement* target, HandoffBehavior handoffBehavior,
        NsBool isControllable) = 0;
    virtual void Begin(FrameworkElement* target, FrameworkElement* nameScope) = 0;
    virtual void Begin(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool isControllable) = 0;
    virtual void Begin(FrameworkElement* target, FrameworkElement* nameScope,
        HandoffBehavior handoffBehavior) = 0;
    virtual void Begin(FrameworkElement* target, FrameworkElement* nameScope,
        HandoffBehavior handoffBehavior, NsBool isControllable) = 0;
    //@}

    /// Pauses the Clock of the specified FrameworkElement associated with this Storyboard
    //@{
    virtual void Pause() = 0;
    virtual void Pause(FrameworkElement* target) = 0;
    //@}

    /// Resumes the Clock that was created for this Storyboard
    //@{
    virtual void Resume() = 0;
    virtual void Resume(FrameworkElement* target) = 0;
    //@}

    /// Stops the Clock that was created for this Storyboard
    //@}
    virtual void Stop() = 0;
    virtual void Stop(FrameworkElement* target) = 0;
    //@}

    /// Removes the Clock objects that were created for this Storyboard. Animations that belong to
    /// this Storyboard no longer affect the properties they once animated, regardless of their
    /// FillBehavior setting
    //@{
    virtual void Remove() = 0;
    virtual void Remove(FrameworkElement* target) = 0;
    //@}

    /// Indicates if a controllable storyboard is playing
    //@{
    virtual NsBool IsPlaying() const = 0;
    virtual NsBool IsPlaying(FrameworkElement* target) const = 0;
    //@}

    /// Indicates if a controllable storyboard is paused
    //@{
    virtual NsBool IsPaused() const = 0;
    virtual NsBool IsPaused(FrameworkElement* target) const = 0;
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION_(IStoryboard, Core::Interface)
};

}
}

#endif
