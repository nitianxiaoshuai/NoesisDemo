////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #781]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DEPENDENCYPROPERTY_H__
#define __GUI_DEPENDENCYPROPERTY_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Map.h>
#include <NsCore/Delegate.h>
#include <NsCore/Symbol.h>
#include <NsGui/DependencySystemApi.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
class Type;
class TypeProperty;
}
namespace Gui
{
class DependencyObject;
class PropertyMetadata;
class DependencyPropertySerializer;
struct StoredValue;
NS_INTERFACE IExpression;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum PropertyAccess
{
    PropertyAccess_ReadWrite,
    PropertyAccess_ReadOnly
};

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DependencyProperty. Represents a dependency property that is registered in the property system.
/// Dependency properties provide support for value expressions, property invalidation and
/// dependent-value coercion, default values, inheritance, data binding, animation, property change
/// notification, and styling.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_DEPENDENCYSYSTEM_API DependencyProperty: public Core::BaseComponent
{
public:
    typedef Core::Delegate<NsBool (const void* value)> ValidateValueDelegate;

    /// Constructors
    //@{
    DependencyProperty(NsSymbol name, const Core::Type* type, NsSize size);

    DependencyProperty(NsSymbol name, const Core::Type* type, NsSize size, 
        const Core::TypeClass* ownerType, PropertyAccess access = PropertyAccess_ReadWrite);

    DependencyProperty(NsSymbol name, const Core::Type* type, NsSize size,
        const Core::TypeClass* ownerType, const Ptr<PropertyMetadata>& metaData, 
        PropertyAccess access = PropertyAccess_ReadWrite);

    DependencyProperty(NsSymbol name, const Core::Type* type, NsSize size,
        const Core::TypeClass* ownerType, const Ptr<PropertyMetadata>& metaData, 
        const ValidateValueDelegate& delegate, PropertyAccess access = PropertyAccess_ReadWrite);
    //@}

    /// Destructor
    virtual ~DependencyProperty() = 0;

    /// Returns a static value that is used by the property system rather than a null Ptr to 
    /// indicate that the property exists, but does not have its value set by the property system.
    static Core::BaseComponent* GetUnsetValue();

    /// Gets property name
    inline NsSymbol GetName() const;

    /// Gets property type
    inline const Core::Type* GetType() const;

    /// Gets property owner type
    inline const Core::TypeClass* GetOwnerType() const;

    /// Gets property default value
    virtual const void* GetDefaultValue(const Core::TypeClass* type) const = 0;

    /// Gets property default value as a boxed object
    const Ptr<Core::BaseComponent>& GetDefaultValueObject(const Core::TypeClass* type) const;

    /// Checks if property is read-only
    inline NsBool IsReadOnly() const;
    
    /// Returns size of the property type
    inline NsSize GetSize() const;

    /// Gets property metaData
    //@{
    const Ptr<const PropertyMetadata>& GetMetaData(const Core::TypeClass* type) const;
    //@}

    /// Uses dependency property type information to override its metadata
    virtual void OverrideMetadata(const Core::TypeClass* forType,
        const Ptr<PropertyMetadata>& metadata) const = 0;

    /// Looks for a reflection property in the owner type of this dependency property with the same
    /// name. If not found, null is returned
    inline const Core::TypeProperty* GetTypeProperty() const;

    /// Finds a metaData in the corresponding reflection property
    /// \param T Type of the metaData to look for
    /// \return Returns metaData of the specified type if found, otherwise it returns null
    template<class T>
    const T* FindTypeMetaData() const;

    /// Compares the value of this property in the specified dependency object with
    /// the supplied value and returns true if they are the same
    virtual NsBool IsSameValue(const DependencyObject* obj,
        const Ptr<Core::BaseComponent>& value) const = 0;

    /// Compares 2 values and returns true when they are the same value
    virtual NsBool IsSameValue(const Ptr<Core::BaseComponent>& left,
        const Ptr<Core::BaseComponent>& right) const = 0;

    /// Compares 2 values and returns true when they are the same value
    virtual NsBool IsSameValue(const void* left, const void* right) const = 0;

    /// Constructs value object using property type information
    virtual void ConstructValue(void* ptr, const void* value) const = 0;

    /// Creates a new value in the heap returning a pointer to it
    //virtual void* CreateValue(const void* value) const = 0;

    /// Destroys value object using property type information
    virtual void DestroyValue(void* value) const = 0;

    /// Copies a value object over an existing one
    virtual void CopyValue(void* ptr, const void* value) const = 0;

    /// Indicates if the value type is valid for this property
    virtual NsBool CheckType(const Core::Type* valueType) const = 0;

    /// Indicates if the boxed value is valid for this property type
    virtual NsBool CheckType(const Ptr<Core::BaseComponent>& value) const = 0;

    /// Gets an unboxed value for this property from a boxed or a Ptr object value
    /// \remarks When value represents a Ptr object the exact type (Ptr<BaseComponent>) must be
    /// passed as the function argument, if not, a temporal Ptr object will be created and the
    /// address returned will point to invalid memory
    virtual const void* GetValue(const Ptr<Core::BaseComponent>& value) const = 0;

    /// Gets the a boxed value or Ptr object for this property from a raw pointer
    virtual Ptr<Core::BaseComponent> GetValueObject(const void* value) const = 0;

    /// Gets or sets the raw value of the property from the specified dependency object
    //@{
    virtual const void* GetValue(const DependencyObject* obj) const = 0;
    virtual void SetValue(DependencyObject* obj, const void* value) const = 0;
    //@}

    /// Gets or sets the (boxed) value of this property in the given dependency object
    //@{
    virtual Ptr<Core::BaseComponent> GetValueObject(const DependencyObject* obj) const = 0;
    virtual void SetValueObject(DependencyObject* obj, const Ptr<Core::BaseComponent>& value) 
        const = 0;
    virtual void SetCurrentValueObject(DependencyObject* obj, const Ptr<Core::BaseComponent>& value)
        const = 0;
    //@}

    /// Gets the boxed baseValue of this property in the given dependency object
    virtual Ptr<Core::BaseComponent> GetBaseValueObject(const DependencyObject* obj) const = 0;

    /// Sets the boxed value as the property animation value in the given dependency object
    virtual void SetAnimationObject(DependencyObject* obj, 
        const Ptr<Core::BaseComponent>& value) const = 0;

    /// Clears the animation value
    virtual void ClearAnimation(DependencyObject* obj) const = 0;

    // Coerces and validates the effective value
    virtual void CoerceValue(DependencyObject* obj) const = 0;

    /// Indicates if the specified value is valid for this property. The value is verifyed against
    /// property type and property validate callback
    NsBool IsValidValue(const Ptr<Core::BaseComponent>& value) const;

    /// Public methods to change internal values. Are used from DependencyData
    //@{
    void SetOwnerType(const Core::TypeClass* owner);
    void SetIsReadOnly(NsBool value);
    void AddMetaData(const PropertyMetadata* metaData);
    void AddMetaData(const Core::TypeClass* type, const PropertyMetadata* metaData);
    void SetValidateValueDelegate(const ValidateValueDelegate& validate);
    //@}

    inline const ValidateValueDelegate& GetValidateValueDelegate() const;

protected:
    virtual void SetValue(DependencyObject* obj, const void* value, NsUInt8 priority,
        IExpression* expression = 0) const = 0;
    virtual void SetValueObject(DependencyObject* obj, const Ptr<Core::BaseComponent>& value,
        NsUInt8 priority, IExpression* expression = 0) const = 0;
    virtual void CoerceValue(DependencyObject* obj, StoredValue* storedValue,
        const void* defaultValue) const = 0;

private:
    friend class DependencyObject;
    friend class DependencyObjectTest;
    friend class DependencyPropertyTest;
    friend class Freezable;

    // Indicates if value is valid for this property according to the validate callback
    NsBool ValidateValue(const void* value) const;

    void MergeMetaData(PropertyMetadata* pmd, const Core::TypeClass* type);

private:
    NsSymbol mName;
    const Core::Type* mType;
    const Core::TypeClass* mOwnerType;
    NsSize mSize;
    ValidateValueDelegate mValidateValueDelegate;
    NsBool mIsReadOnly;
    
    mutable Ptr<DependencyPropertySerializer> mSerializer;

    typedef NsMap<const Core::TypeClass*, Ptr<const PropertyMetadata> > MetaDatas;
    mutable MetaDatas mMetaDatas;

    NS_DECLARE_REFLECTION(DependencyProperty, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

/// Search for dependency properties in the class hierarchy
NS_GUI_DEPENDENCYSYSTEM_API const DependencyProperty* FindDependencyProperty(
    const Core::TypeClass* typeClass, NsSymbol propId);

}
}

#include <NsGui/DependencyProperty.inl>


#endif
