////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FREEZABLECOLLECTION_H__
#define __GUI_FREEZABLECOLLECTION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Freezable.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/IList.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/TypeId.h>
#include <NsCore/String.h>
#include <NsCore/Vector.h>
#include <NsCore/DynamicCast.h>
#include <NsCore/Error.h>
#include <NsCore/ReflectionImplement.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// FreezableCollection. Base collection implementation for storing Freezables
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FreezableCollection: public Freezable, public IList,
    public INotifyCollectionChanged, public IUITreeNode
{
public:
    /// Constructor
    FreezableCollection();
    FreezableCollection(IUITreeNode* owner);

    /// Destructor
    virtual ~FreezableCollection();

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

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

protected:
    // To check an item before adding it to the collection
    virtual void CheckItem(Core::BaseComponent* item) const;

    /// Allows inheritors to perform specific actions when items are added or removed
    //@{
    virtual void OnItemAdded(Core::BaseComponent* item, NsSize index);
    virtual void OnItemRemoved(Core::BaseComponent* item, NsSize index);
    //@}
    
    /// From Freezable
    //@{
    NsBool FreezeCore(NsBool isChecking);
    void CloneCore(const Freezable* source);
    void CloneCurrentValueCore(const Freezable* source);
    void GetAsFrozenCore(const Freezable* source);
    void GetCurrentValueAsFrozenCore(const Freezable* source);
    //void CloneCommonCore(const Freezable* source);
    //@}
    
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

private:
    void CheckFrozen();

private:
    IUITreeNode* mOwner;

    typedef NsVector<Ptr<Core::BaseComponent> > Items;
    Items mItems;
    
    NotifyCollectionChangedEventHandler mEvent;

    NS_DECLARE_REFLECTION(FreezableCollection, Freezable)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_GUI_CORE_API NsString IdOfTypedFreezableCollection(const Core::TypeClass* type);

////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class TypedFreezableCollection: public FreezableCollection
{
protected:
    /// From FreezableCollection
    //@{
    void CheckItem(BaseComponent* item) const
    {
        ParentClass::CheckItem(item);

        if (NsDynamicCast<T*>(item) == 0)
        {
            NS_ERROR("'%s' items not allowed for '%s' collection", item->GetClassType()->GetName(),
                GetClassType()->GetName());
        }
    }
    //@}
    
    NS_IMPLEMENT_INLINE_REFLECTION(TypedFreezableCollection, FreezableCollection)
    {
        NsMeta<Core::TypeId>(IdOfTypedFreezableCollection(Core::TypeOf<T>()).c_str());
    }
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
