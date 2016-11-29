////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1209]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_PROFILER_H__
#define __CORE_PROFILER_H__


#include <Noesis.h>
#include <NsCore/Symbol.h>
#include <NsCore/ScopeGuard.h>
#include <NsCore/Vector.h>
#include <NsCore/NSTLMemoryAllocator.h>
#include <NsCore/Error.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A templated base class for creating nodes with profiling information.
/// See MemProfiler for an example
/// As this is an exported template, functions are inlined inside the body of the class
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class ProfilerNode
{
public:
    explicit ProfilerNode(NsSymbol sym = NsSymbol::Null(), MemoryAllocator* allocator = 0):
        mSym(sym), mChildren(allocator), mSymbols(allocator)
    {
    }
    
    ~ProfilerNode()
    {
        MemoryAllocator* allocator = mChildren.get_allocator().allocator;
        
        for (NsSize i = 0; i < mChildren.size(); i++)
        {
            mChildren[i]->~T();
            allocator->Dealloc(mChildren[i]);
        }
    }
    
    /// Changes the id
    void SetId(NsSymbol id)
    {
        mSym = id;
    }

    /// \return the symbol associated this node
    NsSymbol GetId() const
    {
        return mSym;
    }

    /// If the child doesn't exist a new one is created and returned, otherwise a reference to the
    /// existing child is returned
    T& AddChild(NsSymbol id) throw()
    {
#if NS_INSTRUMENTED_ENABLED
        // AddChild() function is always called from the same thread. And this is the unique function
        // that needs writing. Thanks to that this search can be done without taking the mutex
        NsSize numChildren = mSymbols.size();
        
        if (numChildren > 0)
        {
            NsSymbol* sym = &mSymbols[0];
        
            for (NsSize i = 0; i < numChildren; i++)
            {
                if (*sym++ == id)
                {
                    return *(mChildren[i]);
                }
            }
        }
        
        T::AcquireMutexForAddingChild();
        NS_ON_SCOPE_EXIT(&T::ReleaseMutexForAddingChild);
        MemoryAllocator* allocator = mChildren.get_allocator().allocator;
        T* node = new (allocator->Alloc(sizeof(T))) T(id, allocator);
        mChildren.push_back(node);
        mSymbols.push_back(id);
        return *(mChildren.back());
#else
        NS_UNUSED(id);
        NS_ASSERT_UNREACHABLE;
#endif
    }

    /// Children accessor
    //@{
    NsSize GetNumChildren() const
    {
        return mChildren.size();
    }
    
    const T& GetChild(NsSize i) const
    {
        NS_ASSERT(i < mChildren.size());
        return *(mChildren[i]);
    }
    
    T& GetChild(NsSize i)
    {
        NS_ASSERT(i < mChildren.size());
        return *(mChildren[i]);
    }
    //@}

    /// Comparison operator
    NsBool operator<(const ProfilerNode& node) const
    {
        return mSym < node.mSym;
    }

private:
    ProfilerNode(ProfilerNode&);
    ProfilerNode& operator=(ProfilerNode&);

private:
    NsSymbol mSym;

    typedef NsVector<T*, nstl::MemoryAllocator> Children;
    Children mChildren;
    
    typedef NsVector<NsSymbol, nstl::MemoryAllocator> Symbols;
    Symbols mSymbols;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_INTERNAL_PROFILE(sym, nodeClass, uniqueId) \
    static NsUInt32 uniqueId; \
    if (uniqueId == 0) \
    { \
        uniqueId = NsSymbol(sym); \
    } \
    Noesis::Core::NodeEnterLeave<nodeClass> NS_UNIQUE_NAME(auto)(static_cast<NsSymbol>(uniqueId))
    
#define NS_INTERNAL_PROFILE_SYM(sym, nodeClass)\
    Noesis::Core::NodeEnterLeave<nodeClass> NS_UNIQUE_NAME(auto)(sym)


/// Update profilers and send information to console
NS_CORE_KERNEL_API void TickProfilers();

}
}

#include <NsCore/Profiler.inl>


#endif