////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_EXCEPTIONMACROS_H__
#define __CORE_EXCEPTIONMACROS_H__


#include <Noesis.h>


/// Exception Handling Macros
#ifdef NS_EXCEPTIONS_ENABLED
    #include <NsCore/Exception.h>

    #define NS_TRY try
    #define NS_CATCH catch (Noesis::Core::Exception& exception)
    #define NS_DISCARD_CRITICAL_EXCEPTION if (exception.IsCritical()) throw
    #define NS_RETHROW NS_UNUSED(exception), throw
    #define NS_RETHROW_DESC(...) Noesis::Core::RefineNoesisError(exception, __VA_ARGS__)
    #define NS_ERROR_DESCRIPTION exception.GetDescription()
    #define NS_DISCARD_EXCEPTION NS_UNUSED(exception)
    #define NS_CLEAR_CRITICALFLAG exception.ClearCriticalFlag()
    #define NS_SHOW_ERRORDIALOG Noesis::Core::ShowExceptionInfoDialog(exception)
    #define NS_EXCEPTION_OBJECT exception

#else
    #define NS_TRY
    #define NS_CATCH NS_MSVC_WARNING_SUPPRESS(4127) if (false)
    #define NS_DISCARD_CRITICAL_EXCEPTION NS_NOOP
    #define NS_RETHROW NS_NOOP
    #define NS_RETHROW_DESC(...) NS_NOOP
    #define NS_ERROR_DESCRIPTION ""
    #define NS_DISCARD_EXCEPTION NS_NOOP
    #define NS_CLEAR_CRITICALFLAG NS_NOOP
    #define NS_SHOW_ERRORDIALOG NS_NOOP
    #define NS_EXCEPTION_OBJECT Noesis::Core::Exception()

#endif

#endif
