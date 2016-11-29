////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONTENTPRESENTER_H__
#define __GUI_CONTENTPRESENTER_H__


#include <Noesis.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DataTemplate;
class DataTemplateSelector;
class TextBlock;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Displays the content of ContentControl.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.contentpresenter.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ContentPresenter: public FrameworkElement
{
public:
    /// Constructor
    ContentPresenter();

    /// Destructor
    ~ContentPresenter();

    /// Gets or sets content
    //@{
    Core::BaseComponent* GetContent() const;
    void SetContent(Core::BaseComponent* content);
    void SetContent(const NsChar* content);
    //@}
    
    /// Gets or sets the base name to use during automatic aliasing.
    //@{
    const NsChar* GetContentSource() const;
    void SetContentSource(const NsChar* source);
    //@}
    
    /// Gets or sets the template used to display the content of the control. 
    //@{
    DataTemplate* GetContentTemplate() const;
    void SetContentTemplate(DataTemplate* value);
    //@}
    
    /// Gets or sets the DataTemplateSelector, which allows the application writer to provide 
    /// custom logic for choosing the template that is used to display the content of the control.
    //@{
    DataTemplateSelector* GetContentTemplateSelector() const;
    void SetContentTemplateSelector(DataTemplateSelector* selector);
    //@}

protected:
    // Inheritors must call this function before measuring the content presenter
    void RefreshVisualTree();

    // Invoked when Content property changes
    virtual void OnContentChanged(Core::BaseComponent* oldContent, Core::BaseComponent* newContent);

    /// From DependencyProperty
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    //@}

private:
    friend class ItemsControl;
    void PrepareContainer(Core::BaseComponent* item, DataTemplate* itemTemplate,
        DataTemplateSelector* itemTemplateSelector);
    void ClearContainer(Core::BaseComponent* item);

    void InvalidateVisualTree();

    void RemoveOldParent(Visual* child) const;
    TextBlock* EnsureDefaultTemplate();

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ContentProperty;
    static const DependencyProperty* ContentSourceProperty;
    static const DependencyProperty* ContentTemplateProperty;
    static const DependencyProperty* ContentTemplateSelectorProperty;
    //@}

private:
    NsBool mRefreshVisualTree;

    NS_DECLARE_REFLECTION(ContentPresenter, FrameworkElement)
};

}
}

#endif
