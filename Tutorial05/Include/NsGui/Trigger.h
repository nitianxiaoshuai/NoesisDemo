////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRIGGER_H__
#define __GUI_TRIGGER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/String.h>
#include <NsGui/BaseTrigger.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class BaseSetter;
template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a trigger that applies property values or performs actions conditionally.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.trigger.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Trigger: public BaseTrigger
{
public:
    /// Constructor
    Trigger();

    /// Destructor
    ~Trigger();

    /// Gets or sets the property that returns the value that is compared with the Value property of
    /// the trigger. The comparison is a reference equality check.
    //@{
    const DependencyProperty* GetProperty() const;
    void SetProperty(const DependencyProperty* property);
    //@}

    /// Gets a collection of Setter objects, which describe the property values to apply when the
    /// specified condition has been met.
    //@{
    BaseSetterCollection* GetSetters() const;
    //@}

    /// Gets or sets the name of the object with the property that causes the associated setters 
    /// to be applied.
    //@{
    const NsChar* GetSourceName() const;
    void SetSourceName(const NsChar* name);
    //@}

    /// Gets or sets the value to be compared with the property value of the element. The
    /// comparison is a reference equality check.
    //@{
    Core::BaseComponent* GetValue() const;
    void SetValue(Core::BaseComponent* value);
    //@}

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

    void EnsureSetters() const;

private:
    NsString mSourceName;
    const DependencyProperty* mProperty;
    Ptr<BaseComponent> mValue;
    mutable Ptr<BaseSetterCollection> mSetters;

    NS_DECLARE_REFLECTION(Trigger, BaseTrigger)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}

#endif
