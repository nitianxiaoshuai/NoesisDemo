////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MATH_UTILSAPI_H__
#define __MATH_UTILSAPI_H__


#include <NsCore/CompilerSettings.h>


#ifdef NS_MATH_UTILS_PRIVATE
    #define NS_MATH_UTILS_API
#else
    #ifdef NS_MATH_UTILS_EXPORTS
        #define NS_MATH_UTILS_API NS_DLL_EXPORT
    #else
        #define NS_MATH_UTILS_API NS_DLL_IMPORT
    #endif
#endif


#endif
