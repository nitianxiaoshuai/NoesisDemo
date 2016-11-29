////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_UIELEMENTCOLLECTION_H__
#define __GUI_UIELEMENTCOLLECTION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/VisualCollection.h>
#include <NsGui/UIElement.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
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
/// UIElementCollection. Represents a collection of UIElements.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API UIElementCollection: public VisualCollection
{
public:
    /// Default constructor
    UIElementCollection();

    /// Constructor
    UIElementCollection(Visual* visualParent, FrameworkElement* logicalParent);

    /// Destructor
    ~UIElementCollection();

    /// Gets or sets logical parent
    //@{
    FrameworkElement* GetLogicalParent() const;
    void SetLogicalParent(FrameworkElement* logicalParent);
    //@}

protected:
    /// From Collection
    //@{
    void OnItemAdded(Core::BaseComponent* item, NsSize index);
    void OnItemRemoved(Core::BaseComponent* item, NsSize index);
    void CheckItem(BaseComponent* item) const;
    //@}

private:
    void InvalidateVisualParentMeasure();
    void ResetChildren();

private:
    FrameworkElement* mLogicalParent;

    NS_DECLARE_REFLECTION(UIElementCollection, VisualCollection)
};

}
}

#endif
