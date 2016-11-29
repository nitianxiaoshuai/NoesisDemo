////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TABPANEL_H__
#define __GUI_TABPANEL_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>

namespace Noesis
{

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Handles the layout of the TabItem objects on a TabControl.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.tabpanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TabPanel: public Panel
{
public:
    TabPanel();

protected:
    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

    NS_DECLARE_REFLECTION(TabPanel, Panel)
};

}
}

#endif