////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1403]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_REPEATBEHAVIOR_H__
#define __GUI_REPEATBEHAVIOR_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/TimeSpan.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Gui
{
class TimeSpan;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes how the RepeatBehavior calculates its repetitions
////////////////////////////////////////////////////////////////////////////////////////////////////
enum RepeatMode
{
    /// Specifies that a Timeline repeats n times
    RepeatMode_Count,
    /// Indicates that a Timeline repeats for a specific duration
    RepeatMode_Duration,
    /// Specifies an infinite number of repetitions
    RepeatMode_Forever
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes how a Timeline repeats its simple duration.
/// Examples:
///     RepeatBehavior="2x"             --->  Repeats 2 times
///     RepeatBehavior="1.2:30:15.500"  --->  [days.]hours:minutes:seconds[.fractionalSeconds]
///     RepeatBehavior="2.1:20"         --->  [days.]hours:minutes
///     RepeatBehavior="5"              --->  days
///     RepeatBehavior="Forever"        --->  Repeats forever
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API RepeatBehavior
{
public:
    /// Constructors
    //@{
    RepeatBehavior();
    RepeatBehavior(NsFloat32 count);
    RepeatBehavior(const TimeSpan& duration);
    //@}

    /// Creates a RepeatBehavior object that specifies an infinite number of repetitions
    static RepeatBehavior Forever();

    /// Generates a string representation of the point
    /// The string has the following form: "Forever", "2x", or a TimeSpan: "0:0:1"
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Creates a RepeatBehavior object from a string
    static RepeatBehavior Parse(const NsChar* txt);

    /// Safe version of Parse function
    static NsBool TryParse(const NsChar* txt, RepeatBehavior& result);

    /// Gets repeat mode
    RepeatMode GetRepeatMode() const;

    /// Gets repeat count
    /// \remarks Only valid for repeat mode Count
    NsFloat32 GetCount() const;

    /// Gets repeat time duration
    /// \remarks Only valid for repeat mode Duration
    const TimeSpan& GetDuration() const;

    /// Compares two RepeatBehavior objects
    //@{
    NsBool operator==(const RepeatBehavior& other) const;
    NsBool operator!=(const RepeatBehavior& other) const;
    //@}

private:
    RepeatMode mRepeatMode;
    NsFloat32 mCount;
    TimeSpan mDuration;

    NS_DECLARE_REFLECTION(RepeatBehavior, Core::NoParent)
};

}
}

#endif