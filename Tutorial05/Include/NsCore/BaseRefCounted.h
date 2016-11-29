////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #696]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_BASEREFCOUNTED_H__
#define __CORE_BASEREFCOUNTED_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/BaseObject.h>
#include <NsCore/Atomic.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Core
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for types that control its lifetime with a reference counter. Instances of this class 
/// are usually stored inside a Ptr smart pointer. See Ptr class for more information.
///
/// The reference counter is initialized to 1. This means that the initial creation of the instance
/// counts as a reference. 
///
/// The management of the references is transparent if you use the kernel factory + Ptr, but if you
/// use a BaseRefCounted outside a Ptr, you need to manually release the pointer with Release().
/// Do not delete BaseRefCounted object with the operator delete because additional references 
/// to the instance may still be alive.
///
/// Example:
///     Mesh* mesh = new StaticMesh();
///     // ...
///     mesh->Release();
///     // delete mesh;     // Don't do this!
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API BaseRefCounted: public BaseObject
{
public:
    /// Default constructor.
    inline BaseRefCounted();

    /// Increments reference count
    /// \returns Number of references after incrementing one
    /// \remarks Thread-safe
    inline NsInt32 AddReference() const;

    /// Decrements reference count, deleting the object when reaches 0
    /// \returns Number of references after releasing one
    /// \remarks Thread-safe
    inline NsInt32 Release() const;

    /// Special version of Release() that never invokes the destructor. Only useful in very specific
    /// scenarios. Not used in a normal scenario
    inline NsInt32 ReleaseNoDestroy() const;

    /// Gets current reference count for the object
    /// \return the reference counter
    /// \remarks Thread-safe
    inline NsInt32 GetNumReferences() const;

    /// From BaseObject
    //@{
    const TypeClass* GetClassType() const;
    inline BaseObject* GetBaseObject() const;
    //@}

protected:
    /// Destructor. Base classes are abstract classes. Destructor is pure virtual. This destructor
    /// is declared protected to avoid deleting reference counted objects. Release() should be used
    inline virtual ~BaseRefCounted() = 0;
    
    /// This function is called when the reference counter reaches 0. By default, the destructor
    /// is invoked and the instance is really destroyed but being a virtual function a child class 
    /// can reimplement this function and avoid the destruction
    /// \return the reference counter (0 if the object was destroyed)
    inline virtual NsInt32 OnDestroy() const;

    /// Implementation of reference counting functions
    //@{
    inline virtual NsInt32 InternalAddReference() const;
    inline virtual NsInt32 InternalRelease() const;
    inline NsInt32 InternalGetNumReferences() const;
    //@}

private:
    /// Base classes are non-copyable objects
    //@{
    BaseRefCounted(const BaseRefCounted&);
    BaseRefCounted& operator=(const BaseRefCounted&);
    //@}

private:
    mutable Atomic<NsInt32> mRefCount;

    NS_DECLARE_STATIC_REFLECTION(BaseRefCounted, BaseObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

/// Inline include
#include <NsCore/BaseRefCounted.inl>


#endif
