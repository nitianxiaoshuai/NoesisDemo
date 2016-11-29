////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEINFO_H__
#define __CORE_TYPEINFO_H__


#include <Noesis.h>


#if defined(NS_COMPILER_GCC)

    #include <NsCore/KernelApi.h>
    extern NS_CORE_KERNEL_API const NsSize NsPrettyFunctionOffset;
    
    // Do not use NsChar here because the output of __PRETTY_FUNCTION__ varies dependening of
    // the namespace who calls NsTypeName()
    template<class T> const char* NsTypeName(T* = 0)
    {
        return __PRETTY_FUNCTION__ + NsPrettyFunctionOffset;
    }

#else

    #include <typeinfo.h>

    template<class T> const char* NsTypeName()
    {
        // raw_name() better than name() because it is smaller and we are going to use it to compare
        return typeid(T).raw_name();
    }

#endif

#define NS_TYPEID(T) Noesis::Core::TypeInfo(static_cast<const NsChar*>(NsTypeName<T>()))

namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeInfo, offers a first-class, comparable wrapper for types created with NS_TYPEID
////////////////////////////////////////////////////////////////////////////////////////////////////
class TypeInfo
{
public:
    inline TypeInfo();
    inline TypeInfo(const NsChar* id);

    inline NsBool operator==(const TypeInfo& typeInfo) const;
    inline NsBool operator!=(const TypeInfo& typeInfo) const;

    inline NsBool operator<(const TypeInfo& typeInfo) const;
    inline NsBool operator<=(const TypeInfo& typeInfo) const;
    inline NsBool operator>(const TypeInfo& typeInfo) const;
    inline NsBool operator>=(const TypeInfo& typeInfo) const;

    inline const NsChar* GetId() const;

private:
    TypeInfo& operator=(const TypeInfo&);

private:
    const NsChar* const mId;
};

}
}

// Inline include
#include <NsCore/TypeInfo.inl>

#endif
