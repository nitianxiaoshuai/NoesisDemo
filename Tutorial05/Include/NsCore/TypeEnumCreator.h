////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEENUMCREATOR_H__
#define __CORE_TYPEENUMCREATOR_H__


#include <Noesis.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
class Type;
class TypeInfo;
class TypeEnum;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeEnumCreator. Helps in the creation of TypeEnum reflection.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class EnumT>
class TypeEnumCreator
{
public:
    /// Creates a TypeEnum for the specified type info
    static Type* Create(const TypeInfo& typeInfo);

    /// Fills TypeEnum with members of the enum
    static void Fill(Type* type);

    /// Adds meta data to the type enum
    //@{
    template<class T>
    void Meta();

    template<class T, class T1>
    void Meta(T1 t1);

    template<class T, class T1, class T2>
    void Meta(T1 t1, T2 t2);

    template<class T, class T1, class T2, class T3>
    void Meta(T1 t1, T2 t2, T3 t3);
    //@}

    /// Adds an enum value to the type enum
    void Val(const NsChar* name, NsInt value);

private:
    /// Constructor
    TypeEnumCreator(TypeEnum* typeEnum);

private:
    TypeEnum* mTypeEnum;
};

}
}


/// Inline include
#include <NsCore/TypeEnumCreator.inl>


#endif
