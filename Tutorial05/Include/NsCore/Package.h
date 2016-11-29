////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_PACKAGE_H__
#define __CORE_PACKAGE_H__


#include <NsCore/RegisterComponent.h>


#ifdef NS_COMPILER_MSVC
#pragma warning(disable: 4100)
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_REGISTER_REFLECTION(module, package) \
    void NsRegisterReflection##module##package( \
    Noesis::Core::ComponentFactory* factory, NsBool registerComponents) \

////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_REGISTER_COMPONENT(componentClass) \
    { \
        const Noesis::Core::TypeClass* type = Noesis::Core::TypeOf<componentClass>(); \
        if (registerComponents) \
        { \
            Noesis::Core::RegisterComponent(type, NsComponentCreator<componentClass>); \
        } \
        else \
        { \
            Noesis::Core::UnregisterComponent(type); \
        } \
    }

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NS_TESTS_ENABLED
    #define NS_REGISTER_TEST(testClass) NS_REGISTER_COMPONENT(testClass)
#else
    #define NS_REGISTER_TEST(testClass)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_INIT_PACKAGE(module, package) \
    void NsInitPackage##module##package()

////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_SHUTDOWN_PACKAGE(module, package) \
    void NsShutdownPackage##module##package()

#endif
