////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MULTIDATATRIGGER_H__
#define __GUI_MULTIDATATRIGGER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/BaseTrigger.h>
#include <NsGui/BindingListener.h>
#include <NsCore/Set.h>
#include <NsCore/Vector.h>

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
typedef Noesis::Gui::TypedCollection<Noesis::Gui::Condition> ConditionCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a trigger that applies property values or performs actions when the bound data meet
/// a set of conditions.
///
/// A MultiDataTrigger object is similar to a MultiTrigger, except that the conditions of a
/// MultiDataTrigger are based on property values of bound data instead of those of a UIElement.
/// In a MultiDataTrigger, a condition is met when the property value of the data item matches the
/// specified Value. You can then use setters or the *EnterActions* and *ExitActions* properties to
/// apply changes or start actions when all of the conditions are met.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.multidatatrigger.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API MultiDataTrigger: public BaseTrigger
{
public:
    /// Constructor
    MultiDataTrigger();

    /// Destructor
    ~MultiDataTrigger();

    /// Gets a collection of Condition objects. Changes to property values are applied when all of
    /// the conditions in the collection are met.
    ConditionCollection* GetConditions() const;

    /// Gets a collection of Setter objects, which describe the property values to apply when all
    /// of the conditions of the MultiTrigger are met.
    BaseSetterCollection* GetSetters() const;

    /// From BaseTrigger
    //@{
    void RegisterBindings(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipTargetName, NsUInt8 priority);
    void UnregisterBindings(FrameworkElement* target);
    Core::BaseComponent* FindValue(FrameworkElement* target, FrameworkElement* nameScope,
        DependencyObject* object, const DependencyProperty* dp, NsBool skipSourceName,
        NsBool skipTargetName);
    void Invalidate(FrameworkElement* target, FrameworkElement* nameScope, NsBool skipSourceName,
        NsBool skipTargetName, NsUInt8 priority);
    void FreezeValues();
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

private:
    void EnsureConditions() const;
    void EnsureSetters() const;

    void ForceInvalidate(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipTargetName, NsBool fireEnterActions, NsUInt8 priority);

    NsBool Matches(FrameworkElement* target) const;

private:
    mutable Ptr<ConditionCollection> mConditions;
    mutable Ptr<BaseSetterCollection> mSetters;

    class Listener
    {
    public:
        Listener(MultiDataTrigger* dt, FrameworkElement* t, FrameworkElement* ns, NsBool sk,
            NsUInt8 p);

        struct Comparer;
        NsBool operator<(const Listener& other) const;
        NsBool operator==(const Listener& other) const;

        void Register();
        void Unregister();

        NsBool Matches() const;

    private:
        MultiDataTrigger* trigger;
        BindingListenerData data;

        class ConditionListener: public BindingListener
        {
        public:
            ConditionListener(Listener* listener, Condition* c);

        protected:
            const BindingListenerData* GetData() const;
            Core::BaseComponent* GetValue() const;
            BaseBinding* GetBinding() const;
            void Invalidate(FrameworkElement* target, FrameworkElement* nameScope,
                NsBool skipTargetName, NsBool fireEnterActions, NsUInt8 priority) const;

        private:
            Listener* listener;
            Condition* condition;
        };

        NsVector<ConditionListener> conditions;
    };

    typedef NsSet<Listener> Listeners;
    Listeners mListeners;

    NS_DECLARE_REFLECTION(MultiDataTrigger, BaseTrigger)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
