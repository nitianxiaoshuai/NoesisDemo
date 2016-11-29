////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPEENUMHELPER_H__
#define __CORE_TYPEENUMHELPER_H__


#include <Noesis.h>
#include <NsCore/TypeCreate.h>
#include <NsCore/TypeEnumCreator.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
class TypeEnum;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper structure to create and get reflection type for enums.
/// \remarks Enum type must be register using NS_REGISTER_ENUM(enumType) before calling
/// TypeEnumHelper<enumType>::GetType().
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class TypeEnumHelper
{
public:
    static const TypeEnum* GetType()
    {
        static const TypeEnum* sType;
        
        if (sType == 0)
        {
            sType = static_cast<const TypeEnum*>(TypeCreate::Create(
                NS_TYPEID(T), TypeEnumCreator<T>::Create, TypeEnumCreator<T>::Fill));
        }
        
        return sType;
    }
};

}
}


#endif
