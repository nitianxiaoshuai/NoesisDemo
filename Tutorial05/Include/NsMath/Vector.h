////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MATH_VECTOR_H__
#define __MATH_VECTOR_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsMath/VectorMathApi.h>
#include <NsCore/Error.h>
#include <NsCore/NSTLForwards.h>

#include <limits>


namespace Noesis
{

// Forward declarations
//@{
namespace Math
{
template<class T> inline const NsChar* IdOf();
}
//@}

namespace Math
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// 2D Vector
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct Vector2
{
    T x;
    T y; 

    /// Default constructor. Does no initialization
    inline Vector2()
    {
#ifdef NS_DEBUG_CFG
        x = std::numeric_limits<T>::signaling_NaN();
        y = std::numeric_limits<T>::signaling_NaN();
#endif
    }

    /// Copy constructor
    inline Vector2(const Vector2& v): x(v.x), y(v.y) {}
    template<class S> inline Vector2(const Vector2<S>& v): x(v.x), y(v.y) {}

    /// Constructor from 2 floats
    inline Vector2(T xx, T yy): x(xx), y(yy) {}

    /// Constructor from pointer
    inline Vector2(const T* values)
    {
        NS_ASSERT(values != 0);
        
        x = values[0];
        y = values[1];
    }

    /// Assignment
    inline Vector2& operator=(const Vector2& v)
    {
        x = v.x;
        y = v.y;
        
        return *this;
    }
    template<class S> inline Vector2& operator=(const Vector2<S>& v)
    {
        x = v.x;
        y = v.y;
        
        return *this;
    }

    /// Accessors
    //@{
    inline T& operator[](NsSize i)
    {
        NS_ASSERT(i < 2);
        return (&x)[i];
    }
    inline const T operator[](NsSize i) const
    {
        NS_ASSERT(i < 2);
        return (&x)[i];
    }
    inline const T* GetData() const
    {
        return &x;
    }
    //@}

    /// In-Place operators
    //@{
    inline Vector2& operator+=(const Vector2& v)
    {
        x += v.x;
        y += v.y;
        
        return *this;
    }
    inline Vector2& operator-=(const Vector2& v)
    {
        x -= v.x;
        y -= v.y;
        
        return *this;
    }
    inline Vector2& operator*=(T v)
    {
        x *= v;
        y *= v;
        
        return *this;
    }

    inline Vector2& operator/=(T v)
    {
        x /= v;
        y /= v;
        
        return *this;
    }
    //@}

    /// Logic operators
    //@{
    inline NsBool operator==(const Vector2& v) const
    {
        return x == v.x && y == v.y;
    }
    inline NsBool operator!=(const Vector2& v) const
    {
        return !(operator==(v));
    }

    //@}

    /// Static functions
    //@{
    static inline Vector2 Zero()
    {
        return Vector2<T>(T(0.0), T(0.0));
    }
    static inline Vector2 XAxis()
    {
        return Vector2<T>(T(1.0), T(0.0));
    }
    static inline Vector2 YAxis()
    {
        return Vector2<T>(T(0.0), T(1.0));
    }
    //@}

    /// Returns a string that represents the current vector
    NsString ToString() const;

    /// Returns a hash code for the current vector
    NsUInt32 GetHashCode() const;

    NS_DECLARE_REFLECTION(Vector2, Core::NoParent)
};

/// Unary operators
//@{

/// [sfernandez] The return type of Length() and SignedAngle() functions for integer
///     specializations (Vector2i, Vector3i, Vector4i) should be NsFloat32 instead of NsInt

template<class T> T Length(const Vector2<T>& v);
template<class T> T LengthSquared(const Vector2<T>& v);
template<class T> Vector2<T> Normalize(const Vector2<T>& v);

template<class T> Vector2<T> PerpendicularCCW(const Vector2<T>& v);
template<class T> Vector2<T> PerpendicularCW(const Vector2<T>& v);
template<class T> Vector2<T> Perpendicular(const Vector2<T>& v, NsBool cw);

template<class T> const Vector2<T> operator+(const Vector2<T>& v);
template<class T> const Vector2<T> operator-(const Vector2<T>& v);
//@}

/// Binary operators
//@{
template<class T> const Vector2<T> operator+(const Vector2<T>& v0, const Vector2<T>& v1);
template<class T> const Vector2<T> operator-(const Vector2<T>& v0, const Vector2<T>& v1);
template<class T> const Vector2<T> operator*(const Vector2<T>& v, T f);
template<class T> const Vector2<T> operator*(T f, const Vector2<T>& v);
template<class T> const Vector2<T> operator/(const Vector2<T>& v, T f);

template<class T> T Dot(const Vector2<T>& v0, const Vector2<T>& v1);
template<class T> T PerpDot(const Vector2<T>& v0, const Vector2<T>& v1);
template<class T> const Vector2<T> Lerp(const Vector2<T>& v0, const Vector2<T>& v1, NsFloat32 t);

/// Returns the signed angle between two vectors: the shortest angle that must be applied to v0
/// to become v1.
/// v0 * Transform2f::Rot(SignedAngle(v0, v1) = v1
template<class T> T SignedAngle(const Vector2<T>& v0, const Vector2<T>& v1);
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// 3D Vector
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct Vector3
{
    T x;
    T y;
    T z;

    /// Default constructor. Does no initialization
    inline Vector3()
    {
#ifdef NS_DEBUG_CFG
        x = std::numeric_limits<T>::signaling_NaN();
        y = std::numeric_limits<T>::signaling_NaN();
        z = std::numeric_limits<T>::signaling_NaN();
#endif
    }

    /// Copy constructor
    inline Vector3(const Vector3& v): x(v.x), y(v.y), z(v.z) {}
    template<class S> inline Vector3(const Vector3<S>& v): x(v.x), y(v.y), z(v.z) {}

    /// Constructor from 3 floats
    inline Vector3(T xx, T yy, T zz): x(xx), y(yy), z(zz) {}

    /// Constructor from pointer
    inline Vector3(const T* values)
    {
        NS_ASSERT(values != 0);
        
        x = values[0];
        y = values[1];
        z = values[2];
    }

    /// Constructor from Vector2 + float
    inline Vector3(const Vector2<T>& v, T zz): x(v.x), y(v.y), z(zz) {}

    /// Assignment
    inline Vector3& operator=(const Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        
        return *this;
    }
    template<class S> inline Vector3& operator=(const Vector3<S>& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        
        return *this;
    }

    /// Accessors
    //@{
    inline T& operator[](NsSize i)
    {
        NS_ASSERT(i < 3);
        return (&x)[i];
    }
    inline const T operator[](NsSize i) const
    {
        NS_ASSERT(i < 3);
        return (&x)[i];
    }
    inline const T* GetData() const
    {
        return &x;
    }
    inline Vector2<T> XY() const
    {
        return Vector2<T>(x, y);
    }
    inline Vector2<T> XZ() const
    {
        return Vector2<T>(x, z);
    }
    inline Vector2<T> YZ() const
    {
        return Vector2<T>(y, z);
    }
    //@}

    /// In-Place operators
    //@{
    inline Vector3& operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        
        return *this;
    }
    inline Vector3& operator-=(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        
        return *this;
    }
    inline Vector3& operator*=(T v)
    {
        x *= v;
        y *= v;
        z *= v;
        
        return *this;
    }
    inline Vector3& operator/=(T v)
    {
        x /= v;
        y /= v;
        z /= v;
        
        return *this;
    }
    //@}

