////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_STATICASSERT_H__
#define __CORE_STATICASSERT_H__


namespace Noesis
{
namespace Core
{

template<NsBool> struct CompileTimeChecker
{
    CompileTimeChecker(...) {}
};

template<> class CompileTimeChecker<false> {};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// NS_STATIC_ASSERT(exp,msg) generates a compile time error message if expr is not true. 
/// The param msg is used to beautify the compiler error.
/// This macro is an adaptation of the one described in Modern C++ Design: Generic Programming 
/// and Design Patterns Applied  by Andrei Alexandrescu
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_STATIC_ASSERT(expr, msg) \
    { \
        class ERROR_##msg {}; \
        (void)sizeof(Noesis::Core::CompileTimeChecker<(expr) != 0>((ERROR_##msg)ERROR_##msg())); \
    }

}
}


#endif