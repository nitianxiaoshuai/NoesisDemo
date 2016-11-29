////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #816]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_METADATA_H__
#define __CORE_METADATA_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/Vector.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
class TypeClass;
class TypeMetaData;
template<class T> class Ptr;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Manages the metadata of reflection types
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API MetaData
{
public:
    /// Constructor
    MetaData();

    /// Destructor
    ~MetaData();
    
    /// Copy Constructor
    MetaData(const MetaData& metaData);
    
    /// Copy operator
    MetaData& operator=(const MetaData& metaData);

    /// Adds a metadata
    void Add(TypeMetaData* metaData);

    /// Adds or removes a metadata from the reflection type
    void Remove(TypeMetaData* metaData);

    /// Gets the number of metadatas
    inline NsSize Count() const;

    /// Gets metadata by index
    inline TypeMetaData* Get(NsSize index) const;

    /// Gets metadata by type. If there are several metadatas of the same type the first
    /// found is returned.
    /// May return null
    TypeMetaData* Find(const TypeClass* metaDataType) const;

    /// Finds metadata of type T
    template<class T> T* Find() const;

private:
    typedef NsVector<TypeMetaData*> MetaDataVector;
    MetaDataVector mMetaDatas;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

/// Inline include
#include <NsCore/MetaData.inl>


#endif
