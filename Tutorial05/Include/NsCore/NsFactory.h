////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_NSFACTORY_H__
#define __CORE_NSFACTORY_H__


/// Forward declarations
//@{
namespace Noesis
{
namespace Core
{
class Symbol;
template<class T> class Ptr;
class BaseComponent;
}
}
//@}


template<class T>
inline Noesis::Core::Ptr<T> NsCreateComponent(Noesis::Core::Symbol classId);


#include <NsCore/NsFactory.inl>


#endif
