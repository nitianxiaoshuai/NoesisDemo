////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_LOGGER_H__
#define __CORE_LOGGER_H__


#include <NsCore/Types.h>
#include <NsCore/DelegateForward.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Logs messages to console.
////////////////////////////////////////////////////////////////////////////////////////////////////
class Logger
{
public:
    /// Logs a message
    virtual void Log(NsByte severity, const NsChar* channel, const NsChar* scope, 
        const NsChar* message) = 0;

    /// Increments the indentation level for subsequent messages
    virtual void IncrementIndent() = 0;

    /// Decrements the indentation level for subsequents messages
    virtual void DecrementIndent() = 0;

    /// Mute/UnMute logs for all the threads
    virtual void Mute(NsBool muted) = 0;
    
    /// Returns when all the pending logs have been delivered. If not working under a debugger
    /// the messages are processed in a thread. This function will return when there is not
    /// messages pending in the internal structures
    virtual void Flush() = 0;
    
    /// Functions for adding/removing logger clients. Each client is invoked whenever new messages 
    /// are logged. The delegate may be invoked from a thread different to the main
    //@{
    typedef Delegate<void (NsSize indentation, NsByte severity, NsUInt32 threadId, 
        NsFloat64 timeStamp, const NsChar* channel, const NsChar* scope, 
        const NsChar* message)> Client;

    virtual void AddClient(const Client& client) = 0;
    virtual void RemoveClient(const Client& client) = 0;
    //@}
};

}
}


#endif
