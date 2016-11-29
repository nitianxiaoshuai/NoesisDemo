////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1382]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TIMESPAN_H__
#define __GUI_TIMESPAN_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/NSTLForwards.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a time interval, expressed in days, hours, minutes, seconds and milliseconds, or in
/// ticks (100-nanosecond units)
///
/// TimeSpan is generally used from XAML files, parsing with the following signature:
/// [ws][-]{ d | [d.]hh:mm[:ss[.ff]] }[ws]
///
///     ws: optional white space 
///     -: optional minus sign indicating a negative TimeSpan 
///     d: days, ranging from 0 to 10675199
///     hh: hours, ranging from 0 to 23
///     mm: minutes, ranging from 0 to 59 
///     ss: optional seconds, ranging from 0 to 59 
///     ff: optional fractional seconds, consisting of 1 to 7 decimal digits
///
/// Examples:
///     "1" and "1.0:0" represents 1 day
///     "0:1" represents 1 minute
///     "0:0:1" represents 1 second
///     "0:0:0.1" represents 1 millisecond
///     "-0:0:3" represents 3 seconds negative
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API TimeSpan
{
public:
    /// Constructors
    //@{
    inline TimeSpan();
    inline TimeSpan(NsInt64 ticks);
    inline TimeSpan(NsFloat64 seconds);
    TimeSpan(NsInt hours, NsInt minutes, NsInt seconds);
    TimeSpan(NsInt days, NsInt hours, NsInt minutes, NsInt seconds);
    TimeSpan(NsInt days, NsInt hours, NsInt minutes, NsInt seconds, NsInt milliseconds);
    //@}
    
    /// TypeConverter helper: creates a TimeSpan from a string
    static TimeSpan Parse(const NsChar* str);

    /// Safe version of Parse function
    static NsBool TryParse(const NsChar* str, TimeSpan& result);

    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Gets Zero Timespan
    static inline TimeSpan Zero();
    
    /// Get the days component of the time interval
    inline NsInt GetDays() const;
    
    /// Get the hours component of the time interval
    inline NsInt GetHours() const;
    
    /// Get the minutes component of the time interval
    inline NsInt GetMinutes() const;
    
    /// Get the seconds component of the time interval
    inline NsInt GetSeconds() const;
    
    /// Get the milliseconds component of the time interval
    inline NsInt GetMilliseconds() const;
    
    /// Get total TimeSpan value in Ticks
    inline NsInt64 GetTicks() const;
    
    /// Get total TimeSpan value in seconds
    inline NsFloat64 GetTimeInSeconds() const;

    /// Operators
    //@{
    inline NsBool operator==(const TimeSpan& other) const;
    inline NsBool operator!=(const TimeSpan& other) const;
    inline TimeSpan& operator+=(const TimeSpan& other);
    inline TimeSpan& operator-=(const TimeSpan& other);
    inline TimeSpan& operator*=(NsFloat32 value);
    //@}

private:
    NsInt64 mTicks;
    
    NS_DECLARE_REFLECTION(TimeSpan, Core::NoParent)
};

/// TimeSpan Binary operators
//@{
inline TimeSpan operator+(const TimeSpan& t0, const TimeSpan& t1);
inline TimeSpan operator-(const TimeSpan& t0, const TimeSpan& t1);

inline TimeSpan operator*(const TimeSpan& t, NsFloat32 value);
inline TimeSpan operator*(NsFloat32 value, const TimeSpan& t);

inline NsFloat32 operator/(const TimeSpan& t0, const TimeSpan& t1);
inline TimeSpan operator/(const TimeSpan& t, NsFloat32 value);

inline NsBool operator<(const TimeSpan& t0, const TimeSpan& t1);
inline NsBool operator<=(const TimeSpan& t0, const TimeSpan& t1);
inline NsBool operator>(const TimeSpan& t0, const TimeSpan& t1);
inline NsBool operator>=(const TimeSpan& t0, const TimeSpan& t1);
//@}

}
}


#include <NsGui/TimeSpan.inl>

#endif
