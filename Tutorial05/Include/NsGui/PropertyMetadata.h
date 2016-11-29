////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1197]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PROPERTYMETADATA_H__
#define __GUI_PROPERTYMETADATA_H__


#include <Noesis.h>
#include <NsGui/DependencySystemApi.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Delegate.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyProperty;
class DependencyObject;
struct DependencyPropertyChangedEventArgs;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PropertyMetadata. Defines certain behavior aspects of a dependency property as it is applied to
/// a specific type, including conditions it was registered with.
///
/// WPF PropertyMetadata fields:
///  - DefaultValue
///  - PropertyChangedCallback
///  - CoerceValueCallback
///  - IsSealed
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_DEPENDENCYSYSTEM_API PropertyMetadata: public Core::BaseComponent
{
public:
    typedef Core::Delegate<NsBool (const DependencyObject* d, const void* value, 
        void* coercedValue)> CoerceDelegate;

    typedef Core::Delegate<void (DependencyObject* d, const DependencyPropertyChangedEventArgs& e)>
        PropertyChangedDelegate;

    typedef Core::Delegate<void(PropertyMetadata* m)> DestroyedDelegate;

    /// Helper functions to create a new PropertyMetadata
    //@{
    inline static Ptr<PropertyMetadata> Create();

    template<class T>
    inline static Ptr<PropertyMetadata> Create(const T& defaultValue);

    inline static Ptr<PropertyMetadata> Create(const PropertyChangedDelegate& propChanged);

    inline static Ptr<PropertyMetadata> Create(const CoerceDelegate& coerce);

    template<class T>
    inline static Ptr<PropertyMetadata> Create(const T& defaultValue,
        const PropertyChangedDelegate& propChanged);

    template<class T>
    inline static Ptr<PropertyMetadata> Create(const T& defaultValue, const CoerceDelegate& coerce);

    template<class T>
    inline static Ptr<PropertyMetadata> Create(const T& defaultValue,
        const PropertyChangedDelegate& propChanged, const CoerceDelegate& coerce);
    //@}

    /// Constructors
    //@{
    PropertyMetadata();
    PropertyMetadata(const Ptr<Core::BaseComponent>& defaultValue);
    PropertyMetadata(const PropertyChangedDelegate& propChanged);
    PropertyMetadata(const CoerceDelegate& coerce);
    PropertyMetadata(const Ptr<Core::BaseComponent>& defaultValue,
        const PropertyChangedDelegate& propChanged);
    PropertyMetadata(const Ptr<Core::BaseComponent>& defaultValue, const CoerceDelegate& coerce);
    PropertyMetadata(const Ptr<Core::BaseComponent>& defaultValue,
        const PropertyChangedDelegate& propChanged, const CoerceDelegate& coerce);
    //@}

    ~PropertyMetadata();

    inline NsBool HasDefaultValue() const;
    inline const Ptr<Core::BaseComponent>& GetDefaultValue() const;
    void SetDefaultValue(Core::BaseComponent* def);

    inline NsBool HasCoerceDelegate() const;
    inline const CoerceDelegate& GetCoerceDelegate() const;
    void SetCoerceDelegate(const CoerceDelegate& coerce);

    inline NsBool HasPropertyChangedDelegate() const;
    inline const PropertyChangedDelegate& GetPropertyChangedDelegate() const;
    void SetPropertyChangedDelegate(const PropertyChangedDelegate& propertyChanged);

    inline NsBool IsUncached() const;
    inline NsBool Uncached() const;

    void SetAsUncached();

    /// Remove inherited values from ancestors
    virtual void ClearInheritedValues();

    /// Inherit ancestor values if they are not local in this class
    virtual void Merge(const PropertyMetadata* ancestor);

    /// Notifies listeners when metadata is destroyed
    DestroyedDelegate& Destroyed();

protected:
    /// From BaseComponent
    //@{
    NsInt32 OnDestroy() const;
    //@}

private:
    /// Default value is boxed
    Ptr<Core::BaseComponent> mDefaultValue;

    /// Delegate to be invoked to coerce a value
    CoerceDelegate mCoerceDelegate;

    /// Delegate to be invoked when a property changes
    PropertyChangedDelegate mPropertyChangedDelegate;

    /// Delegate to be invoked when metadata is going to deleted
    DestroyedDelegate mDestroyed;

    enum PropertyFlags
    {
        PropertyFlags_None = 0,
        PropertyFlags_Default = 1 << 1,
        PropertyFlags_Coerce = 1 << 2,
        PropertyFlags_Changed = 1 << 3,
        PropertyFlags_Uncached = 1 << 4
    };

    /// Flag to control if properties value are local or inherited
    NsUInt32 mLocalFlags;

    /// Tells if the property must not be cached in the DependencyObject internal hash
    NsBool mUncached;

    NS_DECLARE_REFLECTION(PropertyMetadata, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

/// Inline Include
#include <NsGui/PropertyMetadata.inl>


#endif
