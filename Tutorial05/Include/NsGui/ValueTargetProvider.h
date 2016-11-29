////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VALUETARGETPROVIDER_H__
#define __GUI_VALUETARGETPROVIDER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyProperty;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ValueTargetProvider
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ValueTargetProvider
{
public:
    ValueTargetProvider(Core::BaseComponent* targetObject,
        const DependencyProperty* targetProperty);

    Core::BaseComponent* GetTargetObject() const;
    const DependencyProperty* GetTargetProperty() const;

private:
    Ptr<Core::BaseComponent> mTargetObject;
    const DependencyProperty* mTargetProperty;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
