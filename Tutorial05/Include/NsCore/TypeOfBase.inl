////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <Noesis.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/TypeEnumHelper.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
class Type;
class TypeClass;
class TypeEnum;
//@}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeOfHelper for classes and enums.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class TypeOfHelper
{
private:
    struct Class
    {
        typedef TypeClass ReturnType;
        static const ReturnType* Get() { return T::StaticGetClassType(); }
    };

    struct Enum
    {
        typedef TypeEnum ReturnType;
        static const ReturnType* Get() { return TypeEnumHelper<T>::GetType(); }
    };

    typedef typename If<IsEnum<T>::Result, Enum, Class>::Result ClassEnumCheck;

public:
    typedef typename ClassEnumCheck::ReturnType ReturnType;

    static const ReturnType* Get()
    {
        return ClassEnumCheck::Get();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class used to implement TypeOf.
/// \param ReturnT Class of the reflection type returned by TypeOf
/// \param CreateT Class of the concrete reflection type that will be created and registered
/// \param T Type that was passed to TypeOf
/// \param S Type passed to typeid to get the corresponding TypeInfo stored in Type
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ReturnT, class CreateT, class T, class S = T>
class TypeOfHelperBase
{
public:
    typedef ReturnT ReturnType;

    static const ReturnT* Get()
    {
        static const ReturnT* type;

        if (type == 0)
        {
            type = static_cast<const ReturnT*>(TypeCreate::Create(NS_TYPEID(S), Create,
                TypeOfHelper<T>::Fill));
        }

        return type;
    }

private:
    static Type* Create(const TypeInfo& typeInfo)
    {
        return new CreateT(typeInfo);
    }

    static void Fill(Type*)
    {
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const typename TypeOfHelper<T>::ReturnType* TypeOf()
{
    return TypeOfHelper<T>::Get();
}

typedef Noesis::Core::NullType NoParent;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeOf specialization for NoParent.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class TypeOfHelper<NoParent>
{
public:
    typedef Type ReturnType;

    static const ReturnType* Get()
    {
        return 0;
    }
};

}
}
