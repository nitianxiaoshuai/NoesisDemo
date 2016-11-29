////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRIDVIEW_H__
#define __GUI_GRIDVIEW_H__


#include <Noesis.h>
#include <NsGui/ControlsApi.h>
#include <NsGui/BaseView.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class ContextMenu;
class DataTemplate;
class DataTemplateSelector;
class GridViewColumn;
class Style;
struct NotifyCollectionChangedEventArgs;
template<class T> class TypedCollection;
//@}

typedef Noesis::Gui::TypedCollection<Noesis::Gui::GridViewColumn> GridViewColumnCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a view mode that displays data items in columns for a ListView control.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.gridview.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CONTROLS_API GridView: public BaseView
{
public:
    GridView();
    ~GridView();
    
    /// Gets or sets whether columns in a GridView can be reordered by a drag-and-drop operation
    //@{
    NsBool GetAllowsColumnReorder() const;
    void SetAllowsColumnReorder(NsBool value);
    //@}
    
    /// Gets or sets the style to apply to column headers
    //@{
    Style* GetColumnHeaderContainerStyle() const;
    void SetColumnHeaderContainerStyle(Style* style);
    //@}
    
    /// Gets or sets a ContextMenu for the GridView
    //@{
    ContextMenu* GetColumnHeaderContextMenu() const;
    void SetColumnHeaderContextMenu(ContextMenu* menu);
    //@}
    
    /// Gets or sets a composite string that specifies how to format the column headers of the 
    /// GridView if they are displayed as strings
    //@{
    const NsChar* GetColumnHeaderStringFormat() const;
    void SetColumnHeaderStringFormat(const NsChar* format);
    //@}
    
    /// Gets or sets a template to use to display the column headers
    //@{
    DataTemplate* GetColumnHeaderTemplate() const;
    void SetColumnHeaderTemplate(DataTemplate* dataTemplate);
    //@}
    
    /// Gets or sets the selector object that provides logic for selecting a template to use for 
    /// each column header
    //@{
    DataTemplateSelector* GetColumnHeaderTemplateSelector() const;
    void SetColumnHeaderTemplateSelector(DataTemplateSelector* selector);
    //@}
    
    /// Gets or sets the content of a tooltip that appears when the mouse pointer pauses over one 
    /// of the column headers
    //@{
    Core::BaseComponent* GetColumnHeaderToolTip() const;
    void SetColumnHeaderToolTip(Core::BaseComponent* tooltip);
    //@}
    
    /// Gets the collection of GridViewColumn objects that is defined for this GridView
    GridViewColumnCollection* GetColumns() const;
    
    /// Gets or sets the attached property that contains the GridViewColumnCollection
    //@{
    //GetColumnCollection();
    //SetColumnCollection();
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* AllowsColumnReorderProperty;
    static const DependencyProperty* ColumnHeaderContainerStyleProperty;
    static const DependencyProperty* ColumnHeaderContextMenuProperty;
    static const DependencyProperty* ColumnHeaderStringFormatProperty;
    static const DependencyProperty* ColumnHeaderTemplateProperty;
    static const DependencyProperty* ColumnHeaderTemplateSelectorProperty;
    static const DependencyProperty* ColumnHeaderToolTipProperty;
    static const DependencyProperty* ColumnCollectionProperty; // Attached

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}
    
    /// From BaseView
    //@{
    void ClearItem(ListViewItem* item);
    void PrepareItem(ListViewItem* item);
    //@}
    
private:
    void ColumnsChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);
    void EnsureColumns() const;

private:
    mutable Ptr<GridViewColumnCollection> mColumns;

    NS_DECLARE_REFLECTION(GridView, BaseView)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif