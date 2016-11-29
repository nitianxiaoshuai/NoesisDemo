////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_DELEGATE_H__
#define __CORE_DELEGATE_H__


#include <Noesis.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/Interface.h>

namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A callable entity with T signature. Similar to C# delegates
//
///    Delegate<void (NsSize&, NsFloat32)> delegate;
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class Delegate;

}
}

// Generator for 0 params
#define NS_DELEGATE_COMMA
#define NS_DELEGATE_TEMPLATE_PARAMS
#define NS_DELEGATE_PARAMS
#define NS_DELEGATE_PARAMS_NONAME
#define NS_DELEGATE_PARAM_TYPES
#define NS_DELEGATE_PARAM_NAMES
#include <NsCore/DelegateGenerator.h>
#undef NS_DELEGATE_PARAM_NAMES
#undef NS_DELEGATE_PARAM_TYPES
#undef NS_DELEGATE_PARAMS
#undef NS_DELEGATE_PARAMS_NONAME
#undef NS_DELEGATE_TEMPLATE_PARAMS
#undef NS_DELEGATE_COMMA

// Generator for 1 params
#define NS_DELEGATE_COMMA ,
#define NS_DELEGATE_TEMPLATE_PARAMS class T0
#define NS_DELEGATE_PARAMS typename Param<T0>::Type t0
#define NS_DELEGATE_PARAMS_NONAME typename Param<T0>::Type
#define NS_DELEGATE_PARAM_TYPES T0
#define NS_DELEGATE_PARAM_NAMES t0
#include <NsCore/DelegateGenerator.h>
#undef NS_DELEGATE_PARAM_NAMES
#undef NS_DELEGATE_PARAM_TYPES
#undef NS_DELEGATE_PARAMS
#undef NS_DELEGATE_PARAMS_NONAME
#undef NS_DELEGATE_TEMPLATE_PARAMS
#undef NS_DELEGATE_COMMA

// Generator for 2 params
#define NS_DELEGATE_COMMA ,
#define NS_DELEGATE_TEMPLATE_PARAMS class T0, class T1
#define NS_DELEGATE_PARAMS typename Param<T0>::Type t0,\
    typename Param<T1>::Type t1
#define NS_DELEGATE_PARAMS_NONAME typename Param<T0>::Type,\
    typename Param<T1>::Type
#define NS_DELEGATE_PARAM_TYPES T0, T1
#define NS_DELEGATE_PARAM_NAMES t0, t1
#include <NsCore/DelegateGenerator.h>
#undef NS_DELEGATE_PARAM_NAMES
#undef NS_DELEGATE_PARAM_TYPES
#undef NS_DELEGATE_PARAMS
#undef NS_DELEGATE_PARAMS_NONAME
#undef NS_DELEGATE_TEMPLATE_PARAMS
#undef NS_DELEGATE_COMMA

// Generator for 3 params
#define NS_DELEGATE_COMMA ,
#define NS_DELEGATE_TEMPLATE_PARAMS class T0, class T1, class T2
#define NS_DELEGATE_PARAMS typename Param<T0>::Type t0,\
    typename Param<T1>::Type t1, typename Param<T2>::Type t2
#define NS_DELEGATE_PARAMS_NONAME typename Param<T0>::Type,\
    typename Param<T1>::Type, typename Param<T2>::Type
#define NS_DELEGATE_PARAM_TYPES T0, T1, T2
#define NS_DELEGATE_PARAM_NAMES t0, t1, t2
#include <NsCore/DelegateGenerator.h>
#undef NS_DELEGATE_PARAM_NAMES
#undef NS_DELEGATE_PARAM_TYPES
#undef NS_DELEGATE_PARAMS
#undef NS_DELEGATE_PARAMS_NONAME
#undef NS_DELEGATE_TEMPLATE_PARAMS
#undef NS_DELEGATE_COMMA

// Generator for 4 params
#define NS_DELEGATE_COMMA ,
#define NS_DELEGATE_TEMPLATE_PARAMS class T0, class T1, class T2, class T3
#define NS_DELEGATE_PARAMS typename Param<T0>::Type t0,\
    typename Param<T1>::Type t1, typename Param<T2>::Type t2,\
    typename Param<T3>::Type t3
#define NS_DELEGATE_PARAMS_NONAME typename Param<T0>::Type,\
    typename Param<T1>::Type, typename Param<T2>::Type,\
    typename Param<T3>::Type