    /// Logic operators
    //@{
    inline NsBool operator==(const Vector3& v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }
    inline NsBool operator!=(const Vector3& v) const
    {
        return !(operator==(v));
    }
    //@}

    /// Static functions
    //@{
    static Vector3 Zero()
    {
        return Vector3<T>(T(0.0), T(0.0), T(0.0));
    }
    static Vector3 XAxis()
    {
        return Vector3<T>(T(1.0), T(0.0), T(0.0));
    }
    static Vector3 YAxis()
    {
        return Vector3<T>(T(0.0), T(1.0), T(0.0));
    }
    static Vector3 ZAxis()
    {
        return Vector3<T>(T(0.0), T(0.0), T(1.0));
    }
    //@}

    /// Returns a string that represents the current vector
    NsString ToString() const;

    /// Returns a hash code for the current vector
    NsUInt32 GetHashCode() const;

    NS_DECLARE_REFLECTION(Vector3, Core::NoParent)
};

/// Unary operators
//@{
template<class T> T Length(const Vector3<T>& v);
template<class T> T LengthSquared(const Vector3<T>& v);
template<class T> Vector3<T> Normalize(const Vector3<T>& v);

/// Projection dividing by z component
template<class T> Vector2<T> Project(const Vector3<T>& v);

template<class T> const Vector3<T> operator+(const Vector3<T>& v);
template<class T> const Vector3<T> operator-(const Vector3<T>& v);
//@}

