////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DEPENDENCYPROPERTYIMPL_H__
#define __GUI_DEPENDENCYPROPERTYIMPL_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyProperty.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DependencyProperty implementation for a specific type
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class DependencyPropertyImpl: public DependencyProperty
{
public:
    /// Constructors
    //@{
    
    // NOTE: This constructors are intended to be used only from DependencyData
    //@{
    DependencyPropertyImpl(NsSymbol name);
    DependencyPropertyImpl(NsSymbol name, const Core::Type* type, NsSize size);
    DependencyPropertyImpl(NsSymbol name, const Core::Type* type, NsSize size,
        const Core::TypeClass* ownerType, const Ptr<PropertyMetadata>& metaData,
        const ValidateValueDelegate& delegate, PropertyAccess access = PropertyAccess_ReadWrite);
    //@}

    DependencyPropertyImpl(NsSymbol name, const Core::TypeClass* ownerType,
        PropertyAccess access = PropertyAccess_ReadWrite);

    DependencyPropertyImpl(NsSymbol name, const Core::TypeClass* ownerType,
        const Ptr<PropertyMetadata>& metaData, PropertyAccess access = PropertyAccess_ReadWrite);
        
    DependencyPropertyImpl(NsSymbol name, const Core::TypeClass* ownerType,
        const Ptr<PropertyMetadata>& metaData, const ValidateValueDelegate& delegate,
        PropertyAccess access = PropertyAccess_ReadWrite);
    //@}

    /// Destructor
    ~DependencyPropertyImpl();

    /// From DependencyProperty
    //@{
    const void* GetDefaultValue(const Core::TypeClass* type) const;
    void OverrideMetadata(const Core::TypeClass* forType,
        const Ptr<PropertyMetadata>& metadata) const;
    NsBool IsSameValue(const DependencyObject* obj,
        const Ptr<Core::BaseComponent>& value) const;
    NsBool IsSameValue(const Ptr<Core::BaseComponent>& left,
        const Ptr<Core::BaseComponent>& right) const;
    NsBool IsSameValue(const void* left, const void* right) const;
    void ConstructValue(void* ptr, const void* value) const;
    void DestroyValue(void* value) const;
    void CopyValue(void* ptr, const void* value) const;
    NsBool CheckType(const Core::Type* valueType) const;
    NsBool CheckType(const Ptr<Core::BaseComponent>& value) const;
    const void* GetValue(const Ptr<Core::BaseComponent>& value) const;
    const void* GetValue(const DependencyObject* obj) const;
    void SetValue(DependencyObject* obj, const void* value) const;
    void SetValue(DependencyObject* obj, const void* value, NsUInt8 priority,
        IExpression* expression = 0) const;
    Ptr<Core::BaseComponent> GetValueObject(const void* value) const;
    Ptr<Core::BaseComponent> GetValueObject(const DependencyObject* obj) const;
    void SetValueObject(DependencyObject* obj, const Ptr<Core::BaseComponent>& value) const;
    void SetCurrentValueObject(DependencyObject* obj, const Ptr<Core::BaseComponent>& value) const;
    Ptr<Core::BaseComponent> GetBaseValueObject(const DependencyObject* obj) const;
    void SetAnimationObject(DependencyObject* obj, const Ptr<Core::BaseComponent>& value) const;
    void ClearAnimation(DependencyObject* obj) const;
    void CoerceValue(DependencyObject* obj) const;
    void CoerceValue(DependencyObject* obj, StoredValue* storedValue,
        const void* defaultValue) const;
    //@}

private:
    typedef Core::Int2Type<0> T_NoBaseComponent;
    typedef Core::Int2Type<1> T_BaseComponent;

    /// From DependencyProperty
    //@{
    void SetValueObject(DependencyObject* obj, const Ptr<Core::BaseComponent>& value, 
        NsUInt8 priority, IExpression* expression = 0) const;
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION_(DependencyPropertyImpl, DependencyProperty)
};

}
}

#include <NsGui/DependencyPropertyImpl.inl>


#endif