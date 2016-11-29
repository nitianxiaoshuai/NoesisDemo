////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BINDINGEXPRESSION_H__
#define __GUI_BINDINGEXPRESSION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsGui/CoreApi.h>
#include <NsGui/PropertyPath.h>
#include <NsGui/Binding.h>
#include <NsGui/BaseBindingExpression.h>


NS_IFORWARD(Gui, IValueConverter)
NS_IFORWARD(Gui, IResourceKey)
NS_IFORWARD(Gui, INameScope)
NS_CFORWARD(Gui, DependencyObject)
NS_CFORWARD(Gui, DependencyProperty)
NS_CFORWARD(Gui, FrameworkElement)
NS_CFORWARD(Gui, CollectionView)
NS_SFORWARD(Gui, PropertyChangedEventArgs)
NS_SFORWARD(Gui, NotifyDictionaryChangedEventArgs)
NS_SFORWARD(Gui, NotifyCollectionChangedEventArgs)
NS_SFORWARD(Gui, DependencyPropertyChangedEventArgs)
NS_SFORWARD(Gui, RoutedEventArgs)
NS_SFORWARD(Gui, EventArgs)
NS_SFORWARD(Gui, AncestorNameScopeChangedArgs)
NS_SFORWARD(Gui, NameScopeChangedArgs)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// BindingExpression. Provides high-level access to the definition of a binding, which connects the
/// properties of binding target objects (UI elements), and any data source (for example, a
/// database, an XML file, or any object that contains data).
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BindingExpression: public BaseBindingExpression
{
public:
    ~BindingExpression();

    /// Binding from which this expression was created
    /// \prop
    Binding* GetParentBinding() const;

    /// From BaseBindingExpression
    //@{
    void UpdateTarget() const;
    void UpdateSource() const;
    //@}

    /// From IExpression
    //@{
    Ptr<Core::BaseComponent> Evaluate() const;
    Ptr<IExpression> Reapply(DependencyObject* targetObject,
        const DependencyProperty* targetProperty) const;
    BeforeSetAction BeforeSet(DependencyObject* obj, const DependencyProperty* prop, 
        const void* value, NsBool valueChanged);
    void AfterSet(DependencyObject* obj, const DependencyProperty* prop, 
        const void* value, NsBool valueChanged);
    //@}

private:
    friend class Binding;
    BindingExpression(BaseBinding* binding, DependencyObject* targetObject,
        const DependencyProperty* targetProperty);

    NsBool IsAttached() const;

    void Register();
    void Unregister();

    void RegisterScope();
    void UnregisterScope();

    void Initialize();
    void Shutdown();

    void AddPathElement(const PathElement& element, void* context);

    void RegisterSource();
    void UnregisterSource();

    struct WeakPathElement;
    NsUInt32 GetRegisteredFlags(NsSize end, const WeakPathElement& element) const;
    void RegisterNotification(const WeakPathElement& element, NsUInt32 registeredFlags);
    void UnregisterNotification(const WeakPathElement& element, NsUInt32 registeredFlags);
    NsBool IsSelf(const WeakPathElement& element, NsSize numElements) const;
    Ptr<BaseComponent> GetValue(const WeakPathElement& element, const Core::Type*& valueType) const;

    /// Checks if a converter is needed, creating one when required
    NsBool CheckConverter(const Core::Type* sourceType, Core::BaseComponent* sourceVal) const;

    void UpdateSourceInternal(const void* value) const;
    void TransferSourceValue(const void* value) const;
    Ptr<Core::BaseComponent> GetSourceValue() const;

    void InvalidateSource(NsBool invalidateTargetProperty = true);

    // Source change notification
    //@{
    void OnDataContextChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);

    void OnTargetAncestorChanged(FrameworkElement* oldParent);

    void OnAncestorNameScopeChanged(FrameworkElement* sender,
        const AncestorNameScopeChangedArgs& args);

    void OnSourceNameScopeChanged(INameScope* sender, const NameScopeChangedArgs& args);
    //@}

    // Property change notifications
    //@{
    void OnDependencyPropertyChanged(Core::BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);

    void OnNotifyPropertyChanged(Core::BaseComponent* sender, const PropertyChangedEventArgs& e);

    void OnCollectionChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);
    void OnCollectionReset(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);

    void OnDictionaryChanged(Core::BaseComponent* sender,
        const NotifyDictionaryChangedEventArgs& args);
    void OnDictionaryReset(Core::BaseComponent* sender,
        const NotifyDictionaryChangedEventArgs& args);

    void OnCurrentChanged(Core::BaseComponent* sender, const EventArgs& args);
    //@}

    /// Event notification
    //@{
    void OnTargetLostFocus(Core::BaseComponent*, const RoutedEventArgs& args);
    //@}

    // HACK #884
    //@{
    void OnTargetDestroyed(DependencyObject* object);
    void OnSourceDestroyed(DependencyObject* object);
    //@}

    NsBool IsTargetAlive() const;

private:
    /// Source object for the expression
    BaseComponent* mSource;
    INameScope* mNameScope;

    struct WeakPathElement
    {
        Core::BaseComponent* source;
        CollectionView* collection;
        const Core::TypeProperty* property;
        const DependencyProperty* dp;
        NsInt index;
        Ptr<IResourceKey> key;
    };

    /// List of objects to access final source property
    NsVector<WeakPathElement> mPaths;

    /// Effective binding mode (never set to Default because the proper value is retrieved from 
    /// metadata)
    BindingMode mEffectiveBindingMode;

    /// Value converter is used when source and target property types are different, or when set by
    /// the user in the Converter field of the Binding class.
    mutable Ptr<IValueConverter> mEffectiveConverter;

    /// The effective fallback value to assign in case of fail in the binding
    Ptr<BaseComponent> mEffectiveFallback;
    
    /// The effective UpdateSourceTrigger value to use
    UpdateSourceTrigger mEffectiveUpdateSourceTrigger;

    union
    {
        mutable struct
        {
            NsBool fullReevaluationNeeded : 1;
            NsBool pathPartiallySolved : 1;
            NsBool sourceRegistered : 1;
            NsBool targetDestroyRegistered : 1;
            NsBool targetLostFocusRegistered : 1;
            NsBool targetAncestorChangedRegistered : 1;
            NsBool targetDataContextChangedRegistered : 1;
            NsBool targetAncestorNameScopeChangedRegistered : 1;
            NsBool propertyChangeRegistered : 1;
            NsBool updatingSource : 1;
            NsBool transferingSourceValue : 1;
            NsBool doNothing : 1;
            NsBool checkConverter : 1;
            NsBool oneTimeEvaluated : 1;
        } mFlags;

        // To quickly set all flags to 0
        NsUInt32 mAllFlags;
    };

    NS_DECLARE_REFLECTION(BindingExpression, BaseBindingExpression)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
