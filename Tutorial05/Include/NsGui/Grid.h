////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRID_H__
#define __GUI_GRID_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>
#include <NsGui/GridLength.h>

#include <NsCore/Vector.h>
#include <NsCore/Set.h>
#include <NsCore/HashMap.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class ColumnDefinition;
class RowDefinition;
template<class T> class TypedCollection;
//@}

typedef Noesis::Gui::TypedCollection<Noesis::Gui::ColumnDefinition> ColumnDefinitionCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::RowDefinition> RowDefinitionCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a flexible grid area that consists of columns and rows.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.grid.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Grid: public Panel
{
public:
    /// Constructor
    Grid();
    ~Grid();

    /// Gets column definitions collection
    ColumnDefinitionCollection* GetColumnDefinitions() const;

    /// Gets a value that indicates which column child within a Grid should appear in
    static NsUInt32 GetColumn(const DependencyObject* element);
    /// Sets a value that indicates which column child within a Grid should appear in
    static void SetColumn(DependencyObject* element, NsUInt32 column);

    /// Gets a value that indicates the number of columns that child spans within a grid
    static NsUInt32 GetColumnSpan(const DependencyObject* element);
    /// Sets a value that indicates the number of columns that child spans within a grid
    static void SetColumnSpan(DependencyObject* element, NsUInt32 columnSpan);

    /// Gets a value that indicates that multiple Grid elements are sharing size information
    static NsBool GetIsSharedSizeScope(const DependencyObject* element);
    /// Sets a value that indicates that multiple Grid elements are sharing size information
    static void SetIsSharedSizeScope(DependencyObject* element, NsBool value);

    /// Gets row definitions collection
    RowDefinitionCollection* GetRowDefinitions() const;

    /// Gets a value that represents the distance between the top of an element and the top
    /// of its parent Canvas
    static NsUInt32 GetRow(const DependencyObject* element);
    /// Sets a value that represents the distance between the top of an element and the top
    /// of its parent Canvas
    static void SetRow(DependencyObject* element, NsUInt32 row);

    /// Gets a value that represents the distance between the top of an element and the top
    /// of its parent Canvas
    static NsUInt32 GetRowSpan(const DependencyObject* element);
    /// Sets a value that represents the distance between the top of an element and the top
    /// of its parent Canvas
    static void SetRowSpan(DependencyObject* element, NsUInt32 rowSpan);

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ColumnProperty; // attached property
    static const DependencyProperty* ColumnSpanProperty; // attached property
    static const DependencyProperty* IsSharedSizeScopeProperty; // attached property
    static const DependencyProperty* RowProperty; // attached property
    static const DependencyProperty* RowSpanProperty; // attached property
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const;
    Visual* GetVisualChild(NsSize index) const;
    void OnVisualChildrenChanged(Visual* added, Visual* removed);
    //@}

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    // Simple measure of children
    Drawing::Size SimpleMeasure(const Drawing::Size& availableSize);

    // Simple arrange of children
    Drawing::Size SimpleArrange(const Drawing::Size& finalSize);

    // Updates private cell structures
    void UpdateCellStructure();
    void UpdateElementCache();

    // Gets element column and row info
    //@{
    void GetColumnInfo(const UIElement* child, NsSize numCols, NsSize& col, NsSize& colSpan) const;
    void GetRowInfo(const UIElement* child, NsSize numRows, NsSize& row, NsSize& rowSpan) const;
    //@}

    struct DefinitionsInfo;
    struct DefinitionCache
    {
        GridUnitType type;
        NsFloat32 size;
        NsFloat32 minSize;
        NsFloat32 maxSize;

        DefinitionCache();
        DefinitionCache(GridUnitType t, NsFloat32 s, NsFloat32 mins, NsFloat32 maxs);
    };

    typedef NsVector<DefinitionCache> DefinitionCacheVector;
    typedef NsVector<NsFloat32> FloatVector;

    // Measure helpers
    //@{
    Drawing::Size DoMeasure(const Drawing::Size& availableSize);
    void MeasureElements(NsSize start, NsSize end);
    NsFloat32 MeasureSizes(const DefinitionCacheVector& defVec, FloatVector& sizes);
    void UpdateSizes(const DefinitionCacheVector& defVec, NsSize index, NsSize span,
        NsBool allAutoSpan, NsFloat32 size, NsFloat32 starTotal, FloatVector& sizes);
    void SolveDef(NsFloat32 availableSize, const DefinitionsInfo& info, const FloatVector& sizes,
        FloatVector& constraints, NsFloat32& usedSize);
    //@}

    // Arrange helpers
    //@{
    void DoArrange(const Drawing::Size& finalSize);
    void ArrangeDef(NsFloat32 finalSize, NsFloat32 desiredSize, NsBool isDesiredSize,
        const DefinitionsInfo& info, const FloatVector& measureSizes,
        FloatVector& arrangeSizes, FloatVector& arrangePositions);
    void UpdateArrangeSize(NsSize index, FloatVector& arrangeSizes, NsFloat32 size,
        NsFloat32& usedSize, NsFloat32 star, NsFloat32& usedStar);
    //@}

    // Determines if grid size is determined by children
    void IsDesiredSize(const Drawing::Size& size, NsBool& isDesiredWidth, NsBool& isDesiredHeight);
    NsBool IsDesiredSize(NsFloat32 finalSize, NsFloat32 desiredSize, NsFloat32 localSize) const;

    // Distributes desired size within the cell span
    void DistributeSize(NsSize index, NsSize span, NsBool allAuto, NsFloat32 size,
        NsFloat32 starTotal, const DefinitionCacheVector& defVec, FloatVector& vec) const;

    // Calculates the size of a range of cells
    NsFloat32 GetSpanSize(const FloatVector& vec, NsSize index, NsSize span) const;

    // Indicates if all cells in the span are auto
    void GetAllAutoSpanAndOrder(const DefinitionCacheVector& defVec, NsSize index, NsSize span,
        NsBool& allAutoSpan, NsSize& orderType) const;

    // Notifies when a collection of column or row definitions changed
    void OnCollectionChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);

    // Notifies when the definition of a column or row changes
    void OnDefinitionChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);

    // Invalidates grid cell cache
    void InvalidateCellCache();

    // Creates column/row definitions if necessary
    void EnsureColumns() const;
    void ConnectColumns() const;
    void DisconnectColumns();
    void EnsureRows() const;
    void ConnectRows() const;
    void DisconnectRows();

    // Detects changes in cell properties of children elements
    static void StaticCellChanged(DependencyObject* obj,
        const DependencyPropertyChangedEventArgs& args);