/// Binary operators
//@{
template<class T> const Vector3<T> operator+(const Vector3<T>& v0, const Vector3<T>& v1);
template<class T> const Vector3<T> operator-(const Vector3<T>& v0, const Vector3<T>& v1);
template<class T> const Vector3<T> operator*(const Vector3<T>& v, T f);
template<class T> const Vector3<T> operator*(T f, const Vector3<T>& v);
template<class T> const Vector3<T> operator/(const Vector3<T>& v, T f);

template<class T> T Dot(const Vector3<T>& v0, const Vector3<T>& v1);
template<class T> Vector3<T> Cross(const Vector3<T>& v0, const Vector3<T>& v1);
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// 4D Vector
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> struct Vector4
{
    T x;
    T y;
    T z;
    T w;

    /// Default constructor. Does no initialization
    inline Vector4()
    {
#ifdef NS_DEBUG_CFG
        x = std::numeric_limits<T>::signaling_NaN();
        y = std::numeric_limits<T>::signaling_NaN();
        z = std::numeric_limits<T>::signaling_NaN();
        w = std::numeric_limits<T>::signaling_NaN();
#endif
    }

    /// Copy constructor
    inline Vector4(const Vector4& v): x(v.x), y(v.y), z(v.z), w(v.w) {}
    template<class S> inline Vector4(const Vector4<S>& v): x(v.x), y(v.y), z(v.z), w(v.w) {}

    /// Constructor from 3 floats
    inline Vector4(T xx, T yy, T zz, T ww): x(xx), y(yy), z(zz), w(ww) {}

    /// Constructor from pointer
    inline Vector4(const T* values)
    {
        NS_ASSERT(values != 0);
        
        x = values[0];
        y = values[1];
        z = values[2];
        w = values[3];
    }

    /// Constructor from Vector3 + float
    inline Vector4(const Vector3<T>& v, T ww): x(v.x), y(v.y), z(v.z), w(ww) {}
    
    /// Constructor from Vector2 + float, float
    inline Vector4(const Vector2<T>& v, T zz, T ww): x(v.x), y(v.y), z(zz), w(ww) {}

    /// Assignment
    inline Vector4& operator=(const Vector4& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        
        return *this;
    }
    template<class S> inline Vector4& operator=(const Vector4<S>& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        
        return *this;
    }

    /// Accessors
    //@{
    inline T& operator[](NsSize i)
    {
        NS_ASSERT(i < 4);
        return (&x)[i];
    }
    inline const T operator[](NsSize i) const
    {
        NS_ASSERT(i < 4);
        return (&x)[i];
    }
    inline const T* GetData() const
    {
        return &x;
    }
    inline Vector2<T> XY() const
    {
        return Vector2<T>(x, y);
    }
    inline Vector2<T> XZ() const
    {
        return Vector2<T>(x, z);
    }
    inline Vector2<T> XW() const
    {
        return Vector2<T>(x, w);
    }
    inline Vector2<T> YZ() const
    {
        return Vector2<T>(y, z);
    }
    inline Vector2<T> YW() const
    {
        return Vector2<T>(y, w);
    }
    inline Vector3<T> XYZ() const
    {
        return Vector3<T>(x, y, z);
    }
    inline Vector3<T> XYW() const
    {
        return Vector3<T>(x, y, w);
    }
    //@}

    /// In-Place operators
    //@{
    inline Vector4& operator+=(const Vector4& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        
        return *this;
    }
    inline Vector4& operator-=(const Vector4& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        
        return *this;
    }
    inline Vector4& operator*=(T v)
    {
        x *= v;
        y *= v;
        z *= v;
        w *= v;
        
        return *this;
    }
    inline Vector4& operator/=(T v)
    {
        x /= v;
        y /= v;
        z /= v;
        w /= v;
        
        return *this;
    }
    //@}

    /// Logic operators
    //@{
    inline NsBool operator==(const Vector4& v) const
    {
        return x == v.x && y == v.y && z == v.z && w == v.w;
    }
    inline NsBool operator!=(const Vector4& v) const
    {
        return !(operator==(v));
    }
    //@}

    /// Static functions
    //@{
    static Vector4 Zero()
    {
        return Vector4<T>(T(0.0), T(0.0), T(0.0), T(0.0));
    }
    static Vector4 XAxis()
    {
        return Vector4<T>(T(1.0), T(0.0), T(0.0), T(0.0));
    }
    static Vector4 YAxis()
    {
        return Vector4<T>(T(0.0), T(1.0), T(0.0), T(0.0));
    }
    static Vector4 ZAxis()
    {
        return Vector4<T>(T(0.0), T(0.0), T(1.0), T(0.0));
    }
    static Vector4 WAxis()
    {
        return Vector4<T>(T(0.0), T(0.0), T(0.0), T(1.0));
    }
    //@}

    /// Returns a string that represents the current vector
    NsString ToString() const;

    /// Returns a hash code for the current vector
    NsUInt32 GetHashCode() const;

    NS_DECLARE_REFLECTION(Vector4, Core::NoParent)
};

