////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_UIPROPERTYMETADATA_H__
#define __GUI_UIPROPERTYMETADATA_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// UIPropertyMetadata. Provides property metadata for non-framework properties that do have
/// rendering/user interface impact at the core level.
///
/// WPF UIPropertyMetadata fields:
///  - IsAnimationProhibited
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API UIPropertyMetadata: public PropertyMetadata
{
public:
    /// Helper functions to create a new PropertyMetadata
    //@{
    inline static Ptr<UIPropertyMetadata> Create();

    template<class T>
    inline static Ptr<UIPropertyMetadata> Create(const T& defaultValue);

    inline static Ptr<UIPropertyMetadata> Create(const PropertyChangedDelegate& propChanged);

    inline static Ptr<UIPropertyMetadata> Create(const CoerceDelegate& coerce);

    template<class T>
    inline static Ptr<UIPropertyMetadata> Create(const T& defaultValue,
        const PropertyChangedDelegate& propChanged);

    template<class T>
    inline static Ptr<UIPropertyMetadata> Create(const T& defaultValue,
        const CoerceDelegate& coerce);

    template<class T>
    inline static Ptr<UIPropertyMetadata> Create(const T& defaultValue,
        const PropertyChangedDelegate& propChanged, const CoerceDelegate& coerce);
    //@}

    /// Constructors
    //@{
    UIPropertyMetadata();
    UIPropertyMetadata(const Ptr<Core::BaseComponent>& defaultValue);
    UIPropertyMetadata(const PropertyChangedDelegate& propChanged);
    UIPropertyMetadata(const CoerceDelegate& coerce);
    UIPropertyMetadata(const Ptr<Core::BaseComponent>& defaultValue,
        const PropertyChangedDelegate& propChanged);
    UIPropertyMetadata(const Ptr<Core::BaseComponent>& defaultValue, const CoerceDelegate& coerce);
    UIPropertyMetadata(const Ptr<Core::BaseComponent>& defaultValue,
        const PropertyChangedDelegate& propChanged, const CoerceDelegate& coerce);
    //@}

    NS_DECLARE_REFLECTION(UIPropertyMetadata, PropertyMetadata)
};

}
}

/// Inline Include
#include <NsGui/UIPropertyMetadata.inl>

#endif
