////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/DynamicCast.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Boxing.h>
#include <NsCore/Ptr.h>
#include <NsGui/DependencyObject.h>


namespace Noesis
{
namespace Gui
{

namespace BoxingUtils
{
////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
NsBool IsSameValue(const T& left, const T& right, Core::Int2Type<0>)
{
    return left == right;
}

inline NsBool IsSameValue(const Ptr<Core::BaseComponent>& left,
    const Ptr<Core::BaseComponent>& right, Core::Int2Type<1>)
{
    if (left != 0)
    {
        return left->Equals(right.GetPtr());
    }

    return left == right;
}

template<class T>
NsBool IsSameValue(const void* left_, const void* right_)
{
    NS_ASSERT(left_ != 0);
    NS_ASSERT(right_ != 0);

    const T* left = static_cast<const T*>(left_);
    const T* right = static_cast<const T*>(right_);

    return IsSameValue(*left, *right, Core::Int2Type<Core::IsSame<T, Ptr<Core::BaseComponent> >::
        Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool CheckType(const Ptr<Core::BaseComponent>& value, const Core::Type*, Core::Int2Type<0>)
{
    return NsDynamicCast<Core::Boxed<T>*>(value.GetPtr()) != 0;
}

template<class T>
NsBool CheckType(const Ptr<Core::BaseComponent>& value, const Core::Type* type, Core::Int2Type<1>)
{
    if (!value)
    {
        return true;
    }

    const Core::TypeClass* valueType = value->GetClassType();
    const Core::TypeClass* propType = NsStaticCast<const Core::TypeClass*>(type);
    return valueType == propType || valueType->IsDescendantOf(propType);
}

template<class T>
NsBool CheckType(const Ptr<Core::BaseComponent>& value, const Core::Type* type)
{
    return CheckType<T>(value, type, Core::Int2Type<Core::IsPtr<T>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const void* GetRawValue(const Ptr<Core::BaseComponent>& value, Core::Int2Type<0>)
{
    NS_ASSERT(NsDynamicCast<Core::Boxed<T>*>(value.GetPtr()) != 0);
    return &Core::Boxing::Unbox<T>(NsStaticCast<Core::BoxedValue*>(value.GetPtr()));
}

template<class T>
const void* GetRawValue(const Ptr<Core::BaseComponent>& value, Core::Int2Type<1>)
{
    return &value;
}

template<class T>
const void* GetRawValue(const Ptr<Core::BaseComponent>& value)
{
    return GetRawValue<T>(value, Core::Int2Type<Core::IsPtr<T>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<Core::BaseComponent> GetBoxedValue(const void* value, Core::Int2Type<0>)
{
    return Core::Boxing::Box<T>(*static_cast<const T*>(value));
}

template<class T>
Ptr<Core::BaseComponent> GetBoxedValue(const void* value, Core::Int2Type<1>)
{
    return NsDynamicCast< Ptr<Core::BaseComponent> >(*static_cast<const T*>(value));
}

template<class T>
Ptr<Core::BaseComponent> GetBoxedValue(const void* value)
{
    return GetBoxedValue<T>(value, Core::Int2Type<Core::IsPtr<T>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<Core::BaseComponent> GetBoxedValue(const DependencyObject* obj, const DependencyProperty* dp,
    Core::Int2Type<0>)
{
    return Core::Boxing::Box<T>(obj->GetValue<T>(dp));
}

template<class T>
Ptr<Core::BaseComponent> GetBoxedValue(const DependencyObject* obj, const DependencyProperty* dp,
    Core::Int2Type<1>)
{
    return NsDynamicCast< Ptr<Core::BaseComponent> >(obj->GetValue<T>(dp));
}

template<class T>
Ptr<Core::BaseComponent> GetBoxedValue(const DependencyObject* obj, const DependencyProperty* dp)
{
    return GetBoxedValue<T>(obj, dp, Core::Int2Type<Core::IsPtr<T>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void SetBoxedValue(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value, NsUInt8 priority, IExpression* expression, 
    Value::Destination destination, Core::Int2Type<0>)
{
    obj->InternalSetValue<T>(dp, Core::Boxing::Unbox<T>(NsStaticCast<Core::BoxedValue*>(
        value.GetPtr())), priority, expression, destination);
}

template<class T>
void SetBoxedValue(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value, NsUInt8 priority, IExpression* expression, 
    Value::Destination destination, Core::Int2Type<1>)
{
    obj->InternalSetValue<T>(dp, NsDynamicCast< Ptr<typename T::Type> >(value), priority, expression,
        destination);
}

template<class T>
void SetBoxedValue(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value, NsUInt8 priority, IExpression* expression,
    Value::Destination destination)
{
    SetBoxedValue<T>(obj, dp, value, priority, expression, destination,
        Core::Int2Type<Core::IsPtr<T>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<Core::BaseComponent> GetBoxedBaseValue(const DependencyObject* obj, 
    const DependencyProperty* dp, Core::Int2Type<0>)
{
    return Core::Boxing::Box<T>(obj->GetBaseValue<T>(dp));
}

template<class T>
Ptr<Core::BaseComponent> GetBoxedBaseValue(const DependencyObject* obj, 
    const DependencyProperty* dp, Core::Int2Type<1>)
{
    return NsDynamicCast< Ptr<Core::BaseComponent> >(obj->GetBaseValue<T>(dp));
}

template<class T>
Ptr<Core::BaseComponent> GetBoxedBaseValue(const DependencyObject* obj, 
    const DependencyProperty* dp)
{
    return GetBoxedBaseValue<T>(obj, dp, Core::Int2Type<Core::IsPtr<T>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void SetBoxedAnimation(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value, Core::Int2Type<0>)
{
    obj->SetAnimation<T>(dp, Core::Boxing::Unbox<T>(value.GetPtr()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void SetBoxedAnimation(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value, Core::Int2Type<1>)
{
    obj->SetAnimation<T>(dp, Core::Boxing::Unbox<NsString>(value.GetPtr()).c_str());
}

template<class T>
void SetBoxedAnimation(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value, Core::Int2Type<2>)
{
    obj->SetAnimation<T>(dp, NsStaticCast<typename T::Type*>(value.GetPtr()));
}

template<class T>
void SetBoxedAnimation(DependencyObject* obj, const DependencyProperty* dp,
    const Ptr<Core::BaseComponent>& value)
{
    SetBoxedAnimation<T>(obj, dp, value,
        typename Core::If<Core::IsPtr<T>::Result,
            Core::Int2Type<2>,
            typename Core::If<Core::IsSame<T, NsString>::Result,
                Core::Int2Type<1>,
                Core::Int2Type<0> >::Result>::Result());
}

}

}
}
