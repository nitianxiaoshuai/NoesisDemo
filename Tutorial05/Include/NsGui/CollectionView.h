////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COLLECTIONVIEW_H__
#define __GUI_COLLECTIONVIEW_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/Events.h>
#include <NsGui/ICollectionView.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Vector.h>
#include <NsCore/Delegate.h>


NS_IFORWARD(Gui, IList)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// CollectionView
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API CollectionView: public Core::BaseComponent, public ICollectionView,
    public INotifyCollectionChanged, public IComponentInitializer, public IUITreeNode
{
public:
    /// Serialization constructor
    CollectionView();

    /// Constructor
    CollectionView(IList* collection);

    /// Destructor
    ~CollectionView();

    /// Returns the underlying unfiltered collection
    IList* GetSourceCollection() const;

    /// Gets the number of records in the view
    NsSize Count() const;

    /// Retrieves the item at the specified zero-based index in the view
    Core::BaseComponent* GetItemAt(NsSize index) const;

    /// Returns the index at which the specified item is located; -1 if the item is unknown
    NsInt IndexOf(Core::BaseComponent* item) const;

    /// From ICollectionView
    //@{
    NsBool CanFilter() const;
    NsBool CanGroup() const;
    NsBool CanSort() const;
    NsBool Contains(Core::BaseComponent* item) const;
    BaseComponent* CurrentItem() const;
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
    void InternalCollectionChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);

    void ConnectCollection();
    
    void SetCurrentPosition(NsInt pos);

private:
    friend class CollectionViewTest;

    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    NsBool mIsDynamic;
    NsInt mCurrentPosition;

    Ptr<IList> mCollection;

    EventHandler mCurrentChanged;
    NotifyCollectionChangedEventHandler mCollectionChanged;

    NS_DECLARE_REFLECTION(CollectionView, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif