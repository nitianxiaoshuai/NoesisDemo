////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RESOURCEDICTIONARY_H__
#define __GUI_RESOURCEDICTIONARY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/DictionaryMap.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/BaseDictionary.h>
#include <NsGui/INameScope.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/HashMap.h>


NS_CFORWARD(Gui, ResourceDictionary)
NS_CFORWARD(Gui, DelayedStaticResources)
NS_SFORWARD(Gui, NotifyCollectionChangedEventArgs)


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::ResourceDictionary> ResourceDictionaryCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a hash table that contains resources used by the UI.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.resourcedictionary.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ResourceDictionary: public BaseDictionary,
    public IComponentInitializer, public INameScope, public IUITreeNode
{
public:
    /// Constructor
    ResourceDictionary();

    /// Destructor
    ~ResourceDictionary();

    /// Indicates if this dictionary or any of the merged dictionaries contains a resource
    NsBool HasResourcesDefined() const;

    /// Gets a collection of the ResourceDictionary dictionaries that constitute the various 
    /// resource dictionaries in the merged dictionaries.
    ResourceDictionaryCollection* GetMergedDictionaries() const;

    /// Get or set source file for dictionary
    //@{
    const NsChar* GetSource() const;
    void SetSource(const NsChar* source);
    //@}

    /// From IDictionary
    //@{
    NsBool Find(IResourceKey* key, Core::BaseComponent*& resource) const;
    Core::BaseComponent* Get(IResourceKey* key) const;
    void Set(IResourceKey* key, Core::BaseComponent* value);
    void Add(IResourceKey* key, Core::BaseComponent* value);
    void Clear();
    NsBool Contains(IResourceKey* key) const;
    void Remove(IResourceKey* key);
    /// The number of entries of the base dictionary (excluding merged dictionaries)
    NsSize Count() const;
    /// Enumerates the entries of the base dictionary (excluding merged dictionaries)
    void EnumKeyValues(const EnumCallback& callback) const;
    //@}

    /// From IComponentInitializer
    //@{
    NsBool IsInitialized() const;
    void Init();
    //@}

    /// From INameScope
    //@{
    Core::BaseComponent* FindName(const NsChar* name) const;
    void RegisterName(const NsChar* name, Core::BaseComponent* object);
    void UnregisterName(const NsChar* name);
    void UpdateName(const NsChar* name, Core::BaseComponent* object);
    INameScope::ChangedDelegate& NameScopeChanged();
    //@}

    // Templated version of FindName
    // \remarks Asserts that returned object implements specified type
    template<class T>
    T* FindName(const NsChar* name) const
    {
        return NsStaticCast<T*>(FindName(name));
    }

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

private:
    /// Item management
    //@{
    void OnItemAdded(Core::BaseComponent* item);
    void OnItemRemoved(Core::BaseComponent* item);
    void OnAllItemsRemoved();
    //@}

    /// Tries to get an object from the map
    Core::BaseComponent* TryGet(IResourceKey* key) const;

    /// Clears all dictionary elements, including merged dictionaries
    void Reset();

    /// Load source dictionary resource
    void LoadSource();

    /// Indicates if this ResourceDictionary is read-only (loaded from a source)
    NsBool IsReadOnly() const;
    void CheckReadOnly() const;
    void CheckItemKey(IResourceKey* key, BaseComponent* item) const;

    /// Called when a dictionary is added to be merged
    void OnMergedDictionariesChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);
    void OnAddMergedDictionary(ResourceDictionary* dict);
    void OnRemoveMergedDictionary(ResourceDictionary* dict);
    void OnRemoveMergedDictionaryForMerged(ResourceDictionary* dict);

    void EnsureMergedDictionaries() const;

    friend class XamlContext;
    void SetDelayedStaticResources(DelayedStaticResources* delayedResources);
    DelayedStaticResources* GetDelayedStaticResources() const;

private:
    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    NsString mSource;
    Ptr<ResourceDictionary> mSourceDictionary;

    struct Data;
    Ptr<Data> mData;

    NS_DECLARE_REFLECTION(ResourceDictionary, BaseDictionary)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
