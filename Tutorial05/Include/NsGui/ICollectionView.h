////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ICOLLECTIONVIEW_H__
#define __GUI_ICOLLECTIONVIEW_H__


#include <Noesis.h>
#include <NsCore/Interface.h>
#include <NsGui/Events.h>


namespace Noesis
{
// Forward declarations
//@{
namespace Core
{
class BaseComponent;
}
//@}
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ICollectionView: Enables collections to have the functionalities of current record management, 
/// custom sorting, filtering, and grouping. 
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE ICollectionView: public Core::Interface
{
    /// Gets a value that indicates whether this view supports filtering via the Filter property
    virtual NsBool CanFilter() const = 0;

    /// Gets a value that indicates whether this view supports grouping via GroupDescriptions 
    virtual NsBool CanGroup() const = 0;

    /// Gets a value that indicates whether this view supports sorting via SortDescriptions 
    virtual NsBool CanSort() const = 0;

    /// Returns a value that indicates whether a given item belongs to this collection view
    virtual NsBool Contains(Core::BaseComponent* item) const = 0;

    /// Gets the current item in the view
    virtual Core::BaseComponent* CurrentItem() const = 0;

    /// Gets the ordinal position of the CurrentItem within the view
    virtual NsInt CurrentPosition() const = 0;

    /// Gets a value that indicates whether the CurrentItem of the view is beyond the end of the 
    /// collection
    virtual NsBool IsCurrentAfterLast() const = 0;

    /// Gets a value that indicates whether the CurrentItem of the view is beyond the beginning of 
    /// the collection
    virtual NsBool IsCurrentBeforeFirst() const = 0;

    /// Returns a value that indicates whether the resulting view is empty. 
    virtual NsBool IsEmpty() const = 0;

    /// Move current item methods
    //@{
    virtual NsBool MoveCurrentTo(Core::BaseComponent* item) = 0;
    virtual NsBool MoveCurrentToFirst() = 0;
    virtual NsBool MoveCurrentToLast() = 0;
    virtual NsBool MoveCurrentToNext() = 0;
    virtual NsBool MoveCurrentToPosition(NsInt position) = 0;
    virtual NsBool MoveCurrentToPrevious() = 0;
    //@}

    virtual void Refresh() = 0;

    virtual EventHandler& CurrentChanged() = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(ICollectionView, Core::Interface)
};

}
}


#endif
