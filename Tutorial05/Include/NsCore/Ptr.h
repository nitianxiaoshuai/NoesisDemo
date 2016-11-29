////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #629]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_PTR_H__
#define __CORE_PTR_H__


#include <NsCore/Types.h>
#include <NsCore/Functional.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Smart pointer for BaseRefCounted objects. Automatically handles their lifetime.
/// Ptr<> is const-correct in the two types of constness that can be found in a normal pointer:
///
///    * The pointer is constant (T* const): this is expressed in a Ptr with the const operator
///      applied like in other classes
///
///        const Ptr<MyInterface> obj;
///
///    * The object pointed to is constant (const T*): this is expressed in a Ptr applying the
///      const to the type T of the Ptr
///
///        Ptr<const MyConstInterface> obj
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class Ptr
{
public:
    typedef T Type;

    /// Constructs a null smart pointer
    Ptr();

    /// Constructor from pointer that increments the reference counter of the passed object
    explicit Ptr(T* ptr);

    /// Constructor from reference that does NOT increment the reference counter. This function
    /// is used for assigning from new operator: Ptr<Cube> cube = *new Cube();
    Ptr(T& ptr);

    /// Copy Constructors
    Ptr(const Ptr& ptr);
    template<class S> Ptr(const Ptr<S>& ptr);

    /// Destructor
    ~Ptr();

    /// Copy operators
    Ptr& operator=(const Ptr& ptr);
    template<class S> Ptr& operator=(const Ptr<S>& ptr);

    /// Copy from pointer that does NOT increment the reference counter. This function
    /// is used for assigning from new operator: Ptr<Cube> cube = *new Cube();
    Ptr& operator=(T& ptr);

    /// Reset to null pointer
    void Reset();

    /// Reset to pointer. Reference counter is incremented
    void Reset(T* ptr);

    /// Like Reset() but without reference decrementing
    void Destroy();

    /// Dereferencing operators
    //@{
    T* const operator->() const;
    T* const GetPtr() const;
    //@}

    /// True if holds a valid (non null) pointer
    operator NsBool() const;

    /// Comparison operators
    //@{
    template<class S> NsBool operator==(const Ptr<S>& ptr) const;
    template<class S> NsBool operator!=(const Ptr<S>& ptr) const;
    template<class S> NsBool operator<(const Ptr<S>& ptr) const;
    
    template<class S> NsBool operator==(S* ptr) const;
    template<class S> NsBool operator!=(S* ptr) const;
    template<class S> NsBool operator<(S* ptr) const;
    //@}
    
    /// Null reference to Ptr<T>. Useful for functions that return const Ptr<T>& and may return 0
    static const Ptr<T>& Null();

private:
    T* mPtr;
};

}

/// Ptr is used frequently, so we don't want to write Core::Ptr every time
using Core::Ptr;

}

#ifndef SWIG

////////////////////////////////////////////////////////////////////////////////////////////////////
// Hash function
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace eastl
{
template<class T> struct hash<Noesis::Core::Ptr<T> >
{
    size_t operator()(const Noesis::Core::Ptr<T>& s) const
    {
        return size_t(NsUIntPtr(s.GetPtr()));
    }
};
}

#endif // SWIG

#include <NsCore/Ptr.inl>


#endif
