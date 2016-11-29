
////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #952]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BINDING_H__
#define __GUI_BINDING_H__


#include <Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/Symbol.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/BaseBinding.h>
#include <NsGui/CoreApi.h>
#include <NsGui/UpdateSourceTrigger.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/Enums.h>


NS_CFORWARD(Gui, DependencyObject)
NS_CFORWARD(Gui, DependencyProperty)
NS_CFORWARD(Gui, PropertyPath)
NS_CFORWARD(Gui, RelativeSource)
NS_CFORWARD(Gui, FrameworkElement)
NS_IFORWARD(Gui, IValueConverter)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides high-level access to the definition of a binding, which connects the properties
/// of binding target objects and any data source.
///
/// Example:
///
/// .. code-block:: xml
///
///     <TextBlock Text="{Binding Source={StaticResource myDataSource}, Path=PersonName}"/>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.data.binding.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Binding: public BaseBinding
{
public:
    /// Default constructor
    Binding();

    /// Constructor with an initial property path
    Binding(const NsChar* path);
    Binding(const DependencyProperty* path);

    /// Constructor with an initial property path and a source
    Binding(const NsChar* path, Core::BaseComponent* source);
    Binding(const DependencyProperty* path, Core::BaseComponent* source);

    /// Constructor with an initial property path and an element name
    Binding(const NsChar* path, const NsChar* elementName);
    Binding(const DependencyProperty* path, const NsChar* elementName);

    /// Constructor with an initial property path and a relative source
    Binding(const NsChar* path, RelativeSource* relativeSource);
    Binding(const DependencyProperty* path, RelativeSource* relativeSource);

    /// Destructor
    ~Binding();

    /// Gets or sets the name of the element to use as the binding source object.
    /// Only one of the three properties, *ElementName*, *Source*, or *RelativeSource*, should be 
    /// set for each binding, or a conflict can occur. Setting this property throws an exception 
    /// if there is a binding source conflict
    //@{
    const NsChar* GetElementName() const;
    void SetElementName(const NsChar* elementName);
    //@}
    
    /// Gets or sets the object to use as the binding source.
    /// Only one of the three properties, *ElementName*, *Source*, or *RelativeSource*, should be 
    /// set for each binding, or a conflict can occur. Setting this property throws an exception 
    /// if there is a binding source conflict
    //@{
    Core::BaseComponent* GetSource() const;
    void SetSource(Core::BaseComponent* source);
    //@}

    /// Gets or sets the binding source by specifying its location relative to the position of
    /// the binding target.
    /// Only one of the three properties, *ElementName*, *Source*, or *RelativeSource*, should be 
    /// set for each binding, or a conflict can occur. Setting this property throws an exception 
    /// if there is a binding source conflict
    //@{
    RelativeSource* GetRelativeSource() const;
    void SetRelativeSource(RelativeSource* source);
    //@}
    
    /// Gets or sets the path to the binding source property
    //@{
    PropertyPath* GetPath() const;
    void SetPath(PropertyPath* path);
    //@}
    
    /// Gets or sets the binding mode. It can be set to one of the following values of the
    /// *BindingMode* enumeration:
    ///
    /// * *OneWay*: The target is updated whenever the source changes.
    ///
    /// * *TwoWay*: A change to either the target or source updates the other.
    ///
    /// * *OneWayToSource*: The opposite of *OneWay*. The source is updated whenever the target 
    /// changes.
    ///
    /// * *OneTime*: This works just like *OneWay*, except changes to the source are not 
    /// reflected at the target. The target retains a snapshot of the source at the time the 
    /// *Binding* is initiated.
    //@{
    BindingMode GetMode() const;
    void SetMode(BindingMode mode);
    //@}
    
    /// Gets or sets the converter to use. If you set the Converter and StringFormat properties,
    /// the converter is applied to the data value first, and then the StringFormat is applied
    //@{
    IValueConverter* GetConverter() const;
    void SetConverter(IValueConverter* converter);
    //@}
    
    /// Gets or sets the parameter to pass to the Converter
    //@{
    Core::BaseComponent* GetConverterParameter() const;
    void SetConverterParameter(Core::BaseComponent* parameter);
    //@}
    
    /// Gets or sets a value that determines the timing of binding source updates:
    ///
    /// * *Default*: The default UpdateSourceTrigger value of the binding target property. The 
    /// default value for most dependency properties is *PropertyChanged*, while the *Text* 
    /// property has a default value of *LostFocus*.
    ///
    /// * *PropertyChanged*: The source is updated whenever the target property value changes.
    /// 
    /// * *LostFocus*: When the target property value changes, the source is only updated after 
    /// the target element loses focus.
    /// 
    /// * *Explicit*: The source is only updated when you make an explicit call to 
    /// *BindingExpression.UpdateSource*.
    //@{
    UpdateSourceTrigger GetUpdateSourceTrigger() const;
    void SetUpdateSourceTrigger(UpdateSourceTrigger value);
    //@}
    
    /// Find data from the appropriate source: Source, ElementName, RelativeSource or DataContext
    ObjectWithNameScope GetSourceObject(Core::BaseComponent* target,
        const DependencyProperty* targetProperty) const;

    /// From IMarkupExtension
    //@{
    /// \remarks Can return 0 when the source object is not resolvable (doesn't throw exception)
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

    // Used internally when binding is solved to log warning messages
    static void LogWarning(const NsChar* format, ...);

    // Item[] property is used to notify of changes on collections
    static NsSymbol ItemNotifyName();

    // Placeholder item to keep bindings working when item containers are recycled
    static Core::BaseComponent* DisconnectedItem();

    /// A source property or a converter can return Binding.DoNothing to instruct the binding engine
    /// to do nothing when binding gets evaluated
    static Core::BaseComponent* GetDoNothing();

protected:
    /// From BaseBinding
    //@{
    void OnInit();
    //@}

private:
    void RegisterSource();
    void UnregisterSource();

    void OnSourceDestroyed(DependencyObject* object);

    void SetSourceImpl(Core::BaseComponent* source);

private:
    /// Name of the element to use as the binding source object
    NsString mElementName;

    /// Object to use as the binding source
    Core::BaseComponent* mSource;

    /// Gets or sets the binding source by specifying its location relative to the position of the
    /// binding target
    Ptr<RelativeSource> mRelativeSource;

    /// Path to the binding source property
    Ptr<PropertyPath> mPath;

    /// Gets or sets a value that indicates the direction of the data flow in the binding
    BindingMode mMode;

    /// Value converter
    Ptr<IValueConverter> mConverter;

    /// Parameter to pass to mConverter
    Ptr<Core::BaseComponent> mConverterParameter;
    
    /// Value to indicate the timing of the binding update
    UpdateSourceTrigger mUpdateSourceTrigger;

    NS_DECLARE_REFLECTION(Binding, BaseBinding)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}


#endif
