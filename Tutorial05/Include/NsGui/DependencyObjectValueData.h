////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #751]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DEPENDENCYOBJECTVALUEDATA_H__
#define __GUI_DEPENDENCYOBJECTVALUEDATA_H__


#include <Noesis.h>
#include <NsGui/DependencySystemApi.h>
#include <NsCore/Ptr.h>
#include <NsCore/Vector.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyProperty;
NS_INTERFACE IExpression;
typedef void* ValueStorage;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Structure to store a dependency property value.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_DEPENDENCYSYSTEM_API StoredValue
{
    /// Stores the chain of values for a non-simple property
    struct ComplexValue
    {
        /// Stores the expression when the property is set using SetExpression or a 
        /// ValueProvider returned an expression
        Ptr<IExpression> expression;
        // Source value (using SetValue or returned by a ValueProvider), or if there is an
        /// expression stored above, this will contain the result of evaluating the expression
        ValueStorage base;
        /// Value set by animation using SetAnimate
        ValueStorage animated;
        /// If the property has a coerce callback in the metadata, the resulting value of 
        /// calling the animated or base value is stored here
        ValueStorage coerced;
    };

    union
    {
        /// Stores a simple value (of it's not an expression, nor is animated or coerced)
        ValueStorage simple;
        /// If the value is complex, stores a pointer to the ComplexValue struct
        ComplexValue* complex;
    } value;

    /// 8 bits for storing the priority of the provider which setted the value
    NsUInt8 provider;

    union
    {
        struct
        {
            // Indicate if the value is initialized
            NsBool isInitialized:1;
            // Indicate if the value union stores a simple or complex value
            NsBool isComplex:1;
            // The field ComplexValue::Expression is valid
            NsBool isExpression:1;
            // The field ComplexValue::Animated is valid
            NsBool isAnimated:1;
            // The field ComplesValue::Coerced is valid
            NsBool isCoerced:1;
            // The coerced value was set using SetCurrentValue
            NsBool isCoercedCurrentValue:1;
        } flags;

        // To quickly set all flags to 0
        NsUInt8 allFlags;
    };

    StoredValue();
    
    /// Create a complex struct, points value.complex to it and sets isComplex flag
    void CreateComplex();
    
    /// Returns the void* member (simple, value, animated or coerced) where the final value is 
    /// referenced
    ValueStorage GetFinalStorage() const;
    
    /// Passing void* storage, it returns the effective pointer to value
    static void* StorageToValue(const ValueStorage* storage, NsSize size);
    
    /// Returns a pointer to the final value
    void* GetFinalValue(NsSize sizeOfT) const;
    
    /// Returns a pointer to the final value without the coerce
    void* GetUncoercedValue(NsSize sizeOfT) const;
    
    /// Returns a pointer to the coerced value
    void* GetCoercedValue(NsSize sizeOfT) const;
    
    /// Returns a pointer to the source value (value.simple or value.complex.base)
    void* GetBaseValue(NsSize sizeOfT) const;

    /// Create a value in the passed storage field
    static void ConstructStorage(ValueStorage* dst, const void* src, 
        const DependencyProperty* dp);

    /// Destroy the value held in the passed storage field
    static void DestroyStorage(const ValueStorage* storage, const DependencyProperty* dp);
    
    /// Destroy all values (simple or complex)
    void DestroyAllValues(const DependencyProperty* dp);
};

}
}


#endif