private:
    mutable Ptr<ColumnDefinitionCollection> mColumnDefinitions;
    mutable Ptr<RowDefinitionCollection> mRowDefinitions;

    NsBool mDirtyCellStructure;
    NsBool mDirtyElementCache;

    struct ElementInfo
    {
        UIElement* element;
        NsSize col;
        NsSize colSpan;
        NsSize row;
        NsSize rowSpan;
        NsSize order;
        NsBool allAutoRowSpan;
        NsBool allAutoColSpan;
    };

    typedef NsVector<ElementInfo> ElementInfoVector;
    typedef NsVector<NsSize> IndexVector;

    struct OrderedSize
    {
        NsFloat32 size;
        NsSize index;

        OrderedSize(NsFloat32 s = 0.0f, NsSize i = 0);
        NsBool operator<(const OrderedSize& other) const;
    };

    typedef NsMultiset<OrderedSize> OrderedSizes;

    struct DefinitionsInfo
    {
        DefinitionCacheVector definitions;
        IndexVector pixelDefinitions;
        IndexVector autoDefinitions;
        IndexVector starDefinitions;
        NsFloat32 starTotal;

        DefinitionsInfo();
        void Reset();
        void Reserve(NsSize count);
        void AddDefinition(const DefinitionCache& def);
    };

    struct MeasureInfo
    {
        // Contains the constraints applied to each cell element
        FloatVector colConstraints;
        FloatVector rowConstraints;

        // Stores the desired size of each cell
        FloatVector colSizes;
        FloatVector rowSizes;

        // During measure process stores the used size by Pixel and Auto cells, to calculate the
        // remaining space for Star cells. After measure represents the desired size of the grid
        NsFloat32 usedWidth;
        NsFloat32 usedHeight;
    };

    struct ArrangeInfo
    {
        FloatVector colSizes;
        FloatVector rowSizes;
        FloatVector colPositions;
        FloatVector rowPositions;
    };

    typedef NsHashMap<NsSize, IndexVector> OrderedIndices;

    struct CellStructureInfo: public Core::BaseComponent
    {
        DefinitionsInfo colInfo;
        DefinitionsInfo rowInfo;
        ElementInfoVector elements;
        OrderedIndices orderedIndices;
        IndexVector orderedElements;
        OrderedSizes orderedSizes;
        NsSize solveColsIndex;
        NsSize solveRowsIndex;
        MeasureInfo measureInfo;
        ArrangeInfo arrangeInfo;

        void ResetCellInfo();
        void ResetElementCache();
        void ResetMeasureInfo();
        void ResetArrangeInfo();

        NsSize GetNumOrderedIndices(NsSize cell);
        void AddOrderedElements(NsSize cell);

    private:
        void ResetMeasureDef(const DefinitionsInfo& info, FloatVector& constraints,
            FloatVector& sizes, NsFloat32& usedSize);
        void ResetArrangeDef(const DefinitionsInfo& info, FloatVector& sizes,
            FloatVector& positions);
    };

    Ptr<CellStructureInfo> mCellInfo;

    NS_DECLARE_REFLECTION(Grid, Panel)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
