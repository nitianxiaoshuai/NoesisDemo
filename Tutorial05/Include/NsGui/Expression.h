////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_EXPRESSION_H__
#define __GUI_EXPRESSION_H__


#include <Noesis.h>
#include <NsGui/DependencySystemApi.h>
#include <NsGui/IExpression.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base implementation for all expressions.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_DEPENDENCYSYSTEM_API Expression: public Core::BaseComponent, public IExpression
{
public:
    /// Constructor
    Expression();

    /// Destructor
    virtual ~Expression() = 0;

    /// From IExpression
    //@{
    EvaluateBehavior GetEvaluateBehavior() const;
    Ptr<Core::BaseComponent> Evaluate() const;
    Ptr<IExpression> Reapply(DependencyObject* targetObject,
        const DependencyProperty* targetProperty) const;
    BeforeSetAction BeforeSet(DependencyObject* obj, const DependencyProperty* prop,
        const void* value, NsBool valueHasChanged);
    void AfterSet(DependencyObject* obj, const DependencyProperty* prop, const void* value,
        NsBool valueHasChanged);
    //@}

    NS_DECLARE_REFLECTION(Expression, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif