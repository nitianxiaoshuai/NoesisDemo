////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BINDINGLISTENER_H__
#define __GUI_BINDINGLISTENER_H__


#include <Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/Delegate.h>
#include <NsCore/Vector.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Core
{
class BaseComponent;
class TypeProperty;
class Type;
}
namespace Gui
{
class DependencyObject;
class DependencyProperty;
class FrameworkElement;
class CollectionView;
class BaseBinding;
NS_INTERFACE IResourceKey;
NS_INTERFACE INotifyPropertyChanged;
struct PathElement;
struct DependencyPropertyChangedEventArgs;
struct AncestorNameScopeChangedArgs;
struct PropertyChangedEventArgs;
struct NotifyCollectionChangedEventArgs;
struct NotifyDictionaryChangedEventArgs;
struct EventArgs;
typedef Core::Delegate<Core::BaseComponent* ()> GetValueCallback;
typedef Core::Delegate<void (FrameworkElement* target, FrameworkElement* nameScope,
    NsBool skipTargetName, NsBool fireEnterActions, NsUInt8 priority)> InvalidateCallback;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// BindingListener shared data
////////////////////////////////////////////////////////////////////////////////////////////////////
struct BindingListenerData
{
    FrameworkElement* target;
    FrameworkElement* nameScope;
    NsBool skipTargetName;
    NsUInt8 priority;

    BindingListenerData(FrameworkElement* t, FrameworkElement* ns, NsBool sk, NsUInt8 p);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Used by DataTriggers and MultiDataTriggers to listen to Binding changes
////////////////////////////////////////////////////////////////////////////////////////////////////
class BindingListener
{
public:
    /// Constructor
    BindingListener();

    /// Destructor
    virtual ~BindingListener() = 0;

    /// Tries to resolve binding and subscribes to binding changes
    void Register();

    /// Unsubscribes from binding changes
    void Unregister();

    /// Indicates if current binding 
    NsBool Matches() const;

protected:
    virtual const BindingListenerData* GetData() const = 0;
    virtual Core::BaseComponent* GetValue() const = 0;
    virtual BaseBinding* GetBinding() const = 0;
    virtual void Invalidate(FrameworkElement* target, FrameworkElement* nameScope,
        NsBool skipTargetName, NsBool fireEnterActions, NsUInt8 priority) const = 0;

private:
    void Initialize();
    void Shutdown();

    void AddPathElement(const PathElement& element, void* context);

    struct WeakPathElement;
    void RegisterNotification(const WeakPathElement& element);
    void UnregisterNotification(const WeakPathElement& element);

    void SetPathUnresolved();
    NsBool IsPathResolved() const;

    NsBool TryConvertTriggerValue();

    NsBool MatchesOnReset();
    NsBool MatchesValues(const Ptr<Core::BaseComponent>& val1,
        const Ptr<Core::BaseComponent>& val2) const;
    void Matches(NsBool& matchesOldValue, NsBool& matchesNewValue, NsBool reevaluate,
        const Ptr<Core::BaseComponent>& newValue = Ptr<Core::BaseComponent>::Null());

    Ptr<Core::BaseComponent> GetValue(const WeakPathElement& element) const;
    Ptr<Core::BaseComponent> GetValue(const WeakPathElement& element,
        const Core::Type*& valueType) const;
    Ptr<Core::BaseComponent> GetSourceValue(const WeakPathElement& element,
        const Core::Type*& valueType) const;
    Ptr<Core::BaseComponent> GetConvertedValue(const Ptr<Core::BaseComponent>& value) const;
    NsBool UpdateSourceValue(const Ptr<Core::BaseComponent>& newValue, const Core::Type* type);

    void OnAncestorChanged(FrameworkElement* ancestor);
    void OnNameScopeChanged(FrameworkElement* sender,
        const AncestorNameScopeChangedArgs& args);
    void OnTargetContextChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);

    void InvalidateSource();
    void Invalidate(NsBool matchesOldValue, NsBool matchesNewValue);

    void OnObjectPropertyChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);
    void OnNotifyPropertyChanged(Core::BaseComponent* sender,
        const PropertyChangedEventArgs& args);

    void OnCollectionChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);
    void OnCollectionReset(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);

    void OnDictionaryChanged(Core::BaseComponent* sender,
        const NotifyDictionaryChangedEventArgs& args);
    void OnDictionaryReset(Core::BaseComponent* sender,
        const NotifyDictionaryChangedEventArgs& args);

    void OnCurrentChanged(Core::BaseComponent* sender, const EventArgs& args);

    void OnTargetDestroyed(DependencyObject* sender);
    void OnSourceDestroyed(DependencyObject* sender);

private:
    Core::BaseComponent* mSource;

    struct WeakPathElement
    {
        Core::BaseComponent* source;
        CollectionView* collection;
        const Core::TypeProperty* property;
        const DependencyProperty* dp;
        NsInt index;
        Ptr<IResourceKey> key;

        static WeakPathElement Self(Core::BaseComponent* source);
    };

    // Resolved path elements
    NsVector<WeakPathElement> mPathElements;

    // Last source value
    Ptr<Core::BaseComponent> mSourceValue;
    const Core::Type* mSourceType;

    // Trigger Value converted to the type of the last path property or object
    Ptr<Core::BaseComponent> mTriggerValue;

    NS_DECLARE_REFLECTION(BindingListener, Core::NoParent)
};

}
}

#endif
