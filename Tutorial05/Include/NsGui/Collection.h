////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COLLECTION_H__
#define __GUI_COLLECTION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/IList.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>
#include <NsCore/NSTLForwards.h>
#include <NsCore/Vector.h>
#include <NsCore/String.h>
#include <NsCore/DynamicCast.h>
#include <NsCore/Error.h>
#include <NsCore/Delegate.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides the base class for a generic collection.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Collection: public Core::BaseComponent, public IList,
    public INotifyCollectionChanged, public IComponentInitializer, public IUITreeNode
{
public:
    /// Constructor
    Collection();
    Collection(IUITreeNode* owner);

    /// Destructor
    virtual ~Collection();

    /// From IList
    //@{
    NsSize Count() const;
    Core::BaseComponent* Get(NsSize index) const;
    void Set(NsSize index, Core::BaseComponent* item);
    void Set(NsSize index, const NsChar* item);
    NsSize Add(Core::BaseComponent* item);
    NsSize Add(const NsChar* item);
    void Clear();
    NsBool Contains(Core::BaseComponent* item) const;
    NsInt IndexOf(Core::BaseComponent* item) const;
    void Insert(NsSize index, Core::BaseComponent* item);
    void Insert(NsSize index, const NsChar* item);
    void Remove(Core::BaseComponent* item);
    void RemoveAt(NsSize index);
    //@}

    /// From INotifyCollectionChanged
    //@{
    NotifyCollectionChangedEventHandler& CollectionChanged();
    //@}

    /// From IComponentInitializer
    //@{
    NsBool IsInitialized() const;
    void Init();
    //@}

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

protected:
    /// Allows inheritors to perform specific actions when items are added or removed
    //@{
    virtual void OnItemAdded(Core::BaseComponent* item, NsSize index);
    virtual void OnItemRemoved(Core::BaseComponent* item, NsSize index);
    //@}

    // To check before adding an element
    virtual void CheckItem(Core::BaseComponent* item) const;

    // Helper function to get item's type name taking into account boxed values
    static const NsChar* GetItemType(Core::BaseComponent* item);

private:
    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    typedef NsVector<Ptr<Core::BaseComponent> > Items;
    Items mItems;

    NotifyCollectionChangedEventHandler mEvent;

    NS_DECLARE_REFLECTION(Collection, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_GUI_CORE_API NsString IdOfTypedCollection(const Core::TypeClass* type);

////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class TypedCollection: public Collection
{
protected:
    /// From Collection
    //@{
    void CheckItem(BaseComponent* item) const
    {
        ParentClass::CheckItem(item);

        if (NsDynamicCast<T*>(item) == 0)
        {
            NS_ERROR("Can't add a '%s' to a '%s'", GetItemType(item),
                IdOfTypedCollection(Core::TypeOf<T>()).c_str());
        }
    }
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION(TypedCollection, Collection)
    {
        NsMeta<Core::TypeId>(IdOfTypedCollection(Core::TypeOf<T>()).c_str());
    }
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}

#endif
