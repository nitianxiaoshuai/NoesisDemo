////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DURATION_H__
#define __GUI_DURATION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/TimeSpan.h>


namespace Noesis
{

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum DurationType
{
    /// Identifies a Duration value that is automatically determined
    DurationType_Automatic,

    /// Indicates this Duration represents a TimeSpan value
    DurationType_TimeSpan,

    /// Identifies a Duration value that represents an infinite interval
    DurationType_Forever
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the duration of time that a Timeline is active
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API Duration
{
public:
    /// Default constructor
    Duration();

    /// Constructor for timespan type
    Duration(const TimeSpan& timeSpan);

    /// Creates a new Duration of Automatic type
    static Duration Automatic();

    /// Creates a new Duration of Forever type
    static Duration Forever();

    /// TypeConverter helper
    static Duration Parse(const NsChar* str);

    /// Safe version of Parse function
    static NsBool TryParse(const NsChar* str, Duration& result);

    /// Gets duration time
    inline const TimeSpan& GetTimeSpan() const;

    /// Gets duration type
    inline DurationType GetDurationType() const;

    /// Gets duration as a string
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Operators
    //@{
    Duration& operator=(const TimeSpan& other);
    NsBool operator==(const Duration& other) const;
    NsBool operator!=(const Duration& other) const;
    //@}

private:
    DurationType mDurationType;
    TimeSpan mTimeSpan;

    NS_DECLARE_REFLECTION(Duration, Core::NoParent)
};

}
}


#include <NsGui/Duration.inl>


#endif
