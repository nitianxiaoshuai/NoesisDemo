////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ITIMEMANAGER_H__
#define __GUI_ITIMEMANAGER_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
/// Forward declarations
//@{
namespace Core
{
class Symbol;
}
namespace Gui
{
class FrameworkElement;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Manages all running animations.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE ITimeManager: public Core::Interface
{
    /// Indicates if animations were added after the last Tick
    virtual NsBool HasPendingAnimations() const = 0;

    /// Updates pending animations to the current time
    virtual void TickPending() = 0;

    /// Updates animation values to the specified time
    virtual void Tick(NsFloat64 timeInSeconds) = 0;

    /// Launches the animations associated with the specified state
    virtual NsBool GoToState(FrameworkElement* target, Core::Symbol stateName) const = 0;

    /// Transfers animations of this TimeManager to the specified one
    virtual void TransferTo(ITimeManager* other) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(ITimeManager, Core::Interface)
};

}
}

#endif
