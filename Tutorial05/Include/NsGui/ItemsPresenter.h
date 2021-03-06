////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ITEMSPRESENTER_H__
#define __GUI_ITEMSPRESENTER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class Panel;
class ItemContainerGenerator;
class ScrollContentPresenter;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used within the template of an item control to specify the place in the control's visual tree
/// where the ItemsPanel defined by the ItemsControl is to be added.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.itemspresenter.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ItemsPresenter: public FrameworkElement
{
public:
    ItemsPresenter();

protected:
    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    void OnTemplatedParentChanged(FrameworkElement* oldParent, FrameworkElement* newParent);
    //@}

private:
    friend class ItemsControl;
    friend class ItemContainerGenerator;
    friend class ScrollContentPresenter;

    static ItemsPresenter* FromPanel(Panel* panel);
    ItemContainerGenerator* GetGenerator() const;

    void InvalidateItemsHost();
    void RefreshItemsHost();

    void SetScrollPresenter(ScrollContentPresenter* scrollPresenter);
    void UpdateScrollPresenter();

private:
    NsBool mRefreshItemsHost;
    ScrollContentPresenter* mScrollPresenter;

    NS_DECLARE_REFLECTION(ItemsPresenter, FrameworkElement)
};

}
}

#endif
