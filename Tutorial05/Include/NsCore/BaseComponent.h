////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_BASECOMPONENT_H__
#define __CORE_BASECOMPONENT_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/BaseRefCounted.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// BaseComponent. Base class for all components.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API BaseComponent: public BaseRefCounted
{
public:
    /// Default constructor.
    BaseComponent();

protected:
    /// Destructor. Base classes are abstract classes. Destructor is pure virtual.
    /// This destructor is declared protected to avoid deleting reference counted objects. Release()
    /// should be used in this case.
    virtual ~BaseComponent() = 0;

private:
    /// Base classes are non-copyable objects
    //@{
    BaseComponent(const BaseComponent&);
    BaseComponent& operator=(const BaseComponent&);
    //@}

    NS_DECLARE_REFLECTION(BaseComponent, BaseRefCounted)
};

}
}


#endif
