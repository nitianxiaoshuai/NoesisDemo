////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRIDVIEWCOLUMN_H__
#define __GUI_GRIDVIEWCOLUMN_H__


#include <Noesis.h>
#include <NsGui/ControlsApi.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class Style;
class DataTemplate;
class DataTemplateSelector;
class BaseBindingExpression;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a column that displays data.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.gridviewcolumn.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CONTROLS_API GridViewColumn: public DependencyObject, public IUITreeNode
{
public:
    GridViewColumn();
    ~GridViewColumn();

    /// Gets the actual width of a GridViewColumn.
    NsFloat32 GetActualWidth() const;
    void SetActualWidth(NsFloat32 width);

    /// Event that is fired when ActualWidth changes
    typedef Core::Delegate<void (GridViewColumn* sender)> ActualWidthChangedDelegate;
    ActualWidthChangedDelegate& ActualWidthChanged();

    /// Gets or sets the template to use to display the contents of a column cell
    //@{
    DataTemplate* GetCellTemplate() const;
    void SetCellTemplate(DataTemplate* dataTemplate);
    //@}

    /// Gets or sets a DataTemplateSelector that determines the template to use to display cells in
    /// a column
    //@{
    DataTemplateSelector* GetCellTemplateSelector() const;
    void SetCellTemplateSelector(DataTemplateSelector* selector);
    //@}

    /// Gets or sets the data item to bind to for this column
    //@{
    BaseBindingExpression* GetDisplayMemberBinding() const;
    void SetDisplayMemberBinding(BaseBindingExpression* binding);
    //@}
 
    /// Gets or sets the content of the header of a GridViewColumn
    //@{
    Core::BaseComponent* GetHeader() const;
    void SetHeader(Core::BaseComponent* header);
    //@} 
 
    /// Gets or sets the style to use for the header of the GridViewColumn
    //@{
    Style* GetHeaderContainerStyle() const;
    void SetHeaderContainerStyle(Style* style);
    //@}
 
    /// Gets or sets a composite string that specifies how to format the Header property if it is 
    /// displayed as a string
    //@{
    const NsChar* GetHeaderStringFormat() const;
    void SetHeaderStringFormat(const NsChar* format);
    //@}
 
    /// Gets or sets the template to use to display the content of the column header
    //@{
    DataTemplate* GetHeaderTemplate() const;
    void SetHeaderTemplate(DataTemplate* headerTemplate);
    //@}

    /// Gets or sets the DataTemplateSelector that provides logic to select the template to use to
    /// display the column header
    //@{
    DataTemplateSelector* GetHeaderTemplateSelector() const;
    void SetHeaderTemplateSelector(DataTemplateSelector* selector);
    //@}
 
    /// Gets or sets the width of the column. This is a dependency property.  
    //@{
    NsFloat32 GetWidth() const;
    void SetWidth(NsFloat32 width);
    //@}

    NsFloat32 GetDesiredWidth() const;
    NsFloat32 EnsureWidth(NsFloat32 width);

    enum MeasureState
    {
        /// Measure has not been done yet on this column
        MeasureState_None,
        /// Header measure has been done
        MeasureState_Header,
        /// Items measure has been done
        MeasureState_Items,
        /// Header and items measure has been done, or fixed width was set
        MeasureState_Fixed
    };
    
    MeasureState GetMeasureState() const;
    void SetMeasureState(MeasureState state); // To be used only from GridViewRowPresenterBase

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* CellTemplateProperty;
    static const DependencyProperty* CellTemplateSelectorProperty;
    static const DependencyProperty* HeaderProperty;
    static const DependencyProperty* HeaderContainerStyleProperty;
    static const DependencyProperty* HeaderStringFormatProperty;
    static const DependencyProperty* HeaderTemplateProperty;
    static const DependencyProperty* HeaderTemplateSelectorProperty;
    static const DependencyProperty* WidthProperty;
    //@}

protected:
    /// From DependencyProperty
    //@{
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue);
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    IUITreeNode* mOwner;
    NsFloat32 mActualWidth;
    ActualWidthChangedDelegate mActualWidthChanged;
    
    // TODO: This should be BaseBinding instead on BaseBindingExpression
    Ptr<BaseBindingExpression> mDisplayMemberBinding;
    
    MeasureState mMeasureStateInternal;
    NsFloat32 mDesiredWidthInternal;
    //NsInt mIndex;

    NS_DECLARE_REFLECTION(GridViewColumn, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif