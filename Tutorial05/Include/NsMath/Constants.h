////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MATH_CONSTANTS_H__
#define __MATH_CONSTANTS_H__


#include <Noesis.h>
#include <NsCore/Types.h>


namespace Noesis
{
namespace Math
{

// NsFloat32 constants
//@{
const NsFloat32 Pi_f = 3.14159265358979323846264338327950288419716939937511f;
const NsFloat32 OneOverPi_f = 1 / Pi_f;
const NsFloat32 E_f = 2.71828182845904523536028747135266249775724709369996f;
const NsFloat32 TwoPi_f = 2 * Pi_f;
const NsFloat32 FourPi_f = 4 * Pi_f;
const NsFloat32 HalfPi_f = Pi_f / 2;
const NsFloat32 SqrtPi_f = 1.77245385090551602729816748334114518279754945612239f;
const NsFloat32 DegToRad_f = Pi_f / 180;
const NsFloat32 RadToDeg_f = 180 / Pi_f;
//@}

// NsFloat64 constants
//@{
const NsFloat64 Pi = 3.14159265358979323846264338327950288419716939937511;
const NsFloat64 OneOverPi = 1 / Pi;
const NsFloat64 E = 2.71828182845904523536028747135266249775724709369996;
const NsFloat64 TwoPi = 2 * Pi;
const NsFloat64 FourPi = 4 * Pi;
const NsFloat64 HalfPi = Pi / 2;
const NsFloat64 SqrtPi = 1.77245385090551602729816748334114518279754945612239;
const NsFloat64 DegToRad = Pi / 180;
const NsFloat64 RadToDeg = 180 / Pi;
//@}

template<class T> struct Constants;

template<> struct Constants<NsFloat32>
{
    static NsFloat32 Pi_() { return Pi_f; }
    static NsFloat32 OneOverPi_() { return OneOverPi_f; }
    static NsFloat32 E_() { return E_f; }
    static NsFloat32 TwoPi_() { return TwoPi_f; }
    static NsFloat32 HalfPi_() { return HalfPi_f; }
    static NsFloat32 SqrtPi_() { return SqrtPi_f; }
    static NsFloat32 DegToRad_() { return DegToRad_f; }
    static NsFloat32 RadToDeg_() { return RadToDeg_f; }
};

template<> struct Constants<NsFloat64>
{
    static NsFloat64 Pi_() { return Pi; }
    static NsFloat64 OneOverPi_() { return OneOverPi; }
    static NsFloat64 E_() { return E; }
    static NsFloat64 TwoPi_() { return TwoPi; }
    static NsFloat64 HalfPi_() { return HalfPi; }
    static NsFloat64 SqrtPi_() { return SqrtPi; }
    static NsFloat64 DegToRad_() { return DegToRad; }
    static NsFloat64 RadToDeg_() { return RadToDeg; }
};

}
}


#endif
