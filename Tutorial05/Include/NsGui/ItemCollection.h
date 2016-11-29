////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ITEMCOLLECTION_H__
#define __GUI_ITEMCOLLECTION_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Delegate.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ICollectionView.h>
#include <NsGui/IList.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class ItemsControl;
class Collection;
class CollectionView;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ItemCollection
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ItemCollection: public Core::BaseComponent, public ICollectionView, 
    public IList, public INotifyCollectionChanged, public IComponentInitializer, 
    public IUITreeNode
{
public:
    ItemCollection();
    ItemCollection(ItemsControl* itemsControl);
    ~ItemCollection();

    /// Sets ItemCollection owner, it would be an ItemsControl object
    void SetItemsControlOwner(ItemsControl* itemsControl);
    
    /// To be called from ItemsControl when the ItemsSource is assigned with a CollectionView
    void SetView(CollectionView* view);
    
    /// Check if the itemcollection is related to an external collection, and so it is readonly
    NsBool IsReadOnly() const;
    
    /// From ICollectionView
    //@{
    NsBool CanFilter() const;
    NsBool CanGroup() const;
    NsBool CanSort() const;
    NsBool Contains(Core::BaseComponent* item) const;
    Core::BaseComponent* CurrentItem() const;
    NsInt CurrentPosition() const;
    NsBool IsCurrentAfterLast() const;
    NsBool IsCurrentBeforeFirst() const;
    NsBool IsEmpty() const;
    NsBool MoveCurrentTo(Core::BaseComponent* item);
    NsBool MoveCurrentToFirst();
    NsBool MoveCurrentToLast();
    NsBool MoveCurrentToNext();
    NsBool MoveCurrentToPosition(NsInt position);
    NsBool MoveCurrentToPrevious();
    void Refresh();
    EventHandler& CurrentChanged();
    //@}

    /// From IList
    //@{
    NsSize Count() const;
    Core::BaseComponent* Get(NsSize index) const;
    void Set(NsSize index, Core::BaseComponent* item);
    void Set(NsSize index, const NsChar* item);
    NsSize Add(Core::BaseComponent* item);
    NsSize Add(const NsChar* item);
    void Clear();
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

private:
    void CheckReadOnly() const;

    void ConnectChildren() const;
    void DisconnectChildren() const;

    void CreateCollections();

    void OnCollectionChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);
    void OnCurrentChanged(Core::BaseComponent* sender, const EventArgs& args);

    void ConnectCollection();
    void DisconnectCollection();

    void RegisterDelegates();
    void UnregisterDelegates();
    
private:
    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    ItemsControl* mItemsControl;
    
    Ptr<Collection> mLocalCollection;
    Ptr<CollectionView> mEffectiveCollectionView;
    
    EventHandler mCurrentChanged;
    NotifyCollectionChangedEventHandler mCollectionChanged;

    NS_DECLARE_REFLECTION(ItemCollection, BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif