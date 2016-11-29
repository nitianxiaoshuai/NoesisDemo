////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_COLOR_H__
#define __DRAWING_COLOR_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/NSTLForwards.h>
#include <NsDrawing/TypesApi.h>


namespace Noesis
{

namespace Drawing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// RGBA color in the sRGB (http://en.wikipedia.org/wiki/SRGB) space. Components are interpreted
/// in the 0.0 - 1.0 range as floats or in the range 0 - 255 as integers. An alpha value of 1.0 or
/// 255 represents an opaque color and an alpha value of 0.0 or 0 means that the color is fully 
/// transparent.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_DRAWING_TYPES_API Color
{
public:
    /// Default constructor that creates a black color
    inline Color();
    
    // Constructor from float components (0.0 - 1.0)
    inline Color(NsFloat32 r, NsFloat32 g, NsFloat32 b, NsFloat32 a = 1.0f);
    
    // Constructor from integer components (0 - 255)
    inline Color(NsInt r, NsInt g, NsInt b, NsInt a = 255);

    // Creates a color from an integer representation as obtained from GetPackedColorBGRA
    static Color FromPackedBGRA(NsUInt32 color);
    
    // Creates a color from an integer representation as obtained from GetPackedColorRGBA
    static Color FromPackedRGBA(NsUInt32 color);

    // Creates a sRGB color from components given in linear RGB space
    static Color FromLinearRGB(NsFloat32 r, NsFloat32 g, NsFloat32 b, NsFloat32 a = 1.0f);
    static Color FromLinearRGB(NsInt r, NsInt g, NsInt b,  NsInt a = 255);

    // Returns the components of the color in linear RGB space
    void ToLinearRGB(NsFloat32& r, NsFloat32& g, NsFloat32& b, NsFloat32& a) const;
    void ToLinearRGB(NsInt& r, NsInt& g, NsInt& b, NsInt& a) const;
    
    // Setters
    //@{
    inline void SetRed(NsFloat32 red);
    inline void SetRed(NsInt red);
    inline void SetGreen(NsFloat32 green);
    inline void SetGreen(NsInt green);
    inline void SetBlue(NsFloat32 blue);
    inline void SetBlue(NsInt blue);
    inline void SetAlpha(NsFloat32 alpha);
    inline void SetAlpha(NsInt alpha);
    inline void SetPackedColorBGRA(NsUInt32 color);
    inline void SetPackedColorRGBA(NsUInt32 color);
    //@}

    // Getters
    //@{
    inline NsInt GetRedI() const;
    inline NsInt GetGreenI() const;
    inline NsInt GetBlueI() const;
    inline NsInt GetAlphaI() const;
    inline NsFloat32 GetRedF() const;
    inline NsFloat32 GetGreenF() const;
    inline NsFloat32 GetBlueF() const;
    inline NsFloat32 GetAlphaF() const;
    inline NsUInt32 GetPackedColorBGRA() const;
    inline NsUInt32 GetPackedColorRGBA() const;
    //@}
    
    /// Logic operators
    //@{
    inline NsBool operator==(const Color& color) const;
    inline NsBool operator!=(const Color& color) const;
    //@}
    
    /// Generates a string representation in the form #AARRGGBB
    NsString ToString() const;

    /// Returns a hash code
    NsUInt32 GetHashCode() const;

    /// Creates a color from a string. Valid formats are:
    ///  - #AARRGGBB 
    ///  - #RRGGBB
    ///  - #ARGB | 
    ///  - A predefined color from the list defined in 
    ///     http://msdn.microsoft.com/en-us/library/system.windows.media.colors.aspx
    //@{
    static NsBool TryParse(const NsChar* str, Color& output);
    static Color Parse(const NsChar* str);
    //@}

    /// Constant Colors
    //@{
    static const Color Black;
    static const Color Blue;
    static const Color Cyan;
    static const Color DarkGray;
    static const Color Gray;
    static const Color Green;
    static const Color LightGray;
    static const Color Magenta;
    static const Color Orange;
    static const Color Pink;
    static const Color Red;
    static const Color White;
    static const Color Yellow;
    //@}
    
private:
    NsFloat32 mColor[4];

    NS_DECLARE_REFLECTION(Color, Core::NoParent)
};

/// Returns the Premultiplied alpha representation of the given color
/// The Premultiplied alpha representation of RGBA is (RA, GA, BA, A)
/// Setting sRGB to false performs the premultiplication in linear space
NS_DRAWING_TYPES_API Color PreMultiplyAlpha(const Color& color, NsBool sRGB = true);

/// Returns a linear interpolation between two colours
/// Setting sRGB to false perfoms the interpolation in linear space
NS_DRAWING_TYPES_API Color Lerp(const Color& c0, const Color& c1, NsFloat32 t, NsBool sRGB = true);

/// Add two colours
/// Setting sRGB to false perfoms the operation in linear space
NS_DRAWING_TYPES_API Color Add(const Color& c0, const Color& c1, NsBool sRGB = true);

/// Returns the multiplication of two given colors
NS_DRAWING_TYPES_API Color Modulate(const Color& c0, const Color& c1);

}
}

// Inline include
#include <NsDrawing/Color.inl>


#endif
