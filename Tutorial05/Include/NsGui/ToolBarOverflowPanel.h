////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TOOLBAROVERFLOWPANEL_H__
#define __GUI_TOOLBAROVERFLOWPANEL_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used to arrange overflow ToolBar items.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.toolbaroverflowpanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ToolBarOverflowPanel: public Panel
{
public:
    ToolBarOverflowPanel();

    /// Gets or sets the recommended width for this panel before items flow to the next line
    //@{
    NsFloat32 GetWrapWidth() const;
    void SetWrapWidth(NsFloat32 wrapWidth);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* WrapWidthProperty;
    //@}

protected:
    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

    /// From Panel
    //@{
    Ptr<UIElementCollection> CreateChildrenCollection(FrameworkElement* logicalParent);
    //@}

private:
    void ArrangeLine(NsSize start, NsSize end, NsFloat32 y, NsFloat32 height);

private:
    NsFloat32 mCalculatedWrapWidth;

    NS_DECLARE_REFLECTION(ToolBarOverflowPanel, Panel)
};

}
}


#endif
