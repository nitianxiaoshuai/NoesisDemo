////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DEPENDENCYDATA_H__
#define __GUI_DEPENDENCYDATA_H__


#include <Noesis.h>
#include <NsGui/DependencySystemApi.h>
#include <NsGui/DependencyProperty.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsCore/HashMap.h>


NS_CFORWARD(Gui, PropertyMetadata)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DependencyData. Used to register dependency properties for a type.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_DEPENDENCYSYSTEM_API DependencyData: public Core::TypeMetaData
{
public:
    /// Constructor
    DependencyData(const Core::TypeClass* ownerType);

    /// Registers a dependency property for a type
    /// \param dp Dependency property to store the created property
    /// \param name The name of the dependency property. The name must be unique for the type
    /// \param metaData This object stores extra information about the property
    /// \param validate Delegate to be executed to validate the property value
    /// \remarks Version ending in RO create a Read-Only property
    //@{
    template<class T>
    void RegisterProperty(const DependencyProperty*& dp, const NsChar* name,
        const Ptr<PropertyMetadata>& metaData);
    template<class T>
    void RegisterPropertyRO(const DependencyProperty*& dp, const NsChar* name,
        const Ptr<PropertyMetadata>& metaData);
    template<class T>
    void RegisterProperty(const DependencyProperty*& dp, const NsChar* name,
        const Ptr<PropertyMetadata>& metaData,
        const DependencyProperty::ValidateValueDelegate& validate);
    template<class T>
    void RegisterPropertyRO(const DependencyProperty*& dp, const NsChar* name,
        const Ptr<PropertyMetadata>& metaData,
        const DependencyProperty::ValidateValueDelegate& validate);
    //@}

    // Used internally
    const DependencyProperty* InsertProperty(const DependencyProperty* dp);

    /// Adds another type as an owner of a property that has already been registered to a type
    /// \param dp Dependency property of the DependencyData owner type
    /// \param name The name of the dependency property. Must be the same as the original name
    /// \param source Original dependency property
    /// \param metaData Extra info added to the property for the DependencyData owner type
    template<class T>
    void AddOwner(const DependencyProperty*& dp, const NsChar* name,
        const DependencyProperty*& source, const Ptr<PropertyMetadata>& metaData = 
        Ptr<PropertyMetadata>());

    /// Supplies alternate metadata for this dependency property when it is present on instances of
    /// a specified type, versus the metadata that was provided in the initial dependency property
    /// registration
    /// \param dp Dependency property of the DependencyData owner type
    /// \param name The name of the dependency property. Must be the same as the original name
    template<class T>
    void OverrideMetadata(const DependencyProperty*& dp, const NsChar* name, 
        const Ptr<PropertyMetadata>& metaData);

    /// Finds a property for the owner type given its name
    const DependencyProperty* FindProperty(NsSymbol name) const;

private:
    template<class T>
    void RegisterProperty(const DependencyProperty*& dp, const NsChar* name,
        const Ptr<PropertyMetadata>& metaData, PropertyAccess access, 
        const DependencyProperty::ValidateValueDelegate& validate);

    void RegisterExistingProperty(const DependencyProperty* dp, const NsChar* name,
        const Ptr<PropertyMetadata>& metaData, PropertyAccess access,
        const DependencyProperty::ValidateValueDelegate& validate);

    typedef Core::Int2Type<0> IsNotBaseComponent;
    typedef Core::Int2Type<1> IsBaseComponent;

    template<class T>
    Ptr<DependencyProperty> CreateProperty(const NsChar* name,
        const Ptr<PropertyMetadata>& metaData, PropertyAccess access,
        const DependencyProperty::ValidateValueDelegate& validate, IsNotBaseComponent);
    template<class T>
    Ptr<DependencyProperty> CreateProperty(const NsChar* name,
        const Ptr<PropertyMetadata>& metaData, PropertyAccess access,
        const DependencyProperty::ValidateValueDelegate& validate, IsBaseComponent);

    template<class T>
    Ptr<DependencyProperty> CreateProperty(const NsChar* name, IsNotBaseComponent);
    template<class T>
    Ptr<DependencyProperty> CreateProperty(const NsChar* name, IsBaseComponent);

    template<class T>
    NsBool CheckPropertyType(const DependencyProperty* dp, IsNotBaseComponent);
    template<class T>
    NsBool CheckPropertyType(const DependencyProperty* dp, IsBaseComponent);

    template<class T>
    NsBool CheckMetaData(PropertyMetadata* metaData) const;

protected:
    const Core::TypeClass* mOwnerType;

private:
    friend class DependencyDataTest;

    struct Adapter;

    typedef NsHashMap<NsSymbol, Ptr<const DependencyProperty> > PropertyMap;
    PropertyMap mProperties;

    NS_DECLARE_REFLECTION(DependencyData, Core::TypeMetaData)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}

/// Inline include
#include <NsGui/DependencyData.inl>


#endif
