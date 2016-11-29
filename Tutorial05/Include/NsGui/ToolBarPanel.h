////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TOOLBARPANEL_H__
#define __GUI_TOOLBARPANEL_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/StackPanel.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class UIElementCollection;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Arranges ToolBar items inside a ToolBar.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.toolbarpanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ToolBarPanel: public StackPanel
{
public:
    ToolBarPanel();
    ~ToolBarPanel();

protected:
    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const;
    Visual* GetVisualChild(NsSize index) const;
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

    /// From Panel
    //@{
    Ptr<UIElementCollection> CreateChildrenCollection(FrameworkElement* logicalParent);
    void GenerateChildren();
    void OnItemsChangedOverride(Core::BaseComponent* sender, const ItemsChangedEventArgs& e);
    //@}

private:
    Ptr<UIElementCollection> mVisibleChildren;

    NS_DECLARE_REFLECTION(ToolBarPanel, StackPanel)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
