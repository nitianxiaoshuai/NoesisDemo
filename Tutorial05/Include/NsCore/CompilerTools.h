////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_COMPILERTOOLS_H__
#define __CORE_COMPILERTOOLS_H__


#include <Noesis.h>


namespace Noesis
{
namespace Core
{

class Symbol;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper types Small and Big - guarantee that sizeof(Small) < sizeof(Big).
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
typedef NsChar Small;
struct Big { NsChar dummy[2]; };
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Generates a different type for each template parameter value.
/// Could be used to select functions in compile time.
////////////////////////////////////////////////////////////////////////////////////////////////////
template <NsInt N> struct Int2Type
{
    enum { Result = N };
};

////////////////////////////////////////////////////////////////////////////////
// Converts each type into a unique, insipid type
// Defines the type OriginalType which maps back to T
////////////////////////////////////////////////////////////////////////////////
template <class T> struct Type2Type
{
    typedef T OriginalType;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// If-Then-Else statements.
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
template<NsBool Condition, class Then, class Else> struct If;

template<class Then, class Else> struct If<true, Then, Else>
{
    typedef Then Result;
};

template<class Then, class Else> struct If<false, Then, Else>
{
    typedef Else Result;
};
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if a class type is const and permits getting base type
///
///   Example:
///     IsConst<MyClass>::Result             -> false
///     IsConst<const MyClass>::Result       -> true
///     IsConst<const MyClass>::NonConstType -> MyClass
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsConst
{
private:
    template<class U> struct ConstTraits
    {
        enum { Result = false };
        typedef U Type;
    };
    template<class U> struct ConstTraits<const U>
    {
        enum { Result = true };
        typedef U Type;
    };
    template<class U> struct ConstTraits<const U&>
    {
        enum { Result = true };
        typedef U& Type;
    };

public:
    enum { Result = ConstTraits<T>::Result };
    typedef typename ConstTraits<T>::Type NonConstType;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if a class type is volatile and permits getting base type
///
///   Example:
///     IsVolatile<MyClass>::Result                   -> false
///     IsVolatile<volatile MyClass>::Result          -> true
///     IsVolatile<volatile MyClass>::NonVolatileType -> MyClass
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsVolatile
{
private:
    template<class U> struct VolatileTraits
    {
        enum { Result = false };
        typedef U Type;
    };
    template<class U> struct VolatileTraits<volatile U>
    {
        enum { Result = true };
        typedef U Type;
    };
    template<class U> struct VolatileTraits<volatile U&>
    {
        enum { Result = true };
        typedef U& Type;
    };

public:
    enum { Result = VolatileTraits<T>::Result };
    typedef typename VolatileTraits<T>::Type NonVolatileType;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Removes the const and/or volatile qualifiers from type
///
///   Example:
///     UnqualifiedType<MyClass>::Result                -> MyClass
///     UnqualifiedType<const MyClass>::Result          -> MyClass
///     UnqualifiedType<volatile MyClass>::Result       -> MyClass
///     UnqualifiedType<const volatile MyClass>::Result -> MyClass
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct UnqualifiedType
{
    typedef typename IsVolatile<typename IsConst<T>::NonConstType>::NonVolatileType Type;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if a class derives from another.
///
///   Example:
///     class Father { };
///     class Child: public Father { };
///     IsDerived<Child, Father>::Result -> true;
///     IsDerived<Father, Child>::Result -> false;
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class U> class IsDerived
{
private:
    typedef typename IsConst<T>::NonConstType NonConstT;
    typedef typename IsConst<U>::NonConstType NonConstU;

    static Big Test(...);
    static Small Test(NonConstU*);

    static NonConstT* MakeT();

public:
    enum { Result = (sizeof(Small) == sizeof(Test(MakeT()))) };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if two types are the same.
///
///   Example:
///     class Father { };
///     class Child: public Father { };
///     IsSame<Child, Father>::Result -> false
///     IsSame<Child, Child>::Result  -> true
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
template<class T, class U> struct IsSame
{
    enum { Result = false };
};

template<class T> struct IsSame<T, T>
{
    enum { Result = true };
};
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if a type is void.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct IsVoid
{
    enum { Result = IsSame<typename UnqualifiedType<T>::Type, void>::Result };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if a class type is a pointer and permits getting pointed type.
///
///   Example:
///     IsPointer<MyClass>::Result       -> false
///     IsPointer<MyClass*>::Result      -> true
///     IsPointer<MyClass*>::PointedType -> MyClass
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsPointer
{
private:
    template<class U> struct PointerTraits
    {
        enum { Result = false };
        typedef NullType Type;
    };
    template<class U> struct PointerTraits<U*>
    {
        enum { Result = true };
        typedef U Type;
    };

public:
    enum { Result = PointerTraits<typename UnqualifiedType<T>::Type>::Result };
    typedef typename PointerTraits<typename UnqualifiedType<T>::Type>::Type PointedType;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if T is a pointer to function
///
///   Example:
///     IsPointer<int*>::Result              -> false
///     IsPointer<void (*)()>::Result        -> true
///     IsPointer<NsBool (*)(NsInt)>::Result -> true
////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class IsFunctionPointer
{
private:
    template<class U>
    struct FunctionPointerTraits
    { 
        enum{ Result = false}; 
    };
    
    template<class U> 
    struct FunctionPointerTraits<U(*)()>
    { 
        enum{ Result = true}; 
    };

    template<class U, class T1> 
    struct FunctionPointerTraits<U(*)(T1)> 
    {
        enum {Result = true};
    };

    template<class U, class T1, class T2>
    struct FunctionPointerTraits<U(*)(T1, T2)> 
    {
        enum {Result = true};
    };

    template<class U, class T1, class T2, class T3>
    struct FunctionPointerTraits<U(*)(T1, T2, T3)> 
    {
        enum {Result = true};
    };

    template<class U, class T1, class T2, class T3, class T4>
    struct FunctionPointerTraits<U(*)(T1, T2, T3, T4)> 
    {
        enum {Result = true};
    };

    template<class U, class T1, class T2, class T3, class T4, class T5>
    struct FunctionPointerTraits<U(*)(T1, T2, T3, T4, T5)> 
    {
        enum {Result = true};
    };

    template<class U, class T1, class T2, class T3, class T4, class T5, class T6>
    struct FunctionPointerTraits<U(*)(T1, T2, T3, T4, T5, T6)> 
    {
        enum {Result = true};
    };

    template<class U, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    struct FunctionPointerTraits<U(*)(T1, T2, T3, T4, T5, T6, T7)> 
    {
        enum {Result = true};
    };

    // TODO [srodriguez] Implement vble args version (class T, ...)
public:
    enum { Result = FunctionPointerTraits<typename UnqualifiedType<T>::Type>::Result };
};

// TODO [srodriguez] Implement pointer to class member and to class methods (with and without ...)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if T is ref counted (derived from Interface or BaseRefCounted).
/// If Result is true, the type T can be stored inside a Ptr<>
///
///   Example:
///     NS_STATIC_ASSERT(IsRefCounted<int>::Result == 0, _CONDITION_IS_NOT_TRUE_);
///     NS_STATIC_ASSERT(IsRefCounted<Interface>::Result == 1, _CONDITION_IS_NOT_TRUE_);
///     NS_STATIC_ASSERT(IsRefCounted<const IUnitTest>::Result == 1, _CONDITION_IS_NOT_TRUE_);
///     NS_STATIC_ASSERT(IsRefCounted<CompTest>::Result == 1, _CONDITION_IS_NOT_TRUE_);
///     NS_STATIC_ASSERT(IsRefCounted<const CompTest>::Result == 1, _CONDITION_IS_NOT_TRUE_);
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE Interface;
class BaseRefCounted;

// To avoid the warning when casting from a component to Interface and the cast is ambiguous
template<class T> struct Disambiguate
{
    typedef typename If<IsDerived<T,BaseRefCounted>::Result, BaseRefCounted, T>::Result Result;
};

template<class T> struct IsRefCounted
{
    typedef typename Disambiguate<T>::Result TT;
    enum {  Result = IsDerived<TT, BaseRefCounted>::Result || IsDerived<TT, Interface>::Result };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if T is an interface.
///
///   Example:
///     NS_STATIC_ASSERT(IsInterface<int>::Result == 0, _CONDITION_IS_NOT_TRUE_);
///     NS_STATIC_ASSERT(IsInterface<UnitTestSystem>::Result == 0, _CONDITION_IS_NOT_TRUE_);
///     NS_STATIC_ASSERT(IsInterface<Interface>::Result == 1, _CONDITION_IS_NOT_TRUE_);
///     NS_STATIC_ASSERT(IsInterface<IUnitTest>::Result == 1, _CONDITION_IS_NOT_TRUE_);
///     NS_STATIC_ASSERT(IsInterface<const IUnitTest>::Result == 1, _CONDITION_IS_NOT_TRUE_);
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct IsInterface
{
    typedef typename Disambiguate<T>::Result TT;
    enum { Result = !IsDerived<TT, BaseRefCounted>::Result && IsDerived<TT, Interface>::Result };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if a class type is a Ptr and permits getting pointed type.
///
///   Example:
///     IsPtr<MyClass>::Result            -> false
///     IsPtr<Ptr<MyClass> >::Result      -> true
///     IsPtr<Ptr<MyClass> >::PointedType -> MyClass
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
template<class T> class Ptr;

template<class T> class IsPtr
{
private:
    template<class U> struct PtrTraits
    {
        enum { Result = false };
        typedef U Type;
    };
    template<class U> struct PtrTraits<Ptr<U> >
    {
        enum { Result = true };
        typedef U Type;
    };

public:
    enum { Result = PtrTraits<typename UnqualifiedType<T>::Type>::Result };
    typedef typename PtrTraits<typename UnqualifiedType<T>::Type>::Type PointedType;
};
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if a class type is a reference and permits getting base type
///
///   Example:
///     IsReference<MyClass>::Result            -> false
///     IsReference<MyClass&>::Result           -> true
///     IsReference<MyClass&>::ReferredType     -> MyClass
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsReference
{
private:
    template<class U> struct ReferenceTraits
    {
        enum { Result = false };
        typedef U Type;
    };
    template<class U> struct ReferenceTraits<U&>
    {
        enum { Result = true };
        typedef U Type;
    };

public:
    enum { Result = ReferenceTraits<T>::Result };
    typedef typename ReferenceTraits<T>::Type NonReferenceType;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks in compile time if a type is an array type.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsArray
{
private:
    template<class R> static R (* Check1(Type2Type<R>) )(Type2Type<R>);
    template<class R> static NsChar Check1(...);

    template<class R> static Big Check2(R(*)(Type2Type<R>));
    template<class R> static Small Check2(...);

public:
    enum { Result = sizeof(Small) == sizeof(Check2<T>(Check1<T>(Type2Type<T>()))) };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns the bigger size type from two types.
///
///   Example:
///     MaxSizeType<NsChar, NsFloat32>::Result k = 10.0f;
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T0, class T1> struct MaxSizeType
{
    typedef typename If<sizeof(T0) >= sizeof(T1), T0, T1>::Result Result;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns the smaller size type from two types.
///
///   Example:
///     MinSizeType<NsChar, NsFloat32>::Result c = 'a';
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T0, class T1> struct MinSizeType
{
    typedef typename If<sizeof(T0) <= sizeof(T1), T0, T1>::Result Result;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks if type is a class, struct or union.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsClass
{
private:
  template<class R> static Small Check(void (R::* fn) (void) = 0);
  template<class R> static Big Check(...);

public:
    enum { Result = (sizeof(Small) == sizeof(Check<T>(0))) };
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks if type is scalar (integer or bool)
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsScalar
{
private:
    struct NotScalar {};

    struct BoolConvert
    {
        BoolConvert(bool);
        BoolConvert(char);
        BoolConvert(signed char);
        BoolConvert(unsigned char);
        BoolConvert(signed short);
        BoolConvert(unsigned short);
        BoolConvert(signed int);
        BoolConvert(unsigned int);
        BoolConvert(signed long);
        BoolConvert(unsigned long);
        BoolConvert(signed long long);
        BoolConvert(unsigned long long);
    };

    static Small Check(BoolConvert);
    static Big Check(...);

    typedef typename If<IsVoid<T>::Result || IsReference<T>::Result || IsArray<T>::Result,
        NotScalar,
        T>::Result ScalarType;

    static ScalarType& MakeScalarType();

public:
    enum { Result = sizeof(Small) == sizeof(Check(MakeScalarType())) };
};

template<class T> class IsScalar<T*>
{
public:
    enum { Result = false };
};

template<> class IsScalar<NsFloat32>
{
public:
    enum { Result = false };
};

template<> class IsScalar<NsFloat64>
{
public:
    enum { Result = false };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks if type is an enum
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsEnum
{
private:
    template<class R> static Big Check(R);
    template<class R> static Small Check(...);
    typedef typename If<IsScalar<T>::Result, T, NsInt>::Result ScalarType;

public:
    enum { Result = (sizeof(Small) == sizeof(Check<ScalarType>(0))) };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks if type is a integral type
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsIntegral
{
    template<class TT>
    struct IsIntegralTraits
    {
        enum
        {
            Result =
                IsSame<TT, bool>::Result ||
                IsSame<TT, char>::Result ||
                IsSame<TT, signed char>::Result ||
                IsSame<TT, unsigned char>::Result ||
                IsSame<TT, signed short>::Result ||
                IsSame<TT, unsigned short>::Result ||
                IsSame<TT, signed int>::Result ||
                IsSame<TT, unsigned int>::Result ||
                IsSame<TT, signed long>::Result ||
                IsSame<TT, unsigned long>::Result ||
                IsSame<TT, signed long long>::Result ||
                IsSame<TT, unsigned long long>::Result ||
                IsSame<TT, Symbol>::Result
        };
     };
     
public:
     enum { Result = IsIntegralTraits<typename UnqualifiedType<T>::Type>::Result };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks if type is a float type
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsFloat
{
    template<class TT>
    struct IsFloatTraits
    {
        enum
        {
            Result =
                IsSame<TT, float>::Result ||
                IsSame<TT, double>::Result ||
                IsSame<TT, long double>::Result
        };
    };
    
public:
    enum { Result = IsFloatTraits<typename UnqualifiedType<T>::Type>::Result };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks if type is an arithmetic type
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsArithmetic
{
public:
    enum
    {
        Result = IsIntegral<T>::Result || IsFloat<T>::Result
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks if its best to pass a type as copy or as reference
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class IsBestByCopy
{
public:
    enum
    {
        Result = 
            IsArithmetic<T>::Result || 
            IsEnum<T>::Result || 
            IsPointer<T>::Result ||
            IsFunctionPointer<T>::Result
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Calculates the type that must be used to efficiently pass T as a parameter to a function
///
/// From Modern C++ Design, by Andrei Alexandrescu
///
/// T      ParameterType
/// -----------------------------------------------
/// U      U if U is primitive; otherwise, const U&
/// U&     U&
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class Param
{
public:
    typedef typename If<IsBestByCopy<T>::Result, T, const T&>::Result Type;
};

template<class T>
class Param<T&>
{
public:
    typedef T& Type;
};

}
}


#endif
