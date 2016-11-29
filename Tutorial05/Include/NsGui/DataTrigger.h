////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DATATRIGGER_H__
#define __GUI_DATATRIGGER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/BaseTrigger.h>
#include <NsGui/BindingListener.h>
#include <NsCore/Set.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class BaseSetter;
class BaseBinding;
template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a trigger that applies property values or performs actions when the bound data meets
/// a specified condition.
///
/// Style, ControlTemplate, and DataTemplate all have a triggers collection. A DataTrigger
/// allows you to set property values when the property value of the data object matches a
/// specified Value. For example, if you are displaying a list of *Employee* objects, you may want
/// the foreground color to be different based on each *Employee's* current attendance. In some
/// scenarios it may be more suitable to create a converter or to use a DataTemplateSelector.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.datatrigger.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DataTrigger: public BaseTrigger
{
public:
    /// Constructor
    DataTrigger();

    /// Destructor
    ~DataTrigger();

    /// Gets or sets the binding that produces the property value of the data object.
    //@{
    BaseBinding* GetBinding() const;
    void SetBinding(BaseBinding* binding);
    //@}

    /// Gets a collection of Setter objects, which describe the property values to apply when the
    /// data item meets the specified condition.
    //@{
    BaseSetterCollection* GetSetters() const;
    //@}

    /// Gets or sets the value to be compared with the property value of the data object.
    //@{
    Core::BaseComponent* GetValue() const;
    void SetValue(Core::BaseComponent* value);
    //@}

    /// From BaseTrigger
    //@{
    void RegisterBindings(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipTargetName, NsUInt8 priority);
    void UnregisterBindings(FrameworkElement* target);
    Core::BaseComponent* FindValue(FrameworkElement* target, FrameworkElement* nameScope,
        DependencyObject* object, const DependencyProperty* dp, NsBool skipSourceName,
        NsBool skipTargetName);
    void Invalidate(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipSourceName, NsBool skipTargetName, NsUInt8 priority);
    void FreezeValues();
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

private:
    void EnsureSetters() const;

    void ForceInvalidate(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipTargetName, NsBool fireEnterActions, NsUInt8 priority);

    NsBool Matches(FrameworkElement* target) const;

private:
    Ptr<BaseBinding> mBinding;
    Ptr<BaseComponent> mValue;
    mutable Ptr<BaseSetterCollection> mSetters;

    class Listener: public BindingListener
    {
    public:
        Listener(DataTrigger* dt, FrameworkElement* t, FrameworkElement* ns, NsBool sk, NsUInt8 p);

        struct Comparer;
        NsBool operator<(const Listener& other) const;
        NsBool operator==(const Listener& other) const;

    protected:
        const BindingListenerData* GetData() const;
        Core::BaseComponent* GetValue() const;
        BaseBinding* GetBinding() const;
        void Invalidate(FrameworkElement* target, FrameworkElement* nameScope,
            NsBool skipTargetName, NsBool fireEnterActions, NsUInt8 priority) const;

    private:
        DataTrigger* trigger;
        BindingListenerData data;
    };

    typedef NsSet<Listener> Listeners;
    Listeners mListeners;

    NS_DECLARE_REFLECTION(DataTrigger, BaseTrigger)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}

#endif
