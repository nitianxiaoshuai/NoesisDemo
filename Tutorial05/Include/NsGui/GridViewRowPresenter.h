////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRIDVIEWROWPRESENTER_H__
#define __GUI_GRIDVIEWROWPRESENTER_H__


#include <Noesis.h>
#include <NsGui/ControlsApi.h>
#include <NsGui/BaseGridViewRowPresenter.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{

//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an object that specifies the layout of a row of data.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.gridviewrowpresenter.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CONTROLS_API GridViewRowPresenter: public BaseGridViewRowPresenter
{
public:
    GridViewRowPresenter();
    ~GridViewRowPresenter();
    
    /// Gets or sets the data content to display in a row
    //@{
    Core::BaseComponent* GetContent() const;
    void SetContent(Core::BaseComponent* content);
    //@}
    
public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ContentProperty;
    //@}
    
protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    //@}

private:
    void UpdateCells();
    Ptr<FrameworkElement> CreateCell(GridViewColumn* column, NsBool& contentHasParent);
    void UpdateContent(Core::BaseComponent* content);
    void UpdateCellContent(FrameworkElement* cell, GridViewColumn* column,
        Core::BaseComponent* content, NsBool& contentHasParent);

    NS_DECLARE_REFLECTION(GridViewRowPresenter, BaseGridViewRowPresenter)
};

}
}

#endif