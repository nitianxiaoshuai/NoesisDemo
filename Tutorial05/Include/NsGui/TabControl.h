////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TABCONTROL_H__
#define __GUI_TABCONTROL_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Selector.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
enum Dock;
class TabItem;
class ContentPresenter;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that contains multiple items that share the same space on the screen. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.tabcontrol.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TabControl: public Selector
{
public:
    TabControl();
    ~TabControl();

    /// Gets or sets the DataTemplate to apply to any TabItem that does not have a ContentTemplate 
    // or ContentTemplateSelector property defined
    //@{
    DataTemplate* GetContentTemplate() const;
    void SetContentTemplate(DataTemplate* value);
    //@}

    /// Gets or sets a DataTemplateSelector that provides custom logic for choosing the template 
    /// that is used to display the content of the control
    //@{
    DataTemplateSelector* GetContentTemplateSelector() const;
    void SetContentTemplateSelector(DataTemplateSelector* selector);
    //@}

    /// Gets the content of the currently selected TabItem
    Core::BaseComponent* GetSelectedContent() const;

    /// Gets the DataTemplate of the currently selected item
    DataTemplate* GetSelectedContentTemplate() const;

    /// Gets the DataTemplateSelector of the currently selected item
    DataTemplateSelector* GetSelectedContentTemplateSelector() const;

    /// Gets or sets how tab headers align relative to the tab content
    //@{
    Dock GetTabStripPlacement() const;
    void SetTabStripPlacement(Dock dock);
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* ContentTemplateProperty;
    static const DependencyProperty* ContentTemplateSelectorProperty;
    static const DependencyProperty* SelectedContentProperty;
    static const DependencyProperty* SelectedContentTemplateProperty;
    static const DependencyProperty* SelectedContentTemplateSelectorProperty;
    static const DependencyProperty* TabStripPlacementProperty;
    //@}

protected:
    /// From Control
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    void UpdateVisualStates();
    //@}

    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;
    //@}

    /// From Selector
    //@{
    void OnContainersGeneratedOverride(Core::BaseComponent* sender, const EventArgs& e);
    void OnSelectionChanged(const SelectionChangedEventArgs& args);
    //@}

private:
    // Updates selected content host so it points to the new selected tab
    void UpdateSelectedContent(TabItem* selectedTab);

    TabItem* SelectedTab() const;

    friend class TabItem;
    void SelectTab(TabItem* tab);

private:
    Ptr<ContentPresenter> mSelectedContentHost;

    NS_DECLARE_REFLECTION(TabControl, Selector)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}

#endif