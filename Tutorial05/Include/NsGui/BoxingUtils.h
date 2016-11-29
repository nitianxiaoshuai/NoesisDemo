////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BOXINGUTILS_H__
#define __GUI_BOXINGUTILS_H__


#include <NsGui/ValueDestination.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Core
{
template<class T> class Ptr;
class BaseComponent;
class Type;
}
using Core::Ptr;
namespace Gui
{
class DependencyObject;
class DependencyProperty;
NS_INTERFACE IExpression;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Utility functions to manage boxed values that come from Ptr objects and basic types
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace BoxingUtils
{

/// Compares two boxed values
template<class T>
NsBool IsSameValue(const void* left, const void* right);

/// Checks that a boxed value has the specified T type
template<class T>
NsBool CheckType(const Ptr<Core::BaseComponent>& value, const Core::Type* type);

/// Gets a raw pointer to the value
template<class T>
const void* GetRawValue(const Ptr<Core::BaseComponent>& value);

/// Gets a boxed value from a raw pointer
template<class T>
Ptr<Core::BaseComponent> GetBoxedValue(const void* value);

/// Gets a boxed value from the specified dependency object property
template<class T>
Ptr<Core::BaseComponent> GetBoxedValue(const DependencyObject* obj, const DependencyProperty* dp);

/// Sets a boxed value to the specified dependency object property
template<class T>
void SetBoxedValue(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value, NsUInt8 priority, IExpression* expression, 
    Value::Destination destination);
    
/// Gets a boxed base value from the specified dependency object property
template<class T>
Ptr<Core::BaseComponent> GetBoxedBaseValue(const DependencyObject* obj, 
    const DependencyProperty* dp);
}

/// Sets a boxed animation value to the specified dependency object property
template<class T>
void SetBoxedAnimation(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value, NsUInt8 priority, IExpression* expression);

}
}

// Inline Include
#include <NsGui/BoxingUtils.inl>


#endif
