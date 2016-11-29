////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_FRAMEWORKPROPERTYMETADATA_H__
#define __CORE_FRAMEWORKPROPERTYMETADATA_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/UIPropertyMetadata.h>
#include <NsGui/UpdateSourceTrigger.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// FrameworkOptions. Specifies the types of framework-level property behavior that pertain to a
/// particular dependency property in the property system.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FrameworkOptions
{
    FrameworkOptions_None = 1 << 0,
    FrameworkOptions_AffectsMeasure = 1 << 1,
    FrameworkOptions_AffectsArrange = 1 << 2,
    FrameworkOptions_AffectsParentMeasure = 1 << 3,
    FrameworkOptions_AffectsParentArrange = 1 << 4,
    FrameworkOptions_AffectsRender = 1 << 5,
    FrameworkOptions_Inherits = 1 << 6,
    FrameworkOptions_OverridesInheritanceBehavior = 1 << 7,
    FrameworkOptions_NotDataBindable = 1 << 8,
    FrameworkOptions_BindsTwoWayByDefault = 1 << 9,
    //FrameworkOptions_Journal = 1 << 10,
    FrameworkOptions_SubPropertiesDoNotAffectRender = 1 << 11,
    FrameworkOptions_UpdateSourceTriggerLostFocus = 1 << 12,
    FrameworkOptions_UpdateSourceTriggerExplicit = 1 << 13
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// FrameworkPropertyMetadata. Reports or applies metadata for a dependency property, specifically
/// adding framework-specific property system characteristics.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FrameworkPropertyMetadata: public UIPropertyMetadata
{
public:
    /// Helper functions to create a new PropertyMetadata
    //@{
    inline static Ptr<FrameworkPropertyMetadata> Create();

    inline static Ptr<FrameworkPropertyMetadata> Create(NsInt32 options);

    inline static Ptr<FrameworkPropertyMetadata> Create(const PropertyChangedDelegate& propChanged);

    inline static Ptr<FrameworkPropertyMetadata> Create(const CoerceDelegate& coerce);

    template<class T>
    inline static Ptr<FrameworkPropertyMetadata> Create(const T& defaultValue, NsInt32 options);

    template<class T>
    inline static Ptr<FrameworkPropertyMetadata> Create(const T& defaultValue,
        const PropertyChangedDelegate& propChanged);

    template<class T>
    inline static Ptr<FrameworkPropertyMetadata> Create(const T& defaultValue,
        const CoerceDelegate& coerce);

    template<class T>
    inline static Ptr<FrameworkPropertyMetadata> Create(const T& defaultValue, NsInt32 options,
        const PropertyChangedDelegate& propChanged);
    
    template<class T>
    inline static Ptr<FrameworkPropertyMetadata> Create(const T& defaultValue, NsInt32 options,
        const CoerceDelegate& coerce);
    
    template<class T>
    inline static Ptr<FrameworkPropertyMetadata> Create(const T& defaultValue, NsInt32 options,
        const PropertyChangedDelegate& propChanged, const CoerceDelegate& coerce);
    //@}

    /// Constructors
    //@{
    FrameworkPropertyMetadata();
    FrameworkPropertyMetadata(NsInt32 options);
    FrameworkPropertyMetadata(const PropertyChangedDelegate& propChanged);
    FrameworkPropertyMetadata(const CoerceDelegate& coerce);
    FrameworkPropertyMetadata(const Ptr<Core::BaseComponent>& defValue,
        const PropertyChangedDelegate& propChanged);
    FrameworkPropertyMetadata(const Ptr<Core::BaseComponent>& defValue,
        const CoerceDelegate& coerce);
    FrameworkPropertyMetadata(const Ptr<Core::BaseComponent>& defValue, NsInt32 options);
    FrameworkPropertyMetadata(const Ptr<Core::BaseComponent>& defValue, NsInt32 options,
        const PropertyChangedDelegate& propChanged);
    FrameworkPropertyMetadata(const Ptr<Core::BaseComponent>& defValue, NsInt32 options,
        const CoerceDelegate& coerce);
    FrameworkPropertyMetadata(const Ptr<Core::BaseComponent>& defValue, NsInt32 options,
        const PropertyChangedDelegate& propChanged, const CoerceDelegate& coerce);
    //@}

    /// Indicates if the property affects measure layout pass
    inline NsBool AffectsMeasure() const;

    /// Indicates if the property affects arrange layout pass
    inline NsBool AffectsArrange() const;

    /// Indicates if the property affects parent measure layout pass
    inline NsBool AffectsParentMeasure() const;

    /// Indicates if the property affects parent arrange layout pass
    inline NsBool AffectsParentArrange() const;

    /// Indicates if the property affects render pass
    inline NsBool AffectsRender() const;

    /// Indicates if the property inherits its value from logical tree ancestors
    inline NsBool Inherits() const;

    /// Indicates whether the property value inheritance evaluation should span across certain
    /// content boundaries in the logical tree of elements
    inline NsBool OverridesInheritanceBehavior() const;

    /// Indicates whether the dependency property supports data binding
    inline NsBool IsNotDataBindable() const;

    /// Indicates whether the property binds two-way by default
    inline NsBool BindsTwoWayByDefault() const;
    
    /// Gets the default for UpdateSourceTrigger to use when bindings for the property with this 
    /// metadata are applied, which have their UpdateSourceTrigger set to Default.
    UpdateSourceTrigger DefaultUpdateSourceTrigger() const;

    /// Indicates whether this property contains journaling information that applications can or
    /// should store as part of a journaling implementation
    //inline NsBool Journal() const;

    /// Indicates whether sub-properties of the dependency property do not affect the rendering of
    /// the containing object
    inline NsBool SubPropertiesDoNotAffectRender() const;
    
    /// From PropertyMetadata
    //@{
    void ClearInheritedValues();
    void Merge(const PropertyMetadata* ancestor);
    //@}

private:
    NsInt32 mLocalOptions;
    NsInt32 mFrameworkOptions;

    NS_DECLARE_REFLECTION(FrameworkPropertyMetadata, UIPropertyMetadata)
};

}
}

/// Inline Include
#include <NsGui/FrameworkPropertyMetadata.inl>


#endif
