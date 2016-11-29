////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #696]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>
#include <NsCore/LoggerMacros.h>

namespace Noesis
{
namespace Core
{

const NsInt32 ObjectAlreadyDeleted = -202443794; // 0xF3EEF3EE

////////////////////////////////////////////////////////////////////////////////////////////////////
BaseRefCounted::BaseRefCounted()
{
    mRefCount = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BaseRefCounted::~BaseRefCounted()
{
    NS_ASSERT(mRefCount != ObjectAlreadyDeleted, "Destroy an already destroyed object");
    // mRefCount == 1 is a valid number. Even if we force to always use Ptr<>, for example, if
    // the constructor BaseRefCounted() is successfully invoked but the constructor of an
    // inheriting class raise an exception, ~BaseRefCounted() will be invoked with 1 references
    NS_ASSERT(mRefCount == 1 || mRefCount == 0, "Object deleted with %d references", 
        static_cast<NsInt32>(mRefCount));

#if NS_ASSERTS_ENABLED
    mRefCount = ObjectAlreadyDeleted;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsInt32 BaseRefCounted::AddReference() const
{
    return InternalAddReference();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsInt32 BaseRefCounted::Release() const
{
    return InternalRelease();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsInt32 BaseRefCounted::ReleaseNoDestroy() const
{
    return --mRefCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsInt32 BaseRefCounted::GetNumReferences() const
{
    return InternalGetNumReferences();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
BaseObject* BaseRefCounted::GetBaseObject() const
{
    return (BaseObject*)this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsInt32 BaseRefCounted::OnDestroy() const
{
#ifdef NS_TRACK_COMPONENTS
    TrackObjectDealloc(GetClassType()->GetName());
#endif
    NS_ASSERT(mRefCount != ObjectAlreadyDeleted, "OnDestroy() on object already destroyed");
    delete this;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsInt32 BaseRefCounted::InternalAddReference() const
{
    NS_ASSERT(mRefCount != ObjectAlreadyDeleted, "AddReference() on object already destroyed");
    return ++mRefCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsInt32 BaseRefCounted::InternalRelease() const
{
    NS_ASSERT(mRefCount > 0, "Object released without references");
    
    NsInt32 ref = --mRefCount;

    if (ref == 0)
    {
        return OnDestroy();
    }

    return ref;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsInt32 BaseRefCounted::InternalGetNumReferences() const
{
    return mRefCount;
}

}
}
