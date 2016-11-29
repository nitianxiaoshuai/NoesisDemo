////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEMENU_H__
#define __GUI_BASEMENU_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ItemsControl.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that defines choices for users to select. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.menubase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseMenu: public ItemsControl
{
public:
    /// Constructor
    BaseMenu();
    
    /// Destructor
    virtual ~BaseMenu() = 0;

protected:
    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;
    void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);
    //@}

private:
    friend class MenuItem;
    Panel* GetMenuItemsPanel() const;

    NS_DECLARE_REFLECTION(BaseMenu, ItemsControl)
};

}
}

#endif