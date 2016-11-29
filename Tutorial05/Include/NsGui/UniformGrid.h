////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_UNIFORMGRID_H__
#define __GUI_UNIFORMGRID_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a way to arrange content in a grid where all the cells in the grid have the same size.
///
/// .. code-block:: xml
///
///    <Grid xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///        Height="200" Width="250">
///
///        <UniformGrid>
///            <Button Content="Button 1"/>
///            <Button Content="Button 2"/>
///            <Button Content="Button 3"/>
///            <Button Content="Button 4"/>
///        </UniformGrid>
///
///    </Grid>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.uniformgrid.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API UniformGrid: public Panel
{
public:
    /// Constructor
    UniformGrid();
    ~UniformGrid();

    /// Gets or sets the number of leading blank cells in the first row of the grid
    //@{
    NsUInt32 GetFirstColumn() const;
    void SetFirstColumn(NsUInt32 firstColumn);
    //@}

    /// Gets or set the number of columns that are in the grid
    //@{
    NsUInt32 GetColumns() const;
    void SetColumns(NsUInt32 columns);
    //@}

    /// Gets or sets the number of rows that are in the grid
    //@{
    NsUInt32 GetRows() const;
    void SetRows(NsUInt32 rows);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* FirstColumnProperty;
    static const DependencyProperty* ColumnsProperty;
    static const DependencyProperty* RowsProperty;
    //@}

protected:
    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    void CalculateCells();

private:
    NsUInt32 mNumColumns;
    NsUInt32 mNumRows;

    NS_DECLARE_REFLECTION(UniformGrid, Panel)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
