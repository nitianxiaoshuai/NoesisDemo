////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #938]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TEMPLATEBINDINGEXTENSION_H__
#define __GUI_TEMPLATEBINDINGEXTENSION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IMarkupExtension.h>


NS_CFORWARD(Gui, DependencyProperty)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements a markup extension that supports the binding between the value of a property in a
/// template and the value of some other exposed property on the templated control. Using a
/// TemplateBinding is equivalent to using a Binding with the Source property set to
/// RelativeSource.TemplatedParent.
///
/// The method ProvideValue returns a TemplateBindingExpression.
///
/// Example:
///
/// .. code-block:: xml
///
///     <ControlTemplate Key="buttonTemplate" TargetType="{x:Type Button}">
///       <Border Background="{TemplateBinding Background}"/>
///     </ControlTemplate>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.templatebindingextension.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TemplateBindingExtension: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// Default constructor
    TemplateBindingExtension();
    
    /// Constructor
    TemplateBindingExtension(const DependencyProperty* dp);

    /// Gets or sets property
    //@{
    const DependencyProperty* GetProperty() const;
    void SetProperty(const DependencyProperty* property);
    //@}

    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    /// Gets or sets the source property being bound to
    const DependencyProperty* mProperty;
    
    NS_DECLARE_REFLECTION(TemplateBindingExtension, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
