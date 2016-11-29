////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsGui/BoxingUtils.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create()
{
    return *new FrameworkPropertyMetadata();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(NsInt32 options)
{
    return *new FrameworkPropertyMetadata(options);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(
    const PropertyChangedDelegate& propChanged)
{
    return *new FrameworkPropertyMetadata(propChanged);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(
    const CoerceDelegate& coerce)
{
    return *new FrameworkPropertyMetadata(coerce);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(const T& defaultValue,
    NsInt32 options)
{
    return *new FrameworkPropertyMetadata(
        BoxingUtils::GetBoxedValue<T>(&defaultValue), options);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(const T& defaultValue,
    const PropertyChangedDelegate& propChanged)
{
    return *new FrameworkPropertyMetadata(
        BoxingUtils::GetBoxedValue<T>(&defaultValue), propChanged);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(const T& defaultValue,
    const CoerceDelegate& coerce)
{
    return *new FrameworkPropertyMetadata(
        BoxingUtils::GetBoxedValue<T>(&defaultValue), coerce);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(const T& defaultValue,
    NsInt32 options, const PropertyChangedDelegate& propChanged)
{
    return *new FrameworkPropertyMetadata(
        BoxingUtils::GetBoxedValue<T>(&defaultValue), options, propChanged);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(const T& defaultValue,
    NsInt32 options, const CoerceDelegate& coerce)
{
    return *new FrameworkPropertyMetadata(
        BoxingUtils::GetBoxedValue<T>(&defaultValue), options, coerce);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<FrameworkPropertyMetadata> FrameworkPropertyMetadata::Create(const T& defaultValue,
    NsInt32 options, const PropertyChangedDelegate& propChanged, const CoerceDelegate& coerce)
{
    return *new FrameworkPropertyMetadata(
        BoxingUtils::GetBoxedValue<T>(&defaultValue), options, propChanged, coerce);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::AffectsMeasure() const
{
    return (mFrameworkOptions & FrameworkOptions_AffectsMeasure) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::AffectsArrange() const
{
    return (mFrameworkOptions & FrameworkOptions_AffectsArrange) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::AffectsParentMeasure() const
{
    return (mFrameworkOptions & FrameworkOptions_AffectsParentMeasure) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::AffectsParentArrange() const
{
    return (mFrameworkOptions & FrameworkOptions_AffectsParentArrange) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::AffectsRender() const
{
    return (mFrameworkOptions & FrameworkOptions_AffectsRender) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::Inherits() const
{
    return (mFrameworkOptions & FrameworkOptions_Inherits) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::OverridesInheritanceBehavior() const
{
    return (mFrameworkOptions & FrameworkOptions_OverridesInheritanceBehavior) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::IsNotDataBindable() const
{
    return (mFrameworkOptions & FrameworkOptions_NotDataBindable) != 0;
}

/// Indicates whether the property binds two-way by default
inline NsBool FrameworkPropertyMetadata::BindsTwoWayByDefault() const
{
    return (mFrameworkOptions & FrameworkOptions_BindsTwoWayByDefault) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//inline NsBool FrameworkPropertyMetadata::Journal() const
//{
//    return (mFrameworkOptions & FrameworkOptions_Jornal) != 0;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline NsBool FrameworkPropertyMetadata::SubPropertiesDoNotAffectRender() const
{
    return (mFrameworkOptions & FrameworkOptions_SubPropertiesDoNotAffectRender) != 0;
}

}
}