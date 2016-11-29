////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CLOCKCONTROLLER_H__
#define __GUI_CLOCKCONTROLLER_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class Clock;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

class NS_GUI_ANIMATION_API ClockController: public Core::BaseComponent
{
public:
    ClockController(Clock* clock);
    ~ClockController();

private:
    Ptr<Clock> mClock;

    NS_DECLARE_REFLECTION(ClockController, BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif