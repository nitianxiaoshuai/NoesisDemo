////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PROPERTYPATH_H__
#define __GUI_PROPERTYPATH_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/String.h>
#include <NsCore/Ptr.h>
#include <NsCore/Symbol.h>
#include <NsCore/Vector.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{

// Forward declarations
namespace Core
{
template<class T> class Delegate;
class TypeProperty;
namespace PE
{
struct PropertyPathExpr;
}
}
namespace Gui
{
class Collection;
class DependencyProperty;
class CollectionView;
NS_INTERFACE IResourceKey;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API PathElement
{
    PathElement();
    PathElement(const PathElement& pe);
    ~PathElement();
    
    PathElement& operator=(const PathElement& pe);

    // If you add a new member here, remember to add the proper code in copy ctor and operator=
    Ptr<Core::BaseComponent> source;
    Ptr<CollectionView> collection;
    const Core::TypeProperty* property;
    const DependencyProperty* dp;
    NsInt index;
    Ptr<IResourceKey> key;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PropertyPath
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API PropertyPath: public Core::BaseComponent
{
public:
    PropertyPath();
    PropertyPath(const NsChar* str);
    PropertyPath(const DependencyProperty* dp);
    ~PropertyPath();

    /// Creates a property path from a string
    static Ptr<PropertyPath> Parse(const NsChar* str);

    /// Creates and caches a property path that points to a property
    /// \returns Null if path does not corresponds to a valid property name
    static PropertyPath* Create(const NsChar* path);

    /// Gets or sets path
    //@{
    const NsChar* GetPath() const;
    void SetPath(const NsChar* path);
    //@}

    /// \return False if path cannot be resolved for the provided source
    typedef NsVector<PathElement> Elements;
    NsBool GetPathElements(BaseComponent* source, NsBool insertLastValue, Elements& elements) const;

    /// \return False if path cannot be resolved for the provided source
    typedef Noesis::Core::Delegate<void (const PathElement&, void*)> EnumPathElementsDelegate;
    NsBool EnumPathElements(BaseComponent* source, NsBool enumLastValue,
        const EnumPathElementsDelegate& delegate, void* context = 0) const;

private:
    void AddPathElements(const PathElement& pathElement, void* context) const;
    void UpdatePathItems() const;
    const NsString& RebuildPath() const;

private:
    friend class PropertyPathTest;

    mutable NsString mPath;

    struct PathItem
    {
        NsBool slash;
        NsSymbol owner;
        NsSymbol prop;

        struct IndexKey
        {
            NsInt index;
            NsString key;

            /// Constructor
            IndexKey();
        };

        NsVector<IndexKey> keys;

        /// Constructor
        PathItem();
    };

    typedef NsVector<PathItem> PathItems;
    mutable PathItems mPathItems;

    NS_DECLARE_REFLECTION(PropertyPath, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
