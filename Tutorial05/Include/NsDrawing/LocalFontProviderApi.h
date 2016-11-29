////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_LOCALFONTPROVIDERAPI_H__
#define __DRAWING_LOCALFONTPROVIDERAPI_H__


#include <NsCore/CompilerSettings.h>


#ifdef NS_DRAWING_LOCALFONTPROVIDER_PRIVATE
    #define NS_DRAWING_LOCALFONTPROVIDER_API
#else
    #ifdef NS_DRAWING_LOCALFONTPROVIDER_EXPORTS
        #define NS_DRAWING_LOCALFONTPROVIDER_API NS_DLL_EXPORT
    #else
        #define NS_DRAWING_LOCALFONTPROVIDER_API NS_DLL_IMPORT
    #endif
#endif


#endif
