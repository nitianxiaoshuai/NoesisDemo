////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1410]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_KEYTIME_H__
#define __GUI_KEYTIME_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/TimeSpan.h>


namespace Noesis
{

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the different types of behavior for a KeyTime
////////////////////////////////////////////////////////////////////////////////////////////////////
enum KeyTimeType
{
    /// Specifies that the allotted total time for an animation sequence is divided evenly amongst 
    /// each of the key frames.
    KeyTimeType_Uniform,
    /// Specifies that each KeyTime value is expressed as a percentage of the total time allotted 
    /// for a given animation sequence.
    KeyTimeType_Percent,
    /// Specifies that each KeyTime is expressed as a TimeSpan value relative to the BeginTime of 
    /// an animation sequence.
    KeyTimeType_TimeSpan,
    /// Specifies that adjacent KeyFrames are each allotted a slice of time proportional to their 
    /// length, respectively. The overall goal is to produce a length value that keeps the pace of 
    /// the animation sequence constant.
    KeyTimeType_Paced
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the precise timing when a particular key frame should take place
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API KeyTime
{
public:
    /// Default constructor
    KeyTime();

    /// Creates a new KeyTime instance, with the KeyTimeType property initialized to the value of 
    /// the specified parameter
    static KeyTime FromPercent(NsFloat32 value);
    
    /// Creates a new KeyTime instance, with the KeyTimeType property initialized to the value of 
    /// the specified parameter
    static KeyTime FromTimeSpan(const TimeSpan& timeSpan);
    
    /// Creates a Paced KeyTime which creates timing behavior resulting in an animation that 
    /// interpolates at a constant rate
    static KeyTime Paced();

    /// Creates a Uniform KeyTime which divides the allotted time of the animation evenly between 
    /// key frames
    static KeyTime Uniform();

    /// Generates a string representation of the point
    /// The string has the following form: "Uniform", "Paced", "21.5%", or a TimeSpan: "0:0:1"
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Creates a KeyTime from a string
    static KeyTime Parse(const NsChar* str);

    /// Safe version of Parse function
    static NsBool TryParse(const NsChar* str, KeyTime& result);
    
    /// Gets the KeyTime type
    inline KeyTimeType GetType() const;
    
    /// Returns the TimeSpan value for a KeyTime of type KeyTimeType_TimeSpan
    inline const TimeSpan& GetTimeSpan() const;
    
    /// Returns the percent value for a KeyTime of type KeyTimeType_Percent
    inline NsFloat32 GetPercent() const;

    /// Compares two KetTime objects
    //@{
    NsBool operator==(const KeyTime& other) const;
    NsBool operator!=(const KeyTime& other) const;
    //@}

private:
    KeyTime(NsFloat32 percent);
    KeyTime(const TimeSpan& timeSpan);

private:
    KeyTimeType mType;
    NsFloat32 mPercent;
    TimeSpan mTimeSpan;
    
    NS_DECLARE_REFLECTION(KeyTime, Core::NoParent)
};

}
}


#include <NsGui/KeyTime.inl>


#endif
