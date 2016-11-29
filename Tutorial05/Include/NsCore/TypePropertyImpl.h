////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #488]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEPROPERTYIMPL_H__
#define __CORE_TYPEPROPERTYIMPL_H__


#include <Noesis.h>
#include <NsCore/TypeProperty.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypePropertyOffset. Represents a property defined by an offset from the instance pointer.
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
template<class T>
class TypePropertyOffset: public TypeProperty
{
public:
    /// Constructor
    TypePropertyOffset(NsSymbol name, NsSize offset);

    /// From TypeProperty
    //@{
    void* GetContent(void* ptr) const;
    const void* GetContent(const void* ptr) const;
    Ptr<BaseComponent> GetComponent(const void* ptr) const;
    void SetComponent(void* ptr, BaseComponent* value) const;
    //@}

protected:
    /// From TypeProperty
    //@{
    const void* InternalGet(const void* ptr) const;
    void InternalGet(const void* ptr, void* storage) const;
    void InternalSet(void* ptr, const void* value) const;
    NsBool InternalIsReadOnly() const;
    //@}

private:
    typedef typename IsConst<T>::NonConstType TT;
    NsSize mOffset;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypePropertyArray. Represents a static array property in a class.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, NsSize N>
class TypePropertyArray: public TypeProperty
{
public:
    /// Constructor
    TypePropertyArray(NsSymbol name, NsSize offset);

    /// From TypeProperty
    //@{
    void* GetContent(void* ptr) const;
    const void* GetContent(const void* ptr) const;
    Ptr<BaseComponent> GetComponent(const void* ptr) const;
    void SetComponent(void* ptr, BaseComponent* value) const;
    //@}

protected:
    /// From TypeProperty
    //@{
    const void* InternalGet(const void* ptr) const;
    void InternalGet(const void* ptr, void* storage) const;
    void InternalSet(void* ptr, const void* value) const;
    NsBool InternalIsReadOnly() const;
    //@}

private:
    NsSize mOffset;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypePropertyFunction. Represents a property defined by Getter and Setter functions of a class.
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
template<class C, class T>
class TypePropertyFunction: public TypeProperty
{
private:
    struct ByRef
    {
        typedef const T& (C::*GetterFn)() const;
        typedef void (C::*SetterFn)(const T&);

        static NsBool CanGetRef();
        static NsBool CanGetCopy();

        static const void* GetRef(GetterFn getter, const void* ptr);
        static void GetCopy(GetterFn getter, const void* ptr, void* storage);
    };

    struct ByCopy
    {
        typedef T (C::*GetterFn)() const;
        typedef void (C::*SetterFn)(T);

        static NsBool CanGetRef();
        static NsBool CanGetCopy();

        static const void* GetRef(GetterFn getter, const void* ptr);
        static void GetCopy(GetterFn getter, const void* ptr, void* storage);
    };

public:
    typedef typename If<IsBestByCopy<T>::Result, ByCopy, ByRef>::Result Helper;
    typedef typename Helper::GetterFn GetterFn;
    typedef typename Helper::SetterFn SetterFn;

    /// Constructor
    TypePropertyFunction(NsSymbol name, GetterFn getter, SetterFn setter);

    /// From TypeProperty
    //@{
    void* GetContent(void* ptr) const;
    const void* GetContent(const void* ptr) const;
    Ptr<BaseComponent> GetComponent(const void* ptr) const;
    void SetComponent(void* ptr, BaseComponent* value) const;
    //@}

protected:
    /// From TypeProperty
    //@{
    const void* InternalGet(const void* ptr) const;
    void InternalGet(const void* ptr, void* storage) const;
    void InternalSet(void* ptr, const void* value) const;
    NsBool InternalIsReadOnly() const;
    //@}

private:
    GetterFn mGetter;
    SetterFn mSetter;
};

}
}

// Inline Include
#include <NsCore/TypePropertyImpl.inl>


#endif
