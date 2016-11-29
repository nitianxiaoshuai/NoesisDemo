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
inline Ptr<UIPropertyMetadata> UIPropertyMetadata::Create()
{
    return *new UIPropertyMetadata();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<UIPropertyMetadata> UIPropertyMetadata::Create(const T& defaultValue)
{
    return *new UIPropertyMetadata(BoxingUtils::GetBoxedValue<T>(&defaultValue));
}


////////////////////////////////////////////////////////////////////////////////////////////////////
inline Ptr<UIPropertyMetadata> UIPropertyMetadata::Create(
    const PropertyChangedDelegate& propChanged)
{
    return *new UIPropertyMetadata(propChanged);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Ptr<UIPropertyMetadata> UIPropertyMetadata::Create(const CoerceDelegate& coerce)
{
    return *new UIPropertyMetadata(coerce);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<UIPropertyMetadata> UIPropertyMetadata::Create(const T& defaultValue,
    const PropertyChangedDelegate& propChanged)
{
    return *new UIPropertyMetadata(BoxingUtils::GetBoxedValue<T>(&defaultValue),
        propChanged);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<UIPropertyMetadata> UIPropertyMetadata::Create(const T& defaultValue,
    const CoerceDelegate& coerce)
{
    return *new UIPropertyMetadata(BoxingUtils::GetBoxedValue<T>(&defaultValue),
        coerce);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Ptr<UIPropertyMetadata> UIPropertyMetadata::Create(const T& defaultValue,
    const PropertyChangedDelegate& propChanged, const CoerceDelegate& coerce)
{
    return *new UIPropertyMetadata(BoxingUtils::GetBoxedValue<T>(&defaultValue),
        propChanged, coerce);
}

}
}