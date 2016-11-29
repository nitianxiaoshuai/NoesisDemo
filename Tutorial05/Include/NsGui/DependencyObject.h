////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #751]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DEPENDENCYOBJECT_H__
#define __GUI_DEPENDENCYOBJECT_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/Delegate.h>
#include <NsCore/HashMap.h>
#include <NsCore/NSTLPoolAllocator.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/DependencySystemApi.h>
#include <NsGui/DependencyObjectValueData.h>
#include <NsGui/ChangedHandler.h>
#include <NsGui/ValueDestination.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// The following macro should be used by DependencyObject derived classes inside their constructors
/// when they need to set dependency properties. This way derived classes ensure that dependency
/// property identifiers are properly created.
////////////////////////////////////////////////////////////////////////////////////////////////////
#define ForceCreateDependencyProperties Noesis::Core::TypeOf<SelfClass>


NS_CFORWARD(Gui, DependencyObject)
NS_CFORWARD(Gui, DependencyProperty)
NS_CFORWARD(Gui, Freezable)
NS_CFORWARD(Gui, ChangedHandler)
NS_SFORWARD(Gui, ProviderValue)
NS_SFORWARD(Gui, DependencyPropertyChangedEventArgs)
NS_IFORWARD(Gui, IExpression)


namespace Noesis
{
namespace Gui
{

namespace BoxingUtils
{
template<class T> void SetBoxedValue(DependencyObject*, const DependencyProperty*,
    const Ptr<Core::BaseComponent>&, NsUInt8, IExpression* expression,
    Value::Destination destination, Core::Int2Type<0>);
template<class T> void SetBoxedValue(DependencyObject*, const DependencyProperty*,
    const Ptr<Core::BaseComponent>&, NsUInt8, IExpression* expression,
    Value::Destination destination, Core::Int2Type<1>);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Param type for DependencyObject::SetValue<T>
//
//      Property Type  | Param Type
//      ---------------------------------------
//      Ptr<T>           T*
//      NsString         const NsChar*
//      T                T (basic types) or T&
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct SetValueType
{
    typedef typename Core::If<Core::IsPtr<T>::Result, 
        typename Core::IsPtr<T>::PointedType*,
        typename Core::If<Core::IsSame<T, NsString>::Result, 
            const NsChar*,
            typename Core::Param<T>::Type>::Result
        >::Result Type;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an object that participates in the dependency property system.
///
/// The DependencyObject class enables the property system services on its many derived classes.
/// The property system's primary function is to compute the values of properties, and to provide
/// system notification about values that have changed. Another key class that participates in the
/// property system is DependencyProperty. DependencyProperty enables the registration of
/// dependency properties into the property system, and provides identification and information
/// about each dependency property, whereas DependencyObject as a base class enables objects to use
/// the dependency properties.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.dependencyobject.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_DEPENDENCYSYSTEM_API DependencyObject: public Core::BaseComponent,
    public IComponentInitializer
{
public:
    /// Constructor
    DependencyObject();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~DependencyObject() = 0;

    /// Gets the provider that returns the effective value for the specified dependency property
    NsUInt8 GetValueProvider(const DependencyProperty* dp) const;

    /// Returns the current effective value of a dependency property on this instance of a
    /// DependencyObject
    template<class T>
    const T& GetValue(const DependencyProperty* dp) const;

    /// Returns the current effective value of a dependency property on this instance of a
    /// DependencyObject as a boxed value
    Ptr<Core::BaseComponent> GetValueObject(const DependencyProperty* dp) const;
    
    /// Returns the local value of a dependency property, if it exists. 
    Ptr<Core::BaseComponent> GetLocalValue(const DependencyProperty* dp) const;
    
    /// Returns the base value without animation nor coerce (this never returns IExpression like
    /// GetLocalValue)
    template<class T>
    const T& GetBaseValue(const DependencyProperty* dp) const;

    /// Sets the local value of a dependency property
    /// \remarks Once set, local value is only removed when calling ClearValue()
    template<class T>
    void SetValue(const DependencyProperty* dp, typename SetValueType<T>::Type value);

    /// Sets the local value of a dependency property using a boxed value
    /// \remarks Once set, local value is only removed when calling ClearValue()
    void SetValueObject(const DependencyProperty* dp, const Ptr<Core::BaseComponent>& value);
    
    /// Sets the current value of a dependency property. The current value is set on the coerce
    /// field, without modifying source or animated value
    template<class T>
    void SetCurrentValue(const DependencyProperty* dp, typename SetValueType<T>::Type value);
    
    /// Sets the current value of a dependency property using a boxed value
    void SetCurrentValueObject(const DependencyProperty* dp, const Ptr<Core::BaseComponent>& value);

    /// Sets the expression to be evaluated dynamically to obtain the value of the property
    void SetExpression(const DependencyProperty* dp, IExpression* expression);

    /// Clears the local value of a property
    /// The property to be cleared is specified by a DependencyProperty identifier
    void ClearLocalValue(const DependencyProperty* dp);
    
    /// Re-evaluates the effective value for the specified dependency property if necessary
    /// \param provider The value provider that originated the property invalidation. If null is
    /// passed, a full re-evaluation could be needed
    void InvalidateProperty(const DependencyProperty* dp, NsUInt8 priority = 1);
    
    /// Sets the animated value of a property
    template<class T>
    void SetAnimation(const DependencyProperty* dp, typename SetValueType<T>::Type value);

    /// Clears the animation value of a property
    template<class T>
    void ClearAnimation(const DependencyProperty* dp);
    void ClearAnimation(const DependencyProperty* dp);
    
    /// Coerces and validates the effective property value
    template<class T>
    void CoerceValue(const DependencyProperty* dp);
    void CoerceValue(const DependencyProperty* dp);

    /// Returns if the value is stored in the cache. If true, the priority is returned in the 
    /// provider field
    NsBool IsCached(const DependencyProperty* dp, NsUInt8* provider) const;
    
    /// Returns true if there is any animated property
    NsBool HasAnimatedProperties() const;

    typedef Core::Delegate<void (Core::BaseComponent*, const DependencyPropertyChangedEventArgs&)>
        DependencyPropertyChangedEventHandler;

    /// Returns the PropertyChanged event
    inline DependencyPropertyChangedEventHandler& DependencyPropertyChanged();
    
    // HACK #884
    //@{
    typedef Core::Delegate<void (DependencyObject*)> DestroyedDelegate;
    inline DestroyedDelegate& Destroyed();
    //@}

    /// From IComponentInitializer
    //@{
    NsBool IsInitialized() const;
    void Init();
    //@}

protected:
    /// Calls Destroyed delegate before destroying the object
    NsInt32 OnDestroy() const;

    /// Used by derived classes to set read-only properties
    //@{
    template<class T>
    void SetReadOnlyProperty(const DependencyProperty* dp,
        typename SetValueType<T>::Type value) const;
    void SetReadOnlyExpression(const DependencyProperty* dp, IExpression* expr) const;
    //@}
    
    /// Indicates whether the property is set to its default value
    NsBool IsDefaultValue(const DependencyProperty* dp) const;

    /// Used by derived classes to clear read-only properties
    void ClearReadOnlyProperty(const DependencyProperty* dp);

    /// Called to initialize inheritors
    virtual void OnInit();
    
    /// Called when initialization process is completed
    virtual void OnPostInit();

    /// Called to allow descendants to manage a property value change
    /// \return True when it has been processed, otherwise false
    virtual NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);

    /// Called to allow descendants to manage a sub property value change
    /// \return True when it has been processed, otherwise false
    virtual NsBool OnSubPropertyChanged(const DependencyProperty* dp);

    /// Called to allow descendants to manage a component value change
    virtual void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue);

    /// Gets the value of a dependency property from the active provider
    //@{
    virtual ProviderValue GetProviderValue(const DependencyProperty* dp) const;
    virtual ProviderValue GetNonCachedProviderValue(const DependencyProperty* dp) const;
    virtual NsUInt8 GetNonCachedValueProvider(const DependencyProperty* dp) const;
    //@}

    void InternalSetValue(const DependencyProperty* dp, const void* value, NsUInt8 priority,
        IExpression* newExpression = 0);

    template<class T>
    void InternalSetValue(const DependencyProperty* dp, const T& value, NsUInt8 priority, 
        IExpression* newExpression = 0, Value::Destination destination = 
        Value::Destination_BaseValue);

    void InternalSetExpression(const DependencyProperty* dp, IExpression* newExpression, 
        NsUInt8 priority);

protected:
    // Friend classes and functions
    //@{
    friend class ChangedHandler;
    friend class DependencyObjectTest;
    friend struct BindingOperations;
    template<class T> friend class DependencyPropertyImpl;
    template<class T> friend void BoxingUtils::SetBoxedValue(DependencyObject*, 
        const DependencyProperty*, const Ptr<Core::BaseComponent>&, NsUInt8,
        IExpression* expression, Value::Destination destination, Core::Int2Type<0>);
    template<class T> friend void BoxingUtils::SetBoxedValue(DependencyObject*, 
        const DependencyProperty*, const Ptr<Core::BaseComponent>&, NsUInt8, 
        IExpression* expression, Value::Destination destination, Core::Int2Type<1>);
    //@}

    /// Hash of stored properties
    typedef NsHashMap<const DependencyProperty*, StoredValue,
        eastl::hash<const DependencyProperty*>, eastl::equal_to<const DependencyProperty*>,
        Core::nstl::PoolAllocator> Values;
    mutable Values mValues;

private:
    /// Base classes are non-copyable objects
    //@{
    DependencyObject(const DependencyObject&);
    DependencyObject& operator=(const DependencyObject&);
    //@}

    template<class T>
    struct Helper
    {
        static void CopyValue(ValueStorage* storage, 
            typename Core::Param<T>::Type value);
        static void ConstructValue(ValueStorage* storage, 
            typename Core::Param<T>::Type value);
        static void DestructValue(ValueStorage* storage);
    };