/// Unary operators
//@{
template<class T> T Length(const Vector4<T>& v);
template<class T> T LengthSquared(const Vector4<T>& v);
template<class T> Vector4<T> Normalize(const Vector4<T>& v);

/// Homogeneous projection (divide by w component)
template<class T> Vector3<T> Project(const Vector4<T>& v);

template<class T> const Vector4<T> operator+(const Vector4<T>& v);
template<class T> const Vector4<T> operator-(const Vector4<T>& v);
//@}

/// Binary operators
//@{
template<class T> const Vector4<T> operator+(const Vector4<T>& v0, const Vector4<T>& v1);
template<class T> const Vector4<T> operator-(const Vector4<T>& v0, const Vector4<T>& v1);
template<class T> const Vector4<T> operator*(const Vector4<T>& v, T f);
template<class T> const Vector4<T> operator*(T f, const Vector4<T>& v);
template<class T> const Vector4<T> operator/(const Vector4<T>& v, T f);

template<class T> T Dot(const Vector4<T>& v0, const Vector4<T>& v1);
//@}

typedef Vector2<NsFloat32> Vector2f;
typedef Vector2<NsInt> Vector2i;
typedef Vector3<NsFloat32> Vector3f;
typedef Vector4<NsFloat32> Vector4f;

template<> inline const NsChar* IdOf<Vector2f>() { return "Vector2f"; }
template<> inline const NsChar* IdOf<Vector2i>() { return "Vector2i"; }
template<> inline const NsChar* IdOf<Vector3f>() { return "Vector3f"; }
template<> inline const NsChar* IdOf<Vector4f>() { return "Vector4f"; }


#define NS_TEMPLATE extern template NS_MATH_VECTORMATH_API

NS_TEMPLATE NsString Vector2f::ToString() const;
NS_TEMPLATE NsString Vector2i::ToString() const;
NS_TEMPLATE NsString Vector3f::ToString() const;
NS_TEMPLATE NsString Vector4f::ToString() const;

NS_TEMPLATE NsUInt32 Vector2f::GetHashCode() const;
NS_TEMPLATE NsUInt32 Vector2i::GetHashCode() const;
NS_TEMPLATE NsUInt32 Vector3f::GetHashCode() const;
NS_TEMPLATE NsUInt32 Vector4f::GetHashCode() const;

NS_TEMPLATE const Core::TypeClass* Vector2f::StaticGetClassType(Core::T2T<Vector2f>*);
NS_TEMPLATE const Core::TypeClass* Vector2i::StaticGetClassType(Core::T2T<Vector2i>*);
NS_TEMPLATE const Core::TypeClass* Vector3f::StaticGetClassType(Core::T2T<Vector3f>*);
NS_TEMPLATE const Core::TypeClass* Vector4f::StaticGetClassType(Core::T2T<Vector4f>*);

#undef NS_TEMPLATE


}
}

// Inline include
#include <NsMath/Vector.inl>

#endif
