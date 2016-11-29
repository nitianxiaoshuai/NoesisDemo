////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #751]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Boxing.h>
#include <NsCore/Ptr.h>
#include <NsCore/MemProfiler.h>
#include <NsGui/DependencyProperty.h>
#include <NsGui/IExpression.h>
#include <NsGui/Freezable.h>
#include <NsGui/ProviderValue.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const T& DependencyObject::GetValue(const DependencyProperty* dp) const
{
    return *static_cast<const T*>(InternalGetValue(dp, sizeof(T)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const T& DependencyObject::GetBaseValue(const DependencyProperty* dp) const
{
    return *static_cast<const T*>(InternalGetBaseValue(dp, sizeof(T)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetValue(const DependencyProperty* dp, typename SetValueType<T>::Type value)
{
    NS_ASSERT(dp != 0);
    CheckReadOnly(dp);

    SetValue_<T>(Core::Int2Type<Core::IsPtr<T>::Result>(), dp, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetCurrentValue(const DependencyProperty* dp,
    typename SetValueType<T>::Type value)
{
    NS_ASSERT(dp != 0);
    CheckReadOnly(dp);

    SetValue_<T>(Core::Int2Type<Core::IsPtr<T>::Result>(), dp, value,
        Value::Destination_CurrentValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetAnimation(const DependencyProperty* dp,
    typename SetValueType<T>::Type value)
{
    NS_ASSERT(dp != 0);
    CheckReadOnly(dp);

    SetValue_<T>(Core::Int2Type<Core::IsPtr<T>::Result>(), dp, value,
        Value::Destination_Animation);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::ClearAnimation(const DependencyProperty* dp)
{
    NS_ASSERT(dp != 0);
    NS_ASSERT(dp->GetSize() == sizeof(T));

    Values::iterator it = mValues.find(dp);
    if (it == mValues.end())
    {
        return;
    }
    
    StoredValue* sv = &it->second;
    if (!sv->flags.isAnimated)
    {
        return;
    }
    
    // Retrieve oldValue
    T oldValue = GetValue<T>(dp);
    
    // Remove animation
    Helper<T>::DestructValue(&sv->value.complex->animated);
    it->second.flags.isAnimated = false;
    
    // Get coercedValue if applicable
    T coercedValue;
    if (sv->flags.isCoercedCurrentValue)
    {
        coercedValue = *static_cast<const T*>(sv->GetCoercedValue(sizeof(T)));
    }
    else
    {
        T baseValue = *static_cast<const T*>(sv->GetBaseValue(sizeof(T)));
        
        if (!CoerceValue(&baseValue, &coercedValue, dp))
        {
            coercedValue = baseValue;
        }
        
        NsBool hasCoerce = (coercedValue != baseValue);
        
        if (hasCoerce)
        {
            if (sv->flags.isCoerced)
            {
                Helper<T>::CopyValue(&sv->value.complex->coerced, coercedValue);
            }
            else
            {
                Helper<T>::ConstructValue(&sv->value.complex->coerced, coercedValue);
                sv->flags.isCoerced = true;
            }
        }
        else if (sv->flags.isCoerced)
        {
            Helper<T>::DestructValue(&sv->value.complex->coerced);
            sv->flags.isCoerced = false;
        }
    }

    NotifyPropertyChanged<T>(dp, sv, oldValue, coercedValue, oldValue != coercedValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::CoerceValue(const DependencyProperty* dp)
{
    NS_ASSERT(dp);

    // TODO [srodriguez] Revisar con el ticket 1317

    Values::iterator it = mValues.find(dp);
    StoredValue* storedValue = it != mValues.end() ? &it->second : 0;

    InternalCoerceValue<T>(dp, storedValue, dp->GetDefaultValue(GetClassType()), dp->GetSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DependencyObject::DependencyPropertyChangedEventHandler&
    DependencyObject::DependencyPropertyChanged()
{
    return mDependencyPropertyChangedEvent;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DependencyObject::DestroyedDelegate& DependencyObject::Destroyed()
{
    return mDestroyedDelegate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::InternalSetValue(const DependencyProperty* dp, const T& newValue, 
    NsUInt8 priority, IExpression* newExpression, Value::Destination destination)
{
    NS_PROFILE_MEM("Gui/DependencyObject");

    NS_ASSERT(dp);
    NS_ASSERT(dp->GetSize() == sizeof(T));
    
    NS_ASSERT((destination == Value::Destination_CurrentValue && priority == 0 && !newExpression) ||
        (destination == Value::Destination_Animation && priority == 0 && !newExpression) ||
        (destination == Value::Destination_BaseValue));

    // Store oldValue
    T oldValue = GetValue<T>(dp);

    // Get coercedValue if applicable
    T coercedValue;
    
    if (!CoerceValue(&newValue, &coercedValue, dp))
    {
        if (priority >= ProviderValue::InheritedValueProviderPriority)
        {
            Values::iterator it = mValues.find(dp);
            if (it == mValues.end())
            {
                // Default value or inherited not coerced and there is no storage created... we 
                // have nothing more to do!
                return;
            }
        }
        
        // Assign coercedValue
        coercedValue = newValue;
    }

    // Validate
    NsBool justInserted;
    StoredValue* sv = &ValidateAndGetEntry(&coercedValue, dp, justInserted);
    if (!justInserted)
    {
        NS_ASSERT(priority <= sv->provider);
    }
    
    // Set the provider. When a value is set, the provider is directly overwritten
    if (destination == Value::Destination_BaseValue)
    {
        sv->provider = priority;
    }
    else 
    {
        // For animations and currentValue, the provider is not changed if there was a previous 
        // value, or it's set to defaultProvider if it is just created
        if (justInserted)
        {
            sv->provider = ProviderValue::DefaultValueProviderPriority;
        }
    }

    // If value is animated, store local value and forget
    if (sv->flags.isAnimated && destination == Value::Destination_BaseValue)
    {
        StoreExpression(newExpression, *sv);
        Helper<T>::CopyValue(&sv->value.complex->base, newValue);
        return;
    }

    NsBool valueChanged = oldValue != coercedValue;
    NsBool notifyExpressionAtEnd = false;
    if (priority == ProviderValue::LocalProviderPriority &&
        destination != Value::Destination_Animation &&
        newExpression == 0 && sv->flags.isExpression)
    {
        notifyExpressionAtEnd = EvaluateLocalExpression(newExpression, *sv, dp, &coercedValue,
            valueChanged);
    }

    NsBool hasCoerce = (coercedValue != newValue || destination == Value::Destination_CurrentValue);
    NsBool hasAnimation = (destination == Value::Destination_Animation);
    NsBool newComplex = (newExpression || hasCoerce || hasAnimation) && 
        (justInserted || !sv->flags.isComplex);

    if (newComplex)
    {
        if (!justInserted)
        {
            // TODO [srodriguez] For types > sizeof(void*) the pointer memory could be reused
            Helper<T>::DestructValue(&sv->value.simple);
        }
        
        // Create complex value
        sv->CreateComplex();

        switch (destination)
        {
            case Value::Destination_BaseValue:
            {
                // And store base and coerced value
                Helper<T>::ConstructValue(&sv->value.complex->base, newValue);
                break;
            }
            case Value::Destination_CurrentValue:
            {
                Helper<T>::ConstructValue(&sv->value.complex->base, oldValue);
                break;
            }
            case Value::Destination_Animation:
            {
                Helper<T>::ConstructValue(&sv->value.complex->base, oldValue);
                break;
            }
        }
    }
    else if (sv->flags.isComplex)
    {
        NS_ASSERT(!justInserted);
        switch (destination)
        {
            case Value::Destination_BaseValue:
            {
                Helper<T>::CopyValue(&sv->value.complex->base, newValue);
                break;
            }
            case Value::Destination_CurrentValue:
            {
                break;
            }
            case Value::Destination_Animation:
            {
                break;
            }
        }
    }
    else if (!justInserted)
    {
        NS_ASSERT(!hasCoerce);
        Helper<T>::CopyValue(&sv->value.simple, newValue);
    }
    else
    {
        NS_ASSERT(justInserted);
        Helper<T>::ConstructValue(&sv->value.simple, newValue);
    }
    
    if (hasAnimation)
    {
        if (sv->flags.isAnimated)
        {
            Helper<T>::CopyValue(&sv->value.complex->animated, newValue);
        }
        else
        {
            Helper<T>::ConstructValue(&sv->value.complex->animated, newValue);
            sv->flags.isAnimated = true;
        }
    }
    else if (sv->flags.isAnimated)
    {
        // Animation can only be cleared using ClearAnimation
    }
    
    if (hasCoerce)
    {
        if (sv->flags.isCoerced)
        {
            Helper<T>::CopyValue(&sv->value.complex->coerced, coercedValue);
        }
        else
        {
            Helper<T>::ConstructValue(&sv->value.complex->coerced, coercedValue);
            sv->flags.isCoerced = true;
        }
        
        sv->flags.isCoercedCurrentValue = (destination == Value::Destination_CurrentValue);
    }
    else if (sv->flags.isCoerced)
    {
        Helper<T>::DestructValue(&sv->value.complex->coerced);
        sv->flags.isCoerced = false;
        sv->flags.isCoercedCurrentValue = false;
    }

    if (destination == Value::Destination_BaseValue)
    {
        StoreExpression(newExpression, *sv);
    }

    NotifyPropertyChanged<T>(dp, sv, oldValue, coercedValue, valueChanged);

    if (notifyExpressionAtEnd)
    {
        NotifyLocalExpression(newExpression, dp, &coercedValue, valueChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetReadOnlyProperty(const DependencyProperty* dp,
    typename SetValueType<T>::Type value) const
{
    NS_ASSERT(dp != 0);
    const_cast<DependencyObject*>(this)->SetValue_<T>(Core::Int2Type<Core::IsPtr<T>::Result>(), dp,
        value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::Helper<T>::CopyValue(ValueStorage* storage, 
    typename Core::Param<T>::Type value)
{
    switch ((int)(sizeof(T) <= sizeof(ValueStorage)))
    {
        case true:
        {
            *static_cast<T*>(static_cast<void*>(storage)) = value;
            break;
        }
        case false:
        {
            *static_cast<T*>(*storage) = value;
            break;
        }
        default:
            NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::Helper<T>::ConstructValue(ValueStorage* storage, 
    typename Core::Param<T>::Type value)
{
    switch ((int)(sizeof(T) <= sizeof(ValueStorage)))
    {
        case true:
        {
            new(storage) T(value);
            break;
        }
        case false:
        {
            NS_PROFILE_MEM("Gui/DependencyObject");
            void* storage_ = NsAlloc(sizeof(T));
            *storage = new(storage_) T(value);
            break;
        }
        default:
            NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::Helper<T>::DestructValue(ValueStorage* storage)
{
    switch ((int)(sizeof(T) <= sizeof(ValueStorage)))
    {
        case true:
        {
            static_cast<T*>(static_cast<void*>(storage))->~T();
            break;
        }
        case false:
        {
            static_cast<T*>(static_cast<void*>(*storage))->~T();
            NsDealloc(*storage);
            break;
        }
        default:
            NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetValue_(IsNotBaseComponent, const DependencyProperty* dp,
    typename Core::Param<T>::Type value, Value::Destination destination)
{
    // Only values of the same type than the property type can be set
    CheckTypes(Core::TypeOf<T>(), dp);

    InternalSetValue(dp, value, 0, 0, destination);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetValue_(IsBaseComponent, const DependencyProperty* dp,
    typename T::Type* value, Value::Destination destination)
{
    Ptr<BaseComponent> valuePtr(value);

    // Only values of the same type than the property type can be set
    CheckTypes(valuePtr, dp);

    InternalSetValue<Ptr<BaseComponent> >(dp, valuePtr, 0, 0, destination);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::AddChangedHandler(T* value, const DependencyProperty* dp)
{
    AddChangedHandler<T>(value, dp, 
        Core::Int2Type<Core::IsDerived<
            typename Core::If<Core::IsPtr<T>::Result, 
                typename Core::IsPtr<T>::PointedType, T>::Result,
            Core::BaseComponent>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::AddChangedHandler(T*, const DependencyProperty*, IsNotBaseComponent)
{
    // Nothing to do for values that are not BaseComponents
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::AddChangedHandler(T* value, const DependencyProperty* dp, IsBaseComponent)
{
    Freezable* freezable = IsFreezableValue((*value).GetPtr());
    if (freezable != 0)
    {
        InternalAddChangedHandler(freezable, dp);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::RemoveChangedHandler(const DependencyProperty* dp)
{
    RemoveChangedHandler<T>(dp,
        Core::Int2Type<Core::IsDerived<
            typename Core::If<Core::IsPtr<T>::Result, 
                typename Core::IsPtr<T>::PointedType, T>::Result,
            Core::BaseComponent>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::RemoveChangedHandler(const DependencyProperty*, IsNotBaseComponent)
{
    // Nothing to do for values that are not BaseComponents
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::RemoveChangedHandler(const DependencyProperty* dp, IsBaseComponent)
{
    InternalRemoveChangedHandler(dp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::InternalCoerceValue(const DependencyProperty* dp, StoredValue* sv,
    const void* defaultValue, NsSize sizeOfT)
{
    NS_PROFILE_MEM("Gui/DependencyObject");
    
    const void* uncoercedValue = sv ? sv->GetUncoercedValue(sizeOfT) : defaultValue;

    // Keep oldValue alive
    T oldValue = *static_cast<const T*>(InternalGetValue(dp, sv, defaultValue, sizeOfT));

    // Get coercedValue if applicable
    T coercedValue;
    if (!CoerceValue(uncoercedValue, &coercedValue, dp))
    {
        coercedValue = *static_cast<const T*>(uncoercedValue);
    }
    
    // We have coercion, so we must store a different value
    if (oldValue != coercedValue)
    {
        // Validate coerced value
        const DependencyProperty::ValidateValueDelegate& validateDelegate = 
            dp->GetValidateValueDelegate();
        if (validateDelegate)
        {
            validateDelegate(&coercedValue);
        }

        // Update stored value and notify if value changed
        if (!sv)
        {
            Core::nstl::pair<Values::iterator, NsBool> it = mValues.insert(dp);
            NS_ASSERT(it.second);

            sv = &it.first->second;
            sv->CreateComplex();
            sv->provider = ProviderValue::DefaultValueProviderPriority;
            
            Helper<T>::ConstructValue(&sv->value.complex->base,
                *static_cast<const T*>(defaultValue));
        }

        if (!sv->flags.isComplex)
        {
            // TODO [srodriguez] For types > sizeof(void*) the pointer memory could be reused
            Helper<T>::DestructValue(&sv->value.simple);

            // Create complex value
            sv->CreateComplex();

            // And store base and coerced value
            Helper<T>::ConstructValue(&sv->value.complex->base, oldValue);
        }

        if (sv->flags.isCoerced)
        {
            Helper<T>::CopyValue(&sv->value.complex->coerced, coercedValue);
        }
        else
        {
            Helper<T>::ConstructValue(&sv->value.complex->coerced, coercedValue);
            sv->flags.isCoerced = true;
        }

        sv->flags.isCoercedCurrentValue = false;
        NotifyPropertyChanged<T>(dp, sv, oldValue, coercedValue, true);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::NotifyPropertyChanged(const DependencyProperty* dp, StoredValue* sv,
    const T& oldValue, const T& newValue, NsBool valueChanged)
{
    // Check for value change
    if (valueChanged)
    {
        // Notify inheritors a new value is being set
        ObjectValueSet(oldValue, newValue, Core::Int2Type<Core::IsPtr<T>::Result>());

        if (IsInitialized())
        {
            // Unregister delegates from old value
            // NOTE: We could use directly InternalRemoveChangedHandler(dp) to avoid using the
            // template, but this has a runtime overhead because for simple types the call to 
            // InternalRemoveChangedHandler is going to look into the HashMap for the dp.
            RemoveChangedHandler<T>(dp);

            // Register delegates to new value
            AddChangedHandler<T>(const_cast<T*>(&newValue), dp);

            const T* pOldValue = &oldValue;

            // Check if value was initialized
            NS_ASSERT(sv != 0);
            if (!sv->flags.isInitialized)
            {
                // Use default as old value because this DP was never notified of change
                pOldValue = static_cast<const T*>(dp->GetDefaultValue(GetClassType()));

                // Mark stored value as initialized
                sv->flags.isInitialized = true;

                // Check again oldValue
                if (*pOldValue == newValue)
                {
                    return;
                }
            }

            // Notify
            DependencyPropertyChangedEventArgs args(dp, pOldValue, &newValue);
            OnPropertyChanged(args);

            // Initialization of new value
            if (!sv->flags.isExpression)
            {
                InitValue(newValue, Core::Int2Type<Core::IsPtr<T>::Result>());
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::ObjectValueSet(const T&, const T&, IsNotBaseComponent)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::ObjectValueSet(const T& oldValue, const T& newValue, IsBaseComponent)
{
    OnObjectValueSet(oldValue.GetPtr(), newValue.GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::InitValue(const T&, IsNotBaseComponent)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::InitValue(const T& newValue, IsBaseComponent)
{
    NS_ASSERT(IsInitialized());
    InitComponent(NsDynamicCast<IComponentInitializer*>(newValue.GetPtr()), true);
}

}
}
