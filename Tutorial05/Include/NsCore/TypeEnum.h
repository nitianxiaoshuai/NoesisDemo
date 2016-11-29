////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEENUM_H__
#define __CORE_TYPEENUM_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/Symbol.h>
#include <NsCore/TypeMeta.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Vector.h>


namespace Noesis
{
namespace Core
{
// Forward declarations
//@{
class BoxedValue;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeEnum. Defines reflection info for enumerations.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypeEnum: public TypeMeta
{
public:
    /// Constructor
    TypeEnum(const TypeInfo& typeInfo);

    /// Destructor
    ~TypeEnum();

    /// Defines enum value information
    struct ValueInfo
    {
        NsSymbol id;
        NsInt value;

        ValueInfo(NsSymbol i, NsInt v): id(i), value(v) { }
    };

    /// Gets number of enumeration values
    NsSize GetNumValues() const;

    /// Gets enum value info
    const ValueInfo* GetValueInfo(NsSize index) const;

    /// Indicates if an enum defines the specified value
    //@{
    NsBool HasValue(NsSymbol id) const;
    NsBool HasValue(NsInt value) const;
    //@}

    /// Gets value of the specified enumeration identifier
    /// An error occurrs if the identifier is not defined in the enumeration
    //@{
    NsInt GetValue(NsSymbol id) const;
    NsSymbol GetValue(NsInt value) const;
    //@}
    
    /// Gets a boxed value of the specified enumeration identifier
    /// An error occurrs if the identifier is not defined in the enumeration
    virtual Ptr<BoxedValue> GetValueObject(NsSymbol id) const = 0;

    /// Enumeration type creation
    void AddValue(NsSymbol id, NsInt value);

private:
    const ValueInfo* TryGetValueInfo(NsSymbol id) const;
    const ValueInfo* TryGetValueInfo(NsInt value) const;

private:
    typedef NsVector<ValueInfo*> ValueVector;
    ValueVector mValues;

    NS_DECLARE_REFLECTION(TypeEnum, TypeMeta)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
