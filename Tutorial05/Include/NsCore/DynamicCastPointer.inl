////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #620]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/StaticAssert.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/TypeClass.h>
#include <NsCore/Interface.h>


namespace Noesis
{
namespace Core
{

class BaseObject;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Auxiliary classes and functions to obtain cast pointer.
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Reflection
{

struct StaticCast
{
    template<class CastT, class SourceT>
    static CastT* Apply(SourceT* ptr)
    {
        return static_cast<CastT*>(ptr);
    }
};

typedef Int2Type<0> T_NoInterface;
typedef Int2Type<1> T_Interface;

template<class SourceT> BaseObject* GetBaseObject(SourceT* ptr, T_Interface)
{
    return (BaseObject*)(ptr == 0 ? 0 : ptr->GetBaseObject()); 
}

template<class SourceT> BaseObject* GetBaseObject(SourceT* ptr, T_NoInterface)
{
    return (BaseObject*)ptr;
}

NS_CORE_KERNEL_API void* Cast(const TypeClass* destType, BaseObject* source);

struct DynamicCast
{
    template<class CastT, class SourceT>
    static CastT* Apply(SourceT* ptr)
    {
        typedef typename IsConst<CastT>::NonConstType CastT_;
        const TypeClass* castType = CastT::StaticGetClassType((T2T<CastT_>*)0);
        BaseObject* source = GetBaseObject(ptr, Int2Type<IsInterface<SourceT>::Result>());
        return reinterpret_cast<CastT*>(Cast(castType, source));
    }
};

/// Up-casting to a derived class is optimized with a static cast
template<class CastT, class SourceT>
CastT* InternalDynamicCast(SourceT* ptr, Int2Type<0> /* CastToICommon == false */)
{
    return If<IsDerived<SourceT, CastT>::Result,
        StaticCast,
        DynamicCast>::Result::template Apply<CastT, SourceT>(ptr);
}

/// When casting to Interface dynamic cast must be done always, because static cast can generate an
/// ambiguity if class implements two or more interfaces (each interface has its own Interface)
template<class CastT, class SourceT>
CastT* InternalDynamicCast(SourceT* ptr, Int2Type<1> /* CastToICommon == true */)
{
    return DynamicCast::Apply<CastT, SourceT>(ptr);
}

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CastT, class SourceT>
CastT NsDynamicCast(SourceT ptr)
{
    typedef typename Noesis::Core::IsPointer<CastT>::PointedType CastTT;
    typedef typename Noesis::Core::IsPointer<SourceT>::PointedType SourceTT;

    NS_STATIC_ASSERT(
        !(Noesis::Core::IsConst<SourceTT>::Result && !Noesis::Core::IsConst<CastTT>::Result),
        _CANNOT_CONVERT_FROM_CONST_TO_NON_CONST_POINTER);

    enum
    {
        CastToICommon =
            Noesis::Core::IsSame<CastTT, Noesis::Core::Interface>::Result ||
            Noesis::Core::IsSame<CastTT, const Noesis::Core::Interface>::Result
    };

    return Noesis::Core::Reflection::InternalDynamicCast<CastTT, SourceTT>(ptr,
        Noesis::Core::Int2Type<CastToICommon>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CastT, class SourceT>
CastT NsStaticCast(SourceT ptr)
{
    NS_ASSERT(!ptr || NsDynamicCast<CastT>(ptr) != 0, "Invalid NsStaticCast");
    return static_cast<CastT>(ptr);
}
//@}
