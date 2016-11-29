////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASETRIGGER_H__
#define __GUI_BASETRIGGER_H__


#include <Noesis.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/CoreApi.h>

#include <NsCore/Set.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class FrameworkElement;
class TriggerCollection;
class TriggerAction;
class BaseSetter;
template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::TriggerAction> TriggerActionCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for specifying a conditional value within a Style object.
///
/// The styling and templating model allows you to specify triggers within your Style,
/// ControlTemplate, and DataTemplate. Essentially, TriggerBase is the base class for
/// objects that allow you to apply changes when certain conditions (such as when a certain
/// property value becomes true, or when an event occurs) are satisfied.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.triggerbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseTrigger: public DependencyObject, public IUITreeNode
{
public:
    /// Constructor
    BaseTrigger();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~BaseTrigger() = 0;

    /// Gets a collection of TriggerAction objects to apply 
    /// when the trigger object becomes active. This property does not apply to the EventTrigger
    /// class
    TriggerActionCollection* GetEnterActions() const;

    /// Gets a collection of TriggerAction objects to apply
    /// when the trigger object becomes inactive. This property does not apply to the EventTrigger
    /// class
    TriggerActionCollection* GetExitActions() const;

    // Invoke enter actions
    void FireEnterActions(FrameworkElement* target, FrameworkElement* nameScope);

    // Invoke exit actions
    void FireExitActions(FrameworkElement* target, FrameworkElement* nameScope);

    // Register against binding changes
    virtual void RegisterBindings(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipTargetName, NsUInt8 priority);

    // Unregister from binding changes
    virtual void UnregisterBindings(FrameworkElement* target);

    // Registers against events
    virtual void RegisterEvents(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipSourceName);

    // Unregisters from events
    virtual void UnregisterEvents(FrameworkElement* target, NsBool skipSourceName);

    // Tests if this trigger will be active for the specified object and looks for a setter value
    // that can be applied to the specified object and property
    // \return UnsetValue if trigger can't be applied or a valid setter was not found
    virtual Core::BaseComponent* FindValue(FrameworkElement* target, FrameworkElement* nameScope,
        DependencyObject* object, const DependencyProperty* dp, NsBool skipSourceName,
        NsBool skipTargetName);

    // Applies setters if trigger conditions are fulfilled
    virtual void Invalidate(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipSourceName, NsBool skipTargetName, NsUInt8 priority);

    // Applies setters if trigger changes its state after the specified property change
    virtual void Invalidate(FrameworkElement* target, FrameworkElement* nameScope,
        FrameworkElement* changedObject, const DependencyProperty* changedProperty,
        const void* oldValue, const void* newValue, NsBool skipSourceName, NsBool skipTargetName,
        NsUInt8 priority);

    // Freezes values in trigger setters
    virtual void FreezeValues();
    static void FreezeValues(BaseSetterCollection* setters);

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

protected:
    static Core::BaseComponent* FindValueInSetters(BaseSetterCollection* setters,
        FrameworkElement* target, FrameworkElement* nameScope, DependencyObject* object,
        const DependencyProperty* dp, NsBool skipTargetName);
    static void InvalidateSetters(BaseSetterCollection* setters, FrameworkElement* target,
        FrameworkElement* nameScope, NsBool skipTargetName, NsUInt8 priority);

    /// From DependencyObject
    //@{
    void OnInit();
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue);
    //@}

private:
    /// Base classes are non-copyable objects
    //@{
    BaseTrigger(const BaseTrigger&);
    BaseTrigger& operator=(const BaseTrigger&);
    //@}

    void EnsureEnterActions() const;
    void EnsureExitActions() const;

private:
    IUITreeNode* mOwner;

    mutable Ptr<TriggerActionCollection> mEnterActions;
    mutable Ptr<TriggerActionCollection> mExitActions;

    NS_DECLARE_REFLECTION(BaseTrigger, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
