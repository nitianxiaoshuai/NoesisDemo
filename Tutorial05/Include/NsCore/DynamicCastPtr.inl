////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #620]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/DynamicCastPointer.h>
#include <NsCore/Ptr.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/StaticAssert.h>


namespace Noesis
{
namespace Core
{
namespace Reflection
{

typedef Noesis::Core::Int2Type<0> IsNotPtr_;
typedef Noesis::Core::Int2Type<1> IsPtr_;

template<class CastT, class SourceT>
CastT InternalDynamicCast(const Noesis::Core::Ptr<SourceT>& ptr, IsNotPtr_)
{
    // Cast from Ptr<> to * is not allowed
    NS_STATIC_ASSERT(false, PTR_CAN_ONLY_BE_CASTED_TO_PTR_);
}

template<class CastT, class SourceT>
CastT InternalDynamicCast(const Noesis::Core::Ptr<SourceT>& ptr, IsPtr_)
{
    return CastT(NsDynamicCast<typename CastT::Type*>(ptr.GetPtr()));
}

template<class CastT, class SourceT>
CastT InternalStaticCast(const Noesis::Core::Ptr<SourceT>& ptr, IsNotPtr_)
{
    // Cast from Ptr<> to * is not allowed
    NS_STATIC_ASSERT(false, PTR_CAN_ONLY_BE_CASTED_TO_PTR_);
}

template<class CastT, class SourceT>
CastT InternalStaticCast(const Noesis::Core::Ptr<SourceT>& ptr, IsPtr_)
{
    return CastT(NsStaticCast<typename CastT::Type*>(ptr.GetPtr()));
}

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CastT, class SourceT>
CastT NsDynamicCast(const Noesis::Core::Ptr<SourceT>& ptr)
{
    return Noesis::Core::Reflection::InternalDynamicCast<CastT>(ptr,
        Noesis::Core::Int2Type<Noesis::Core::IsPtr<CastT>::Result>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CastT, class SourceT>
CastT NsStaticCast(const Noesis::Core::Ptr<SourceT>& ptr)
{
    return Noesis::Core::Reflection::InternalStaticCast<CastT>(ptr,
        Noesis::Core::Int2Type<Noesis::Core::IsPtr<CastT>::Result>());
}
//@}
