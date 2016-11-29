////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #938]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TEMPLATEBINDINGEXPRESSION_H__
#define __GUI_TEMPLATEBINDINGEXPRESSION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Expression.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>


NS_IFORWARD(Core, ITypeConverter)
NS_CFORWARD(Gui, DependencyObject)
NS_CFORWARD(Gui, FrameworkElement)
NS_CFORWARD(Gui, TemplateBindingExtension)
NS_SFORWARD(Gui, DependencyPropertyChangedEventArgs)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TemplateBindingExpression. Expression created from TemplateBindingExtension::ProvideValue
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TemplateBindingExpression: public Expression
{
public:
    ~TemplateBindingExpression();

    /// Gets the TemplateBindingExtension object of this expression instance
    /// \prop
    TemplateBindingExtension* GetTemplateBindingExtension() const;

    /// From IExpression
    //@{
    Ptr<Core::BaseComponent> Evaluate() const;
    Ptr<IExpression> Reapply(DependencyObject* targetObject,
        const DependencyProperty* targetProperty) const;
    //@}

private:
    friend class TemplateBindingExtension;
    TemplateBindingExpression(TemplateBindingExtension* extension, DependencyObject* targetObject,
        const DependencyProperty* targetProperty);

    void Register();
    void Unregister();

    void OnTemplatedParentPropertyChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);

    void TemplatedParentDestroyed(DependencyObject* object);

    void TargetDestroyed(DependencyObject* object);

private:
    Ptr<TemplateBindingExtension> mBinding;
    DependencyObject* mTargetObject;
    const DependencyProperty* mTargetProperty;
    FrameworkElement* mTemplatedParent;
    Ptr<Core::ITypeConverter> mConverter;

    NS_DECLARE_REFLECTION(TemplateBindingExpression, Expression)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
