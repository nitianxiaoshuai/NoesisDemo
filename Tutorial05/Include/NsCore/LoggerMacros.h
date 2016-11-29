////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_LOGGERMACROS_H__
#define __CORE_LOGGERMACROS_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/CompilerSettings.h>


namespace Noesis
{
namespace Core
{

/// Log severties used by macros. The console detects this values and colorize them properly
enum LogSeverity
{
    LogSeverity_Critical = 0,
    LogSeverity_Warning = 10,
    LogSeverity_Info = 20,
    LogSeverity_Debug = 30
};

/// Defines character arrays length for messages
//@{
const NsSize MessageLength = 256;
const NsSize ScopeLength = 32;
const NsSize ChannelLength = 32;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Scope class for automatically opening and closing a log section
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API LoggerSection
{
public:
    /// Constructor
    LoggerSection(NsByte severity, const NsChar* channel, const NsChar* scope, NsBool timing, 
        _Printf_format_string_ const NsChar* message, ...) NS_FORMAT_PRINTF(6,7);

    /// Destructor
    ~LoggerSection();

private:
    NsBool mTiming;
    NsByte mSeverity;
    NsChar mChannel[ChannelLength];
    NsChar mScope[ScopeLength];
    NsChar mMessage[MessageLength];
    NsFloat64 mT0, mT1;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Begins a log section.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_CORE_KERNEL_API void BeginLogSection(NsByte severity, const NsChar* channel, const NsChar* scope, 
    _Printf_format_string_ const NsChar* message, ...) NS_FORMAT_PRINTF(4,5);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Ends a log section.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_CORE_KERNEL_API void EndLogSection(NsByte severity, const NsChar* channel, const NsChar* scope, 
    _Printf_format_string_ const NsChar* message, ...) NS_FORMAT_PRINTF(4,5);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Macros to make easier the creation of log sections.
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{

////////////////////////////////////////////////////////////////////////////////////////////////////
#if NS_LOGGER_ENABLED

    /// Section(severity, channel)
    //@{
    #define NS_LOG_SECTION(severity, channel, ...) \
        Noesis::Core::LoggerSection NS_UNIQUE_NAME(logSection)(severity, channel, \
        "", false, __VA_ARGS__)
        
    #define NS_LOG_SECTION_TIME(severity, channel, ...) \
        Noesis::Core::LoggerSection NS_UNIQUE_NAME(logSection)(severity, channel, \
        "", true, __VA_ARGS__)

    #define NS_BEGIN_LOG_SECTION(severity, channel, ...) \
        Noesis::Core::BeginLogSection(severity, channel, "", __VA_ARGS__)

    #define NS_END_LOG_SECTION(severity, channel, ...) \
        Noesis::Core::EndLogSection(severity, channel, "", __VA_ARGS__)
    //@}
    
    #define __GENCH__ "General"

    /// Info section [General]
    //@{
    #define NS_INFO_SECTION(...) \
        NS_LOG_SECTION(Noesis::Core::LogSeverity_Info, __GENCH__, __VA_ARGS__)
            
    #define NS_INFO_SECTION_TIME(...) \
        NS_LOG_SECTION_TIME(Noesis::Core::LogSeverity_Info, __GENCH__, __VA_ARGS__)

    #define NS_BEGIN_INFO_SECTION(...) \
        NS_BEGIN_LOG_SECTION(Noesis::Core::LogSeverity_Info, __GENCH__, __VA_ARGS__)

    #define NS_END_INFO_SECTION(...) \
        NS_END_LOG_SECTION(Noesis::Core::LogSeverity_Info, __GENCH__, __VA_ARGS__)
    //@}
    
    /// Warning section [General]
    //@{
    #define NS_WARNING_SECTION(...) \
        NS_LOG_SECTION(Noesis::Core::LogSeverity_Warning, __GENCH__, __VA_ARGS__)
            
    #define NS_WARNING_SECTION_TIME(...) \
        NS_LOG_SECTION_TIME(Noesis::Core::LogSeverity_Warning, __GENCH__, __VA_ARGS__)

    #define NS_BEGIN_WARNING_SECTION(...) \
        NS_BEGIN_LOG_SECTION(Noesis::Core::LogSeverity_Warning, __GENCH__, __VA_ARGS__)

    #define NS_END_WARNING_SECTION(...) \
        NS_END_LOG_SECTION(Noesis::Core::LogSeverity_Warning, __GENCH__, __VA_ARGS__)
    //@}
    
   /// Critical section [General]
    //@{
    #define NS_CRITICAL_SECTION(...) \
        NS_LOG_SECTION(Noesis::Core::LogSeverity_Critical, __GENCH__, __VA_ARGS__)
            
    #define NS_CRITICAL_SECTION_TIME(...) \
        NS_LOG_SECTION_TIME(Noesis::Core::LogSeverity_Critical, __GENCH__, __VA_ARGS__)

    #define NS_BEGIN_CRITICAL_SECTION(...) \
        NS_BEGIN_LOG_SECTION(Noesis::Core::LogSeverity_Critical, __GENCH__, __VA_ARGS__)

    #define NS_END_CRITICAL_SECTION(...) \
        NS_END_LOG_SECTION(Noesis::Core::LogSeverity_Critical, __GENCH__, __VA_ARGS__)
    //@}

#else

    #define NS_LOG_SECTION(level, ...) NS_NOOP
    #define NS_LOG_SECTION_TIME(level, ...) NS_NOOP
    #define NS_BEGIN_LOG_SECTION(level, ...) NS_NOOP
    #define NS_END_LOG_SECTION(level, ...) NS_NOOP
    #define NS_INFO_SECTION(...) NS_NOOP
    #define NS_INFO_SECTION_TIME(...) NS_NOOP
    #define NS_BEGIN_INFO_SECTION(...) NS_NOOP
    #define NS_END_INFO_SECTION(...) NS_NOOP
    #define NS_WARNING_SECTION(...) NS_NOOP
    #define NS_WARNING_SECTION_TIME(...) NS_NOOP
    #define NS_BEGIN_WARNING_SECTION(...) NS_NOOP
    #define NS_END_WARNING_SECTION(...) NS_NOOP
    #define NS_CRITICAL_SECTION(...) NS_NOOP
    #define NS_CRITICAL_SECTION_TIME(...) NS_NOOP
    #define NS_BEGIN_CRITICAL_SECTION(...) NS_NOOP
    #define NS_END_CRITICAL_SECTION(...) NS_NOOP

#endif

//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Logs a formated message.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_CORE_KERNEL_API void FormatLog(NsByte severity, const NsChar* channel, const NsChar* scope, 
    _Printf_format_string_ const NsChar* message, ...) NS_FORMAT_PRINTF(4,5);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Macros to make easier the creation of log messages.
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{

////////////////////////////////////////////////////////////////////////////////////////////////////
#if NS_LOGGER_ENABLED

    #define NS_LOG(severity, channel, ...) \
        Noesis::Core::FormatLog(severity, channel, "", __VA_ARGS__)

    #define NS_DEBUG(...) NS_LOG(Noesis::Core::LogSeverity_Debug, __GENCH__, __VA_ARGS__)
    #define NS_INFO(...) NS_LOG(Noesis::Core::LogSeverity_Info, __GENCH__, __VA_ARGS__)
    #define NS_WARNING(...) NS_LOG(Noesis::Core::LogSeverity_Warning, __GENCH__, __VA_ARGS__)
    #define NS_CRITICAL(...) NS_LOG(Noesis::Core::LogSeverity_Critical, __GENCH__, __VA_ARGS__)

#else

    #define NS_LOG(level, ...) NS_NOOP
    #define NS_DEBUG(...) NS_NOOP
    #define NS_INFO(...) NS_NOOP
    #define NS_WARNING(...) NS_NOOP
    #define NS_CRITICAL(...) NS_NOOP

#endif

//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Scope object for muting the log
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API LoggerMuter
{
public:
    /// Constructor
    LoggerMuter(NsBool mute);

    /// Destructor
    ~LoggerMuter();

private:
    NsBool mMute;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Macro to temporary mute the log
////////////////////////////////////////////////////////////////////////////////////////////////////
#if NS_LOGGER_ENABLED
    #define NS_MUTE_LOG(mute) Noesis::Core::LoggerMuter NS_UNIQUE_NAME(logMuter)(mute)
#else
    #define NS_MUTE_LOG(mute) NS_UNUSED(mute)
#endif


}
}


#endif