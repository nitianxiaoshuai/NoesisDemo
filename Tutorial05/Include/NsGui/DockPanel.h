////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DOCKPANEL_H__
#define __GUI_DOCKPANEL_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
enum Dock;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines an area where you can arrange child elements either horizontally or
/// vertically, relative to each other.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.dockpanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DockPanel: public Panel
{
public:
    /// Constructor
    DockPanel();

    /// Gets a value that indicates the position of a child element within a DockPanel
    static Dock GetDock(DependencyObject* element);
    /// Sets a value that indicates the position of a child element within a DockPanel
    static void SetDock(DependencyObject* element, Dock dock);

    /// Gets or sets a value that indicates whether the last child element within a DockPanel
    /// stretches to fill the remaining available space
    //@{
    NsBool GetLastChildFill() const;
    void SetLastChildFill(NsBool fill);
    //@}

private:
    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

    // Detects docking changes in children elements
    static void StaticDockChanged(DependencyObject* obj,
        const DependencyPropertyChangedEventArgs& args);

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* DockProperty; // attached property
    static const DependencyProperty* LastChildFillProperty;
    //@}

private:
    NS_DECLARE_REFLECTION(DockPanel, Panel)
};

}
}

#endif
