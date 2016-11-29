////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LOGICALTREEHELPER_H__
#define __GUI_LOGICALTREEHELPER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class FrameworkElement;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// LogicalTreeHelper. Contains static methods that are useful for performing common tasks with
/// nodes in a logical tree.
///
/// TODO: [sfernandez]
///     WPF has two types of element nodes in the logical tree: FrameworkElement and
///     FrameworkContentElement. The LogicalTreeHelper class exists to help manage the logical tree
///     without knowing about that. We don't know if FrameworkContentElement nodes will be
///     necessary, maybe this class will disappear.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API LogicalTreeHelper
{
    /// Returns the logical parent element of the specified element
    static FrameworkElement* GetParent(const FrameworkElement* element);

    /// Returns the number of children that a parent element contains
    static NsSize GetChildrenCount(const FrameworkElement* element);

    /// Returns the child logical object of a parent at the specified index
    static Core::BaseComponent* GetChild(const FrameworkElement* element, NsSize index);

    /// Search for an element with passed name down the logical tree
    static FrameworkElement* FindLogicalNode(const FrameworkElement* element, const NsChar* name);
};

}
}

#endif
