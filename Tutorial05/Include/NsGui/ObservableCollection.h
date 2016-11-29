////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_OBSERVABLECOLLECTION_H__
#define __GUI_OBSERVABLECOLLECTION_H__


#include <Noesis.h>
#include <NsGui/Collection.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a dynamic data collection that provides notifications when items get added or
/// removed. It is frequently used in data binding to display a collection of records within an
/// *ItemsControl* such as a *ListBox*, *ListView* or *TreeView*.
///
/// .. code-block:: xml
///
///     <ListBox Width="200"
///         ItemsSource="{Binding Source={StaticResource NameListData}}"
///         ItemTemplate="{StaticResource NameItemTemplate}" />
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class ObservableCollection: public Collection
{
public:
    T* Get(NsSize index) const;
    void Set(NsSize index, T* item);
    NsSize Add(T* item);
    NsBool Contains(T* item) const;
    NsInt IndexOf(T* item) const;
    void Insert(NsSize index, T* item);
    void Remove(T* item);

private:
    using Collection::Set;
    using Collection::Add;
    using Collection::Contains;
    using Collection::IndexOf;
    using Collection::Insert;
    using Collection::Remove;

    NS_IMPLEMENT_INLINE_REFLECTION_(ObservableCollection, Collection)
};

}
}


#include <NsGui/ObservableCollection.inl>


#endif
