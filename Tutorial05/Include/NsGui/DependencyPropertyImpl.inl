////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/CompilerTools.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/DependencyData.h>
#include <NsGui/BoxingUtils.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
DependencyPropertyImpl<T>::DependencyPropertyImpl(NsSymbol name): 
    DependencyProperty(name, Core::TypeOf<T>(), sizeof(T))
{
    // NOTE: This constructor doesn't create metadata because it doesn't have the ownerType and
    // because this constructor is intended to be used from DependencyData to partially create
    // the class and later be fulfilled (example: when using AddOwner or OverrideMetadata
    // before RegisterProperty)
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
DependencyPropertyImpl<T>::DependencyPropertyImpl(NsSymbol name, const Core::Type* type,
    NsSize size): DependencyProperty(name, type, size)
{
    // NOTE: This constructor doesn't create metadata because it doesn't have the ownerType and
    // because this constructor is intended to be used from DependencyData to partially create
    // the class and later be fulfilled (example: when using AddOwner or OverrideMetadata
    // before RegisterProperty)
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
DependencyPropertyImpl<T>::DependencyPropertyImpl(NsSymbol name, const Core::Type* type,
    NsSize size, const Core::TypeClass* ownerType, const Ptr<PropertyMetadata>& metaData,
    const ValidateValueDelegate& delegate, PropertyAccess access): DependencyProperty(name, type,
    size, ownerType, metaData, delegate, access)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
DependencyPropertyImpl<T>::DependencyPropertyImpl(NsSymbol name, const Core::TypeClass* ownerType,
    PropertyAccess access): DependencyProperty(name, Core::TypeOf<T>(), sizeof(T), ownerType,
    access)
{
    AddMetaData(PropertyMetadata::Create<T>(T()).GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
DependencyPropertyImpl<T>::DependencyPropertyImpl(NsSymbol name, const Core::TypeClass* ownerType, 
    const Ptr<PropertyMetadata>& metaData, PropertyAccess access): DependencyProperty(name,
    Core::TypeOf<T>(), sizeof(T), ownerType, metaData, access)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
DependencyPropertyImpl<T>::DependencyPropertyImpl(NsSymbol name, const Core::TypeClass* ownerType,
    const Ptr<PropertyMetadata>& metaData, const ValidateValueDelegate& delegate,
    PropertyAccess access): DependencyProperty(name, Core::TypeOf<T>(), sizeof(T), ownerType,
    metaData, delegate, access)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
DependencyPropertyImpl<T>::~DependencyPropertyImpl()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const void* DependencyPropertyImpl<T>::GetDefaultValue(const Core::TypeClass* type) const
{
    return BoxingUtils::GetRawValue<T>(GetDefaultValueObject(type));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::OverrideMetadata(const Core::TypeClass* forType,
    const Ptr<PropertyMetadata>& metadata) const
{
    Ptr<DependencyData> data(forType->GetMetaData().Find<DependencyData>());
    if (!data)
    {
        data = *new DependencyData(forType);
        const_cast<Core::TypeClass*>(forType)->GetMetaData().Add(data.GetPtr());
    }

    const DependencyProperty* dp = this;
    data->OverrideMetadata<T>(dp, GetName().GetStr(), metadata);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool DependencyPropertyImpl<T>::IsSameValue(const DependencyObject* obj,
    const Ptr<Core::BaseComponent>& value) const
{
    return BoxingUtils::IsSameValue<T>(&obj->GetValue<T>(this), BoxingUtils::GetRawValue<T>(value));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool DependencyPropertyImpl<T>::IsSameValue(const Ptr<Core::BaseComponent>& left,
    const Ptr<Core::BaseComponent>& right) const
{
    return BoxingUtils::IsSameValue<T>(
        BoxingUtils::GetRawValue<T>(left),
        BoxingUtils::GetRawValue<T>(right));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool DependencyPropertyImpl<T>::IsSameValue(const void* left, const void* right) const
{
    return BoxingUtils::IsSameValue<T>(left, right);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::ConstructValue(void* ptr, const void* value) const
{
    if (value)
    {
        new(ptr) T(*static_cast<const T*>(value));
    }
    else
    {
        new(ptr) T();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::DestroyValue(void* value) const
{
    NS_UNUSED(value);
    static_cast<T*>(value)->~T();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::CopyValue(void* ptr, const void* value) const
{
    *static_cast<T*>(ptr) = *static_cast<const T*>(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool DependencyPropertyImpl<T>::CheckType(const Core::Type* valueType) const
{
    return valueType == Core::TypeOf<T>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool DependencyPropertyImpl<T>::CheckType(const Ptr<Core::BaseComponent>& value) const
{
    return BoxingUtils::CheckType<T>(value, GetType());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const void* DependencyPropertyImpl<T>::GetValue(const Ptr<Core::BaseComponent>& value) const
{
    return BoxingUtils::GetRawValue<T>(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const void* DependencyPropertyImpl<T>::GetValue(const DependencyObject* obj) const
{
    return &obj->GetValue<T>(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::SetValue(DependencyObject* obj, const void* value) const
{
    obj->InternalSetValue<T>(this, *static_cast<const T*>(value), 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::SetValue(DependencyObject* obj, const void* value, NsUInt8 priority,
    IExpression* expression) const
{
    obj->InternalSetValue<T>(this, *static_cast<const T*>(value), priority, expression);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<Core::BaseComponent> DependencyPropertyImpl<T>::GetValueObject(const void* value) const
{
    return BoxingUtils::GetBoxedValue<T>(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<Core::BaseComponent> DependencyPropertyImpl<T>::GetValueObject(
    const DependencyObject* obj) const
{
    return BoxingUtils::GetBoxedValue<T>(obj, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::SetValueObject(DependencyObject* obj,
    const Ptr<Core::BaseComponent>& value) const
{
    BoxingUtils::SetBoxedValue<T>(obj, this, value, 0, 0, Value::Destination_BaseValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<Core::BaseComponent> DependencyPropertyImpl<T>::GetBaseValueObject(
    const DependencyObject* obj) const
{
    return BoxingUtils::GetBoxedBaseValue<T>(obj, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::SetAnimationObject(DependencyObject* obj,
    const Ptr<Core::BaseComponent>& value) const
{
    BoxingUtils::SetBoxedAnimation<T>(obj, this, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::ClearAnimation(DependencyObject* obj) const
{
    obj->ClearAnimation<T>(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::CoerceValue(DependencyObject* obj) const
{
    obj->CoerceValue<T>(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::CoerceValue(DependencyObject* obj, StoredValue* storedValue,
    const void* defaultValue) const
{
    obj->InternalCoerceValue<T>(this, storedValue, defaultValue, sizeof(T));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::SetValueObject(DependencyObject* obj,
    const Ptr<Core::BaseComponent>& value, NsUInt8 priority, IExpression* expression) const
{
    BoxingUtils::SetBoxedValue<T>(obj, this, value, priority, expression, 
        Value::Destination_BaseValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyPropertyImpl<T>::SetCurrentValueObject(DependencyObject* obj,
    const Ptr<Core::BaseComponent>& value) const
{
    BoxingUtils::SetBoxedValue<T>(obj, this, value, 0, 0, Value::Destination_CurrentValue);
}

}
}
