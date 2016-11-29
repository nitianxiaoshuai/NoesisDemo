////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEOFBASIC_H__
#define __CORE_TYPEOFBASIC_H__


#ifndef __INCLUDED_FROM_TYPEOF_H__
    #error Do not include this file directly. Use <TypeOf.h> instead
#endif


#include <Noesis.h>
#include <NsCore/TypeOfBase.h>


namespace Noesis
{
namespace Core
{

class Symbol;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeOf specialization for basic types.
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
template<> class TypeOfHelper<void>: public TypeOfHelperBase<Type, Type, void> { };
template<> class TypeOfHelper<NsInt8>: public TypeOfHelperBase<Type, Type, NsInt8> { };
template<> class TypeOfHelper<NsInt16>: public TypeOfHelperBase<Type, Type, NsInt16> { };
template<> class TypeOfHelper<NsInt32>: public TypeOfHelperBase<Type, Type, NsInt32> { };
template<> class TypeOfHelper<NsInt64>: public TypeOfHelperBase<Type, Type, NsInt64> { };
template<> class TypeOfHelper<NsUInt8>: public TypeOfHelperBase<Type, Type, NsUInt8> { };
template<> class TypeOfHelper<NsUInt16>: public TypeOfHelperBase<Type, Type, NsUInt16> { };
template<> class TypeOfHelper<NsUInt32>: public TypeOfHelperBase<Type, Type, NsUInt32> { };
template<> class TypeOfHelper<NsUInt64>: public TypeOfHelperBase<Type, Type, NsUInt64> { };
template<> class TypeOfHelper<NsFloat32>: public TypeOfHelperBase<Type, Type, NsFloat32> { };
template<> class TypeOfHelper<NsFloat64>: public TypeOfHelperBase<Type, Type, NsFloat64> { };
template<> class TypeOfHelper<NsChar>: public TypeOfHelperBase<Type, Type, NsChar> { };
template<> class TypeOfHelper<NsBool>: public TypeOfHelperBase<Type, Type, NsBool> { };
template<> class TypeOfHelper<Symbol>: public TypeOfHelperBase<Type, Type, Symbol> { };
template<> class TypeOfHelper<NsString>: public TypeOfHelperBase<Type, Type, NsString> { };
//@}

}
}


#endif
