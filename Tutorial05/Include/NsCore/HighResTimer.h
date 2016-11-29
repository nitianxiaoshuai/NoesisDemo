////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_HIGHRESTIMER_H__
#define __CORE_HIGHRESTIMER_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// A high resolution timer
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API HighResTimer
{
public:
    /// Initializes the timer and sets the StartTime
    static void Init();
    
    /// \return the time when the timer was initialized
    inline static NsFloat64 StartTime();
    
    /// \return the timer precision in hz
    inline static NsFloat64 Frequency();

    /// \return time in seconds. StartTime() must me substracted to get the time since the beginning
    inline static NsFloat64 Seconds();

    /// \return time in cpu cycles
    inline static NsUInt64 Cycles();

private:
    #ifdef _WIN32
        static NsFloat64 sSecondsPerCycle;
    #endif
    
    static NsFloat64 sStartTime;
};

}
}

// Inline include
#include <NsCore/HighResTimer.inl>


#endif
