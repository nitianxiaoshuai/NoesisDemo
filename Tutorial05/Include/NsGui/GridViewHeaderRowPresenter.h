////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRIDVIEWHEADERROWPRESENTER_H__
#define __GUI_GRIDVIEWHEADERROWPRESENTER_H__


#include <Noesis.h>
#include <NsGui/ControlsApi.h>
#include <NsGui/BaseGridViewRowPresenter.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class ContextMenu;
class DataTemplate;
class DataTemplateSelector;
class Style;
class GridViewColumnHeader;
class ScrollViewer;
class Rectangle;
struct ScrollChangedEventArgs;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an object that is used to define the layout of a row of column headers. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.gridviewheaderrowpresenter.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CONTROLS_API GridViewHeaderRowPresenter: public BaseGridViewRowPresenter
{
public:
    GridViewHeaderRowPresenter();
    ~GridViewHeaderRowPresenter();
    
    /// Gets or sets a value that indicates whether columns can change positions.
    //@{
    NsBool GetAllowsColumnReorder() const;
    void SetAllowsColumnReorder(NsBool value);
    //@}
    
    /// Gets or sets the Style to use for the column headers
    //@{
    Style* GetColumnHeaderContainerStyle() const;
    void SetColumnHeaderContainerStyle(Style* style);
    //@}
    
    /// Gets or sets a ContextMenu for the column headers
    //@{
    ContextMenu* GetColumnHeaderContextMenu() const;
    void SetColumnHeaderContextMenu(ContextMenu* menu);
    //@}
    
    /// Gets or sets a composite string that specifies how to format the column headers if they are 
    /// displayed as strings
    //@{
    const NsChar* GetColumnHeaderStringFormat() const;
    void SetColumnHeaderStringFormat(const NsChar* format);
    //@}
    
    /// Gets or sets the template to use to display the column headers
    //@{
    DataTemplate* GetColumnHeaderTemplate() const;
    void SetColumnHeaderTemplate(DataTemplate* dataTemplate);
    //@}
    
    /// Gets or sets a DataTemplateSelector that provides logic that selects the data template to 
    /// use to display a column header
    //@{
    DataTemplateSelector* GetColumnHeaderTemplateSelector() const;
    void SetColumnHeaderTemplateSelector(DataTemplateSelector* selector);
    //@}
    
    /// Gets or sets the content for a tooltip for the column header row
    //@{
    Core::BaseComponent* GetColumnHeaderToolTip() const;
    void SetColumnHeaderToolTip(Core::BaseComponent* tooltip);
    //@}
    
public:
    /// Dependency properties
    //@{
    static const DependencyProperty* AllowsColumnReorderProperty;
    static const DependencyProperty* ColumnHeaderContainerStyleProperty;
    static const DependencyProperty* ColumnHeaderContextMenuProperty;
    static const DependencyProperty* ColumnHeaderStringFormatProperty;
    static const DependencyProperty* ColumnHeaderTemplateProperty;
    static const DependencyProperty* ColumnHeaderTemplateSelectorProperty;
    static const DependencyProperty* ColumnHeaderToolTipProperty;
    //@}

protected:
    /// From UIElement
    //@{
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e);
    void OnMouseMove(const MouseEventArgs& e);
    //@}

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

    /// From BaseGridViewRowPresenter
    //@{
    void OnColumnsChanged(GridViewColumnCollection* oldColumns,
        GridViewColumnCollection* newColumns);
    void OnColumnsCollectionChanged();
    //@}

private:
    void OnScrollChanged(Core::BaseComponent* sender, const ScrollChangedEventArgs& args);

    void UpdateColumnHeaders();
    NsBool IsValidDragPosition() const;
    NsSize CalculateFloatingDestinationIndex() const;
    NsFloat32 CalculateFloatingDestinationOffset() const;

private:
    Ptr<GridViewColumnHeader> mPaddingHeader;
    Ptr<GridViewColumnHeader> mFloatingHeader;
    Ptr<Rectangle> mFloatingDestination;
    ScrollViewer* mHeaderScrollViewer;
    ScrollViewer* mItemsScrollViewer;

    GridViewColumnHeader* mDragHeader;
    Drawing::Point mDragStart;
    Drawing::Point mDragPos;
    NsBool mDragEnabled;
    NsBool mDragging;

    NS_DECLARE_REFLECTION(GridViewHeaderRowPresenter, BaseGridViewRowPresenter)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}

#endif
