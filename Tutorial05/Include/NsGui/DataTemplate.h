////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DATATEMPLATE_H__
#define __GUI_DATATEMPLATE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/FrameworkTemplate.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class TriggerCollection;
class ResourceKeyType;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes the visual structure of a data object.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.datatemplate.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DataTemplate: public FrameworkTemplate
{
public:
    DataTemplate();
    ~DataTemplate();

    /// Gets or sets the type for which this DataTemplate is intended
    //@{
    ResourceKeyType* GetDataType() const;
    void SetDataType(ResourceKeyType* dataType);
    //@}
    
    /// Gets a collection of triggers that apply property values or perform actions based on one or 
    /// more conditions.
    TriggerCollection* GetTriggers() const;

protected:
    /// From FrameworkTemplate
    //@{
    void OnInit();
    TriggerCollection* GetAvailableTriggers() const;

    // NOTE: DataTemplate does not match DataType, it just tries to solve bindings against data.
    // DataType is only used to search for a valid template resource given a type of data.
    //NsBool IsValidTemplatedParent(FrameworkElement* templatedParent, BaseComponent* dataContext) const;
    //@}

private:
    void EnsureTriggers() const;

private:
    Ptr<ResourceKeyType> mDataType;
    mutable Ptr<TriggerCollection> mTriggers;

    NS_DECLARE_REFLECTION(DataTemplate, FrameworkTemplate)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif