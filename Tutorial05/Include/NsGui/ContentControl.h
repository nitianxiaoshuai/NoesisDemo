////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONTENTCONTROL_H__
#define __GUI_CONTENTCONTROL_H__


#include <Noesis.h>
#include <NsGui/Control.h>


namespace Noesis
{
namespace Gui
{

/// Forward declaration
//@{
class DataTemplate;
class DataTemplateSelector;
class ItemsControl;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control with a single piece of content.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.contentcontrol.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ContentControl: public Control
{
public:
    /// Constructor
    ContentControl();

    /// Destructor
    ~ContentControl();

    /// Gets or sets the content of a ContentControl
    //@{
    Core::BaseComponent* GetContent() const;
    void SetContent(Core::BaseComponent* content);
    void SetContent(const NsChar* content);
    //@}

    /// Gets or sets the template used to display the content of the ContentControl
    //@{
    DataTemplate* GetContentTemplate() const;
    void SetContentTemplate(DataTemplate* dataTemplate);
    //@}

    /// Gets or sets a data template selector that provides custom logic for choosing the template
    /// used to display the content
    //@{
    DataTemplateSelector* GetContentTemplateSelector() const;
    void SetContentTemplateSelector(DataTemplateSelector* selector);
    //@}

    /// Gets a value that indicates whether the ContentControl contains content
    NsBool GetHasContent() const;

    /// From BaseObject
    //@{
    NsString ToString() const;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ContentProperty;
    static const DependencyProperty* ContentTemplateProperty;
    static const DependencyProperty* ContentTemplateSelectorProperty;
    static const DependencyProperty* HasContentProperty;
    //@}

protected:
    /// Content property value changed event
    //@{
    virtual void OnContentChanged(Core::BaseComponent* oldContent, Core::BaseComponent* newContent);
    //@}

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From FrameworkElement
    //@{
    NsSize GetLogicalChildrenCount() const;
    BaseComponent* GetLogicalChild(NsSize index) const;
    //@}

protected:
    NsBool mContentAsLogicalChild;


    friend class ItemsControl;
    void PrepareContainer(Core::BaseComponent* item, DataTemplate* itemTemplate,
        DataTemplateSelector* itemTemplateSelector);
    void ClearContainer(Core::BaseComponent* item);

    NS_DECLARE_REFLECTION(ContentControl, Control)
};

}
}

#endif
