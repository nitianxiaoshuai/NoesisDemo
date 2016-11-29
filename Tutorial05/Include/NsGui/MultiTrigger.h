////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MULTITRIGGER_H__
#define __GUI_MULTITRIGGER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/BaseTrigger.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class BaseSetter;
class Setter;
class Condition;
template<class T> class TypedCollection;
//@}

typedef Noesis::Gui::TypedCollection<Noesis::Gui::Condition> ConditionCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a trigger that applies property values or performs actions when a set of conditions
/// are satisfied.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.multitrigger.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API MultiTrigger: public BaseTrigger
{
public:
    MultiTrigger();
    ~MultiTrigger();
    
    /// Gets a collection of Condition objects. Changes to property values are applied when all of 
    /// the conditions in the collection are met.
    ConditionCollection* GetConditions() const;
    
    /// Gets a collection of Setter objects, which describe the property values to apply when all 
    /// of the conditions of the MultiTrigger are met.
    BaseSetterCollection* GetSetters() const;

    /// From BaseTrigger
    //@{
    Core::BaseComponent* FindValue(FrameworkElement* target, FrameworkElement* nameScope,
        DependencyObject* object, const DependencyProperty* dp, NsBool skipSourceName,
        NsBool skipTargetName);
    void Invalidate(FrameworkElement* target, FrameworkElement* nameScope, NsBool skipSourceName,
        NsBool skipTargetName, NsUInt8 priority);
    void Invalidate(FrameworkElement* target, FrameworkElement* nameScope,
        FrameworkElement* changedObject, const DependencyProperty* changedProperty,
        const void* oldValue, const void* newValue, NsBool skipSourceName, NsBool skipTargetName,
        NsUInt8 priority);
    void FreezeValues();
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

private:
    NsBool Matches(FrameworkElement* target, FrameworkElement* nameScope, DependencyObject* object,
        const DependencyProperty* dp, NsBool skipSourceName, NsBool skipSelf) const;
    NsBool Matches(FrameworkElement* target, FrameworkElement* nameScope,
        FrameworkElement* changedObject, const DependencyProperty* changedProperty,
        const void* changedValue, NsBool skipSourceName) const;

    void EnsureConditions() const;
    void EnsureSetters() const;

private:
    mutable Ptr<ConditionCollection> mConditions;
    mutable Ptr<BaseSetterCollection> mSetters;

    NS_DECLARE_REFLECTION(MultiTrigger, BaseTrigger)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
