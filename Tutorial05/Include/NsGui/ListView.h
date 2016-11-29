////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LISTVIEW_H__
#define __GUI_LISTVIEW_H__


#include <Noesis.h>
#include <NsGui/ControlsApi.h>
#include <NsGui/ListBox.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class BaseView;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that displays a list of data items.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.listview.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CONTROLS_API ListView: public ListBox
{
public:
    ListView();
    ~ListView();
    
    /// Gets or sets an object that defines how the data is styled and organized in a ListView control
    //@{
    BaseView* GetView() const;
    void SetView(BaseView* view);
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* ViewProperty;
    //@}

protected:
    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    void PrepareContainerForItemOverride(DependencyObject* element,
        Core::BaseComponent* item) const;
    NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;
    //void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);
    //@}

    NS_DECLARE_REFLECTION(ListView, ListBox)
};

}
}

#endif