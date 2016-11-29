////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ITEMCONTAINERGENERATOR_H__
#define __GUI_ITEMCONTAINERGENERATOR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IRecyclingItemContainerGenerator.h>
#include <NsGui/Events.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Delegate.h>
#include <NsCore/NSTLPoolAllocator.h>
#include <NsCore/List.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyObject;
class DependencyProperty;
class ItemsControl;
class Panel;
struct NotifyCollectionChangedEventArgs;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// The ItemsChanged event is raised by an ItemContainerGenerator to inform layouts that the items
/// collection has changed.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ItemsChangedEventArgs: public EventArgs
{
    NotifyCollectionChangedAction action;
    GeneratorPosition position;
    GeneratorPosition oldPosition;
    NsInt itemCount;
    NsInt itemUICount;

private:
    friend class ItemContainerGenerator;

    ItemsChangedEventArgs(NotifyCollectionChangedAction action, const GeneratorPosition& position,
        const GeneratorPosition& oldPosition, NsInt itemCount, NsInt itemUICount);

    ItemsChangedEventArgs(NotifyCollectionChangedAction action, const GeneratorPosition& position,
        NsInt itemCount, NsInt itemUICount);

    NS_IMPLEMENT_INLINE_REFLECTION_(ItemsChangedEventArgs, EventArgs)
};

