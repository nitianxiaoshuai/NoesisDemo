////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_HEADEREDITEMSCONTROL_H__
#define __GUI_HEADEREDITEMSCONTROL_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ItemsControl.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DataTemplate;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that contains multiple items and has a header.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.headereditemscontrol.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API HeaderedItemsControl: public ItemsControl
{
public:
    /// Constructor
    HeaderedItemsControl();

    /// Destructor
    ~HeaderedItemsControl();

    /// Gets a value that indicates whether this HeaderedItemsControl has a header
    NsBool GetHasHeader() const;

    /// Gets or sets the item that labels the control
    //@{
    Core::BaseComponent* GetHeader() const;
    void SetHeader(Core::BaseComponent* header);
    void SetHeader(const NsChar* header);
    //@}

    /// Gets or sets a composite string that specifies how to format the Header property if it is
    /// displayed as a string.
    //@{
    const NsChar* GetHeaderStringFormat() const;
    void SetHeaderStringFormat(const NsChar* headerStringFormat);
    //@}

    /// Gets or sets the template used to display the contents of the control's header
    //@{
    DataTemplate* GetHeaderTemplate() const;
    void SetHeaderTemplate(DataTemplate* value);
    //@}

    /// Gets or sets the object that provides custom selection logic for a template used to display 
    /// the header of each item. 
    //@{
    DataTemplateSelector* GetHeaderTemplateSelector() const;
    void SetHeaderTemplateSelector(DataTemplateSelector* value);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* HasHeaderProperty; // [CommonDependencyProperty]
    static const DependencyProperty* HeaderProperty; // [CommonDependencyProperty]
    static const DependencyProperty* HeaderStringFormatProperty; // [CommonDependencyProperty]
    static const DependencyProperty* HeaderTemplateProperty; // [CommonDependencyProperty]
    static const DependencyProperty* HeaderTemplateSelectorProperty; // [CommonDependencyProperty]
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From FrameworkElement
    //@{
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    //@}

protected:
    virtual void OnHeaderChanged(Core::BaseComponent* oldHeader, Core::BaseComponent* newHeader);

private:
    friend class ItemsControl;
    void PrepareContainer(Core::BaseComponent* item, ItemsControl* parent);
    void PrepareHierarchy(Core::BaseComponent* item, ItemsControl* parent);
    void ClearContainer(Core::BaseComponent* item);
    DataTemplate* FindHeaderTemplate(BaseComponent* item, ItemsControl* parent) const;

private:
    NsBool mHeaderAsLogicalChild;

    NS_DECLARE_REFLECTION(HeaderedItemsControl, ItemsControl)
};

}
}

#endif