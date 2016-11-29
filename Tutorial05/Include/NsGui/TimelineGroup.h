////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TIMELINEGROUP_H__
#define __GUI_TIMELINEGROUP_H__


#include <Noesis.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/Timeline.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
template<class T> class TypedFreezableCollection;
//@}

typedef Noesis::Gui::TypedFreezableCollection<Noesis::Gui::Timeline> TimelineCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Abstract class that, when implemented represents a Timeline
/// that may contain a collection of child Timeline objects.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.timelinegroup.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API TimelineGroup: public Timeline
{
public:
    TimelineGroup();
    virtual ~TimelineGroup() = 0;
    
    /// Gets or sets the collection of child Timeline objects
    //@{
    TimelineCollection* GetChildren() const;
    void SetChildren(TimelineCollection* timelines);
    //@}

public:
    /// DependencyProperties
    //@{
    static const DependencyProperty* ChildrenProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

    /// From Timeline
    //@{
    Ptr<Clock> CreateClockCore(TimeManager* timeManager, NsBool hasControllableRoot);
    //@}

    NS_DECLARE_REFLECTION(TimelineGroup, Timeline)
};

}
}


#endif