#define NS_DELEGATE_PARAM_TYPES T0, T1, T2, T3
#define NS_DELEGATE_PARAM_NAMES t0, t1, t2, t3
#include <NsCore/DelegateGenerator.h>
#undef NS_DELEGATE_PARAM_NAMES
#undef NS_DELEGATE_PARAM_TYPES
#undef NS_DELEGATE_PARAMS
#undef NS_DELEGATE_PARAMS_NONAME
#undef NS_DELEGATE_TEMPLATE_PARAMS
#undef NS_DELEGATE_COMMA

// Generator for 5 params
#define NS_DELEGATE_COMMA ,
#define NS_DELEGATE_TEMPLATE_PARAMS class T0, class T1, class T2, class T3, class T4
#define NS_DELEGATE_PARAMS typename Param<T0>::Type t0,\
    typename Param<T1>::Type t1, typename Param<T2>::Type t2,\
    typename Param<T3>::Type t3, typename Param<T4>::Type t4
#define NS_DELEGATE_PARAMS_NONAME typename Param<T0>::Type,\
    typename Param<T1>::Type, typename Param<T2>::Type,\
    typename Param<T3>::Type, typename Param<T4>::Type
#define NS_DELEGATE_PARAM_TYPES T0, T1, T2, T3, T4
#define NS_DELEGATE_PARAM_NAMES t0, t1, t2, t3, t4
#include <NsCore/DelegateGenerator.h>
#undef NS_DELEGATE_PARAM_NAMES
#undef NS_DELEGATE_PARAM_TYPES
#undef NS_DELEGATE_PARAMS
#undef NS_DELEGATE_PARAMS_NONAME
#undef NS_DELEGATE_TEMPLATE_PARAMS
#undef NS_DELEGATE_COMMA

// Generator for 6 params
#define NS_DELEGATE_COMMA ,
#define NS_DELEGATE_TEMPLATE_PARAMS class T0, class T1, class T2, class T3, class T4, class T5
#define NS_DELEGATE_PARAMS typename Param<T0>::Type t0,\
    typename Param<T1>::Type t1, typename Param<T2>::Type t2,\
    typename Param<T3>::Type t3, typename Param<T4>::Type t4,\
    typename Param<T5>::Type t5
#define NS_DELEGATE_PARAMS_NONAME typename Param<T0>::Type,\
    typename Param<T1>::Type, typename Param<T2>::Type,\
    typename Param<T3>::Type, typename Param<T4>::Type,\
    typename Param<T5>::Type
#define NS_DELEGATE_PARAM_TYPES T0, T1, T2, T3, T4, T5
#define NS_DELEGATE_PARAM_NAMES t0, t1, t2, t3, t4, t5
#include <NsCore/DelegateGenerator.h>
#undef NS_DELEGATE_PARAM_NAMES
#undef NS_DELEGATE_PARAM_TYPES
#undef NS_DELEGATE_PARAMS
#undef NS_DELEGATE_PARAMS_NONAME
#undef NS_DELEGATE_TEMPLATE_PARAMS
#undef NS_DELEGATE_COMMA

// Generator for 7 params
#define NS_DELEGATE_COMMA ,
#define NS_DELEGATE_TEMPLATE_PARAMS class T0, class T1, class T2, class T3, class T4, class T5, \
    class T6
#define NS_DELEGATE_PARAMS typename Param<T0>::Type t0,\
    typename Param<T1>::Type t1, typename Param<T2>::Type t2,\
    typename Param<T3>::Type t3, typename Param<T4>::Type t4,\
    typename Param<T5>::Type t5, typename Param<T6>::Type t6
#define NS_DELEGATE_PARAMS_NONAME typename Param<T0>::Type,\
    typename Param<T1>::Type, typename Param<T2>::Type,\
    typename Param<T3>::Type, typename Param<T4>::Type,\
    typename Param<T5>::Type, typename Param<T6>::Type
#define NS_DELEGATE_PARAM_TYPES T0, T1, T2, T3, T4, T5, T6
#define NS_DELEGATE_PARAM_NAMES t0, t1, t2, t3, t4, t5, t6
#include <NsCore/DelegateGenerator.h>
#undef NS_DELEGATE_PARAM_NAMES
#undef NS_DELEGATE_PARAM_TYPES
#undef NS_DELEGATE_PARAMS
#undef NS_DELEGATE_PARAMS_NONAME
#undef NS_DELEGATE_TEMPLATE_PARAMS
#undef NS_DELEGATE_COMMA

#endif
