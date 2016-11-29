////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRIGGERCOLLECTION_H__
#define __GUI_TRIGGERCOLLECTION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Collection.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class FrameworkElement;
class BaseTrigger;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TriggerCollection
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TriggerCollection: public Collection
{
public:
    TriggerCollection();
    TriggerCollection(FrameworkElement* owner);

    static void Register(TriggerCollection* triggers, FrameworkElement* element,
        FrameworkElement* nameScope, NsBool skipSourceName, NsBool skipTargetName,
        NsUInt8 priority);
    static void Unregister(TriggerCollection* triggers, FrameworkElement* element,
        NsBool skipSourceName);

private:
    /// From Collection
    //@{
    void OnItemAdded(Core::BaseComponent* item, NsSize index);
    void OnItemRemoved(Core::BaseComponent* item, NsSize index);
    void CheckItem(Core::BaseComponent* item) const;
    //@}

    NS_DECLARE_REFLECTION(TriggerCollection, Collection)
};

}
}


#endif