typedef Core::Delegate<void(Core::BaseComponent*, const ItemsChangedEventArgs&)>
    ItemsChangedEventHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Generates the user interface on behalf of its host, such as an ItemsControl.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.itemcontainergenerator.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ItemContainerGenerator: public Core::BaseComponent,
    public IRecyclingItemContainerGenerator
{
public:
    // TODO: Expose Items as a ReadOnlyCollection<object>

    /// Gets the status of the generator
    GeneratorStatus GetStatus() const;

    /// Raised to inform controls that ItemContainerGenerator status has changed
    EventHandler& StatusChanged();

    /// Raised by a ItemContainerGenerator to inform layouts that the items collection has changed
    ItemsChangedEventHandler& ItemsChanged();

    /// Returns the container corresponding to the item at the given index within the Items
    DependencyObject* ContainerFromIndex(NsInt index) const;

    /// Returns the container corresponding to the given item. Returns null if the item does not
    /// belong to the item collection, or if no container has been generated for it
    DependencyObject* ContainerFromItem(Core::BaseComponent* item) const;

    /// Given a generated container, returns the index of the corresponding item within the Items
    NsInt IndexFromContainer(DependencyObject* container) const;

    /// Returns the item corresponding to the given container. If the element was not generated as
    /// a container for this generator's host, the method returns DependencyProperty.UnsetValue
    Core::BaseComponent* ItemFromContainer(DependencyObject* container) const;

    /// From IItemContainerGenerator
    //@{
    ItemContainerGenerator* GetItemContainerGeneratorForPanel(Panel* panel) const;
    GeneratorPosition GeneratorPositionFromIndex(NsInt itemIndex) const;
    NsInt IndexFromGeneratorPosition(const GeneratorPosition& position) const;
    void StartAt(const GeneratorPosition& position, GeneratorDirection direction);
    void StartAt(const GeneratorPosition& position, GeneratorDirection direction,
        NsBool allowStartAtRealizedItem);
    Ptr<DependencyObject> GenerateNext();
    Ptr<DependencyObject> GenerateNext(NsBool& isNewlyRealized);
    void Stop();
    void PrepareItemContainer(DependencyObject* container) const;
    void Remove(const GeneratorPosition& position, NsSize count);
    void RemoveAll();
    //@}

    /// From IRecyclingItemContainerGenerator
    //@{
    void Recycle(const GeneratorPosition& position, NsSize count);
    //@}

private:
    friend class ItemsControl;
    friend class GeneratorContext;
    friend class VirtualizingStackPanel;

    ItemContainerGenerator();
    ItemContainerGenerator(ItemsControl* host);

    void StartBatch();
    void StopBatch();

    void Refresh();

    void ResetLastNodeIndex() const;

    void SetStatus(GeneratorStatus status);

    Ptr<DependencyObject> GenerateNext(NsBool stopAtRealized, NsBool& isNewlyRealized);

    static Core::BaseComponent* GetContainerItem(DependencyObject* container);
    static void SetContainerItem(DependencyObject* container, Core::BaseComponent* item);

    void OnItemsChanged(Core::BaseComponent* sender, const NotifyCollectionChangedEventArgs& e);
    void OnItemAdded(Core::BaseComponent* item, NsInt index);
    void OnItemRemoved(Core::BaseComponent* item, NsInt index);
    void OnItemReplaced(Core::BaseComponent* oldItem, Core::BaseComponent* newItem, NsInt index);
    void OnItemMoved(Core::BaseComponent* item, NsInt oldIndex, NsInt newIndex);
    void OnReset();

    void AttachContainerItem(DependencyObject* container, Core::BaseComponent* item);
    void DetachContainerItem(DependencyObject* container, Core::BaseComponent* item);

private:
    friend class ItemContainerGeneratorTest;
    friend class VirtualizingStackPanelTest;

    // Host for generator items
    ItemsControl* mHost;

    // Stores info about one (realized) or several (unrealized) items
    struct ItemNode
    {
        enum Type { Unrealized, Realized };
        Type type;

        union
        {
            struct
            {
                NsSize numItems;
            }
            unrealized;

            struct
            {
                Core::BaseComponent* item;
                DependencyObject* container;
            }
            realized;
        };

        ItemNode(NsSize n = 0);
        ItemNode(Core::BaseComponent* i, DependencyObject* c);
        ~ItemNode();

        ItemNode(const ItemNode& node);
        ItemNode& operator=(const ItemNode& node);

        NsSize NumItems() const;
        NsSize NumContainers() const;

        Core::BaseComponent* Item() const;
        DependencyObject* Container() const;

        NsBool MoveAllowed(NsBool allowMove) const;

        NsBool IsRealized() const;

        void Unrealize(NsSize n);
        void Realize(Core::BaseComponent* i, DependencyObject* c);

    private:
        void CopyFrom(const ItemNode& node);
        void UnrealizeInternal(NsSize n);
        void RealizeInternal(Core::BaseComponent* i, DependencyObject* c);
        void Release();
    };

    // Holds correspondence between Items and their Containers. Usually a group of unrealized
    // (virtualized) items, followed by some realized (visible) items, and a final group of
    // unrealized items:
    //
    //       ------------      --------------             --------------      ------------ 
    //      |     n      |    | 1 item*      |           | 1 item*      |    |     n      |
    //      | unrealized | -> | 1 container* | -> ... -> | 1 container* | -> | unrealized |
    //       ------------      --------------             --------------      ------------ 
    //
    typedef NsList<ItemNode, Core::nstl::PoolAllocator> ItemNodes;
    ItemNodes mItemNodes;
    NsSize mNumItems;

    void Remove(const GeneratorPosition& position, NsSize count, NsBool recycleContainers,
        const NsChar* actionName);
    void Remove(const ItemNodes::iterator& startIt, NsInt startIndex, NsSize count,
        NsBool allowUnrealizedItems, NsBool recycleContainers, const NsChar* actionName);
    NsInt RemoveItem(const ItemNodes::iterator& it);
    void CoalesceNodes(const ItemNodes::iterator& prevIt, const ItemNodes::iterator& nextIt);
    ItemNodes::iterator FindNodeFromIndex(NsInt index, NsInt& itemIndex, NsInt& offset);
    void MoveForward();
    void MoveForward(NsInt offset, NsBool allowStartAtRealizedItem);
    void MoveBackward();
    void MoveBackward(NsInt offset, NsBool allowStartAtRealizedItem);

    // Stores recycled containers to be used in future generations
    typedef NsVector<Ptr<DependencyObject> > RecycledContainers;
    RecycledContainers mRecycledContainers;

    // Generator status
    GeneratorStatus mStatus;
    NsBool mBatching;

    // Generation state
    GeneratorDirection mDirection;
    ItemNodes::iterator mNode; // node where next generation should occur
    NsInt mOffset; // offset inside the current node where next generation should occur
    NsInt mItemIndex; // index of next generated item

    // Events
    EventHandler mStatusChanged;
    ItemsChangedEventHandler mItemsChanged;

    // Stores a reference to the item in the container to speed up some searches
    static const DependencyProperty* ContainerItemProperty;

    // Optimization for ContainerFromIndex look-ups
    mutable ItemNodes::const_iterator mLastNode;
    mutable NsInt mLastIndex;

    NS_DECLARE_REFLECTION(ItemContainerGenerator, Core::BaseComponent)
};

}
}


#endif