    void CheckTypes(const Core::Type* valueType, const DependencyProperty* dp) const;
    void CheckTypes(const Ptr<BaseComponent>& value, const DependencyProperty* dp) const;
    void CheckReadOnly(const DependencyProperty* dp) const;
    NsBool CoerceValue(const void* value, void* coercedValue, const DependencyProperty* dp) const;
    StoredValue& ValidateAndGetEntry(const void *value, const DependencyProperty *dp,
        NsBool& justCreated);
    NsBool EvaluateLocalExpression(IExpression*& newExpression, StoredValue& sv, 
        const DependencyProperty* dp, const void* value, NsBool valueChanged);
    void NotifyLocalExpression(IExpression* expression, const DependencyProperty* dp, 
        const void* value, NsBool valueChanged);
    void StoreExpression(IExpression* expression, StoredValue& sv);
    StoredValue* DestroyCachedValue(const DependencyProperty* dp);

    // Helpers
    //@{
    typedef Core::Int2Type<0> IsNotBaseComponent;
    typedef Core::Int2Type<1> IsBaseComponent;

    template<class T>
    void SetValue_(IsNotBaseComponent, const DependencyProperty* dp,
        typename Core::Param<T>::Type value,
        Value::Destination destination = Value::Destination_BaseValue);

    template<class T>
    void SetValue_(IsBaseComponent, const DependencyProperty* dp, typename T::Type* value,
        Value::Destination destination = Value::Destination_BaseValue);
    //@}

    // Management of properties that contain objects that implement INotifyChange
    //@{
    template<class T>
    void AddChangedHandler(T* value, const DependencyProperty* dp);
    template<class T>
    void AddChangedHandler(T* value, const DependencyProperty* dp, IsNotBaseComponent);
    template<class T>
    void AddChangedHandler(T* value, const DependencyProperty* dp, IsBaseComponent);
    void InternalAddChangedHandler(Freezable* freezable, const DependencyProperty* dp);

    template<class T>
    void RemoveChangedHandler(const DependencyProperty* dp);
    template<class T>
    void RemoveChangedHandler(const DependencyProperty* dp, IsNotBaseComponent);
    template<class T>
    void RemoveChangedHandler(const DependencyProperty* dp, IsBaseComponent);
    void InternalRemoveChangedHandler(const DependencyProperty* dp);
    //@}

    void InternalInvalidateProperty(const DependencyProperty* dp, NsUInt8 priority);
    const void* InternalGetUncachedValue(const DependencyProperty* dp,
        const void* defaultValue) const;
    const void* InternalGetValue(const DependencyProperty* dp, NsSize sizeOfT) const;
    const void* InternalGetBaseValue(const DependencyProperty* dp, NsSize sizeOfT) const;
    void InternalNotifyValueChange(const DependencyProperty* dp, const void* finalValue,
        const void* defaultValue);

    // Implementation of coerce value
    template<class T>
    void InternalCoerceValue(const DependencyProperty* dp, StoredValue* storedValue,
        const void* defaultValue, NsSize sizeOfT);
    const void* InternalGetValue(const DependencyProperty* dp, StoredValue* storedValue,
        const void* defaultValue, NsSize sizeOfT);

    // Launches OnPropertyChange when value changes by a SetValue or ClearValue
    template<class T>
    void NotifyPropertyChanged(const DependencyProperty* dp, StoredValue* storedValue,
        const T& oldValue, const T& newValue, NsBool valueChanged);

    template<class T>
    void ObjectValueSet(const T& oldValue, const T& newValue, IsNotBaseComponent);
    template<class T>
    void ObjectValueSet(const T& oldValue, const T& newValue, IsBaseComponent);

    template<class T>
    void InitValue(const T& newValue, IsNotBaseComponent);
    template<class T>
    void InitValue(const T& newValue, IsBaseComponent);

    NsBool IsInitializing() const;
    Freezable* IsFreezableValue(Core::BaseComponent* value) const;

private:
    struct ValueInfo;

    NsUInt32 mFlags;

    /// List of handlers attached to property objects to monitor changes
    /// TODO [srodriguez] Maybe this can be a simple std::set because the value is already stored
    /// in the Values map
    typedef NsHashMap<const DependencyProperty*, ChangedHandler,
        eastl::hash<const DependencyProperty*>, eastl::equal_to<const DependencyProperty*>,
        Core::nstl::PoolAllocator> ChangedHandlers;
    ChangedHandlers mChangedHandlers;

    /// Dependency property changed event
    DependencyPropertyChangedEventHandler mDependencyPropertyChangedEvent;

    // HACK #884
    //@{
    DestroyedDelegate mDestroyedDelegate;
    //@}

    NS_DECLARE_REFLECTION(DependencyObject, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DependencyPropertyChangedEventArgs. Args passed on property changed event notification.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_DEPENDENCYSYSTEM_API DependencyPropertyChangedEventArgs
{
    const DependencyProperty* prop;
    const void* oldValue;
    const void* newValue;

    /// Constructor
    DependencyPropertyChangedEventArgs(const DependencyProperty* dp,
        const void* ov, const void* nv);

    NS_DECLARE_REFLECTION(DependencyPropertyChangedEventArgs, Core::NoParent)
};

}
}

#include <NsGui/DependencyObject.inl>


#endif
