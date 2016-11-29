////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_TEXTUREPROVIDERAPI_H__
#define __DRAWING_TEXTUREPROVIDERAPI_H__


#include <NsCore/CompilerSettings.h>


#ifdef NS_DRAWING_TEXTUREPROVIDER_PRIVATE
    #define NS_DRAWING_TEXTUREPROVIDER_API
#else
    #ifdef NS_DRAWING_TEXTUREPROVIDER_EXPORTS
        #define NS_DRAWING_TEXTUREPROVIDER_API NS_DLL_EXPORT
    #else
        #define NS_DRAWING_TEXTUREPROVIDER_API NS_DLL_IMPORT
    #endif
#endif


#endif
