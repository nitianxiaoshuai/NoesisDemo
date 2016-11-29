////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MATH_VECTORFORWARD_H__
#define __MATH_VECTORFORWARD_H__


#include <NsCore/Types.h>


namespace Noesis
{
namespace Math
{

template<class T> struct Vector2;
template<class T> struct Vector3;
template<class T> struct Vector4;

typedef Vector2<NsInt> Vector2i;
typedef Vector2<NsFloat32> Vector2f;
typedef Vector3<NsFloat32> Vector3f;
typedef Vector4<NsFloat32> Vector4f;

}
}


#endif
