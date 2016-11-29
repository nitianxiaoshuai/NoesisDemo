////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CLOCKGROUP_H__
#define __GUI_CLOCKGROUP_H__


#include <Noesis.h>
#include <NsGui/Clock.h>

#include <NsCore/Vector.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class TimelineGroup;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An assemblage of Clock types with behavior based off of a TimelineGroup.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.clockgroup.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API ClockGroup: public Clock
{
public:
    ClockGroup(TimelineGroup* timelineGroup, NsBool controllable);
    ~ClockGroup();

    /// Gets the children collection of this ClockGroup.
    void Add(Clock* clock);
    
    /// Gets the TimelineGroup object that dictates the behavior of this ClockGroup instance.
    //Ptr<TimelineGroup> GetTimeline() const;
    
    /// Get number of children
    NsSize GetChildrenCount() const;
    
    /// Get child at index position
    Clock* GetChild(NsSize index) const;
    
    /// From Clock
    //@{
    NsBool Tick(NsFloat64 time, ClockState parentState);
    //@}
    
private:
    /// From Clock
    //@{
    void SetOwner(TimeManager* owner);
    void Recycle(TimeManager* owner);
    //@}

private:
    NsVector<Ptr<Clock> > mChildren;

    NS_DECLARE_REFLECTION(ClockGroup, Clock)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
