////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IEXPRESSION_H__
#define __GUI_IEXPRESSION_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsGui/IExpressionTypes.h>


namespace Noesis
{

// Forward declarations
//@{

namespace Core
{
template<class T> class Ptr;
class BaseComponent;
}
namespace Gui
{
class DependencyObject;
class DependencyProperty;
}
using Core::Ptr;
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IExpression
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IExpression: public Core::Interface
{
    /// Indicates expression evaluate behavior
    virtual EvaluateBehavior GetEvaluateBehavior() const = 0;

    /// Evaluates expression when applied to the specified target object
    virtual Ptr<Core::BaseComponent> Evaluate() const = 0;
    
    /// Applies expression to a new target, cloning the expression itself if necessary
    virtual Ptr<IExpression> Reapply(DependencyObject* targetObject,
        const DependencyProperty* targetProperty) const = 0;

    /// Executes the set
    virtual BeforeSetAction BeforeSet(DependencyObject* obj, const DependencyProperty* dp, 
        const void* value, NsBool valueHasChanged) = 0;
        
    /// Executed after set is completed and the property changed has been notified
    virtual void AfterSet(DependencyObject* obj, const DependencyProperty* dp, 
        const void* value, NsBool valueHasChanged) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IExpression, Core::Interface)
};

}
}

#endif
