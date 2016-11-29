////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEBINDINGEXPRESSION_H__
#define __GUI_BASEBINDINGEXPRESSION_H__


#include <Noesis.h>
#include <NsGui/Expression.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class BaseBinding;
class DependencyObject;
class DependencyProperty;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for all Binding Expressions.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseBindingExpression: public Expression
{
public:
    BaseBindingExpression();
    BaseBindingExpression(BaseBinding* binding, DependencyObject* targetObject,
        const DependencyProperty* targetProperty);

    // Base classes are abstract classes. Destructor is pure virtual
    virtual ~BaseBindingExpression() = 0;

    /// Gets the element to which this BindingExpression is attached
    /// \prop
    DependencyObject* GetTarget() const;

    /// Gets the property to which this BindingExpression is attached
    /// \prop
    const DependencyProperty* GetTargetProperty() const;

    /// Gets the BaseBinding object from which this BaseBindingExpression object is created
    /// \prop
    BaseBinding* GetParentBindingBase() const;

    /// Forces a data transfer from source to target
    virtual void UpdateTarget() const = 0;

    /// Sends the current value back to the source. Does nothing when binding's Mode is not TwoWay
    /// or OneWayToSource
    virtual void UpdateSource() const = 0;

private:
    /// Base classes are non-copyable objects
    //@{
    BaseBindingExpression(const BaseBindingExpression&);
    BaseBindingExpression& operator=(const BaseBindingExpression&);
    //@}

protected:
    /// Base binding which originated the expression
    Ptr<BaseBinding> mBinding;

    /// Dependency object where the expression is applied
    DependencyObject* mTargetObject;

    /// Dependency property where the expression is applied
    const DependencyProperty* mTargetProperty;

    NS_DECLARE_REFLECTION(BaseBindingExpression, Expression)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
