////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #785]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_BOXING_H__
#define __CORE_BOXING_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/PtrForward.h>
#include <NsCore/CompilerTools.h>


NS_CFORWARD(Core, Type)


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for boxed objects
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API BoxedValue: public BaseComponent
{
public:
    /// Returns the type of the boxed value
    virtual const Type* GetValueType() const = 0;

    /// Returns the address of the boxed value
    virtual const void* GetValuePtr() const = 0;

    NS_DECLARE_REFLECTION(BoxedValue, BaseComponent)
};

template<class T> class Boxed;

namespace Boxing
{

// Converts a value type to BaseComponent
template<class T> Ptr< Boxed<T> > Box(typename Param<T>::Type value);
inline Ptr< Boxed<NsString> > Box(const NsChar* text);

// Returns whether the given object can be unboxed
template<class T> NsBool CanUnbox(BaseComponent* object);

// Extracts a value type from BaseComponent
template<class T> const T& Unbox(BaseComponent* object);

}
}
}

// Inline include
#include <NsCore/Boxing.inl>


#endif
