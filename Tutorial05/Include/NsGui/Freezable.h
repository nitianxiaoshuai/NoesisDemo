////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FREEZABLE_H__
#define __GUI_FREEZABLE_H__


#include <Noesis.h>
#include <NsGui/DependencySystemApi.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/FreezableEventReason.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines an object that has a modifiable state and a read-only (frozen) state. Classes that 
/// derive from Freezable provide detailed change notification, can be made immutable, and can 
/// clone themselves.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_DEPENDENCYSYSTEM_API Freezable: public DependencyObject
{
public:
    Freezable();
    virtual ~Freezable() = 0;

    /// Gets a value that indicates whether the object can be made unmodifiable.
    NsBool CanFreeze() const;
    
    ///  Gets a value that indicates whether the object is currently modifiable.
    NsBool IsFrozen() const;
    
    /// Makes the current object unmodifiable and sets its IsFrozen property to true.
    void Freeze();

    /// Creates a modifiable clone of the Freezable, making deep copies of the object's values. 
    /// When copying the object's dependency properties, this method copies expressions (which 
    /// might no longer resolve) but not animations or their current values.
    /// The cloned Freezable::IsFrozen property is false even if the source's IsFrozen property is 
    /// true.
    /// \note The cloned element is not initialized
    Ptr<Freezable> Clone() const;
    
    /// Creates a modifiable clone (deep copy) of the Freezable using its current values.
    /// The cloned object's IsFrozen property is false even if the source's IsFrozen property is 
    /// true.
    /// \note The cloned element is not initialized
    Ptr<Freezable> CloneCurrentValue() const;
    
    /// Creates a frozen copy of the Freezable, using base (non-animated) property values. Because 
    /// the copy is frozen, any frozen sub-objects are copied by reference.
    /// The copy's IsFrozen property is set to true.
    /// Throws if the Freezable cannot be frozen because it contains expressions or animated 
    /// properties.
    /// \note The cloned element is not initialized
    Ptr<Freezable> GetAsFrozen() const;

    /// Creates a frozen copy of the Freezable using current property values. Because the copy is 
    /// frozen, any frozen sub-objects are copied by reference.
    /// The copy's IsFrozen property is set to true.
    /// \note The cloned element is not initialized
    Ptr<Freezable> GetCurrentValueAsFrozen() const;
    
    /// Occurs when the Freezable or an object it contains is modified.
    typedef Core::Delegate<void (Freezable*, FreezableEventReason)> FreezableChangedEvent;
    FreezableChangedEvent& Changed();

protected:
    /// Returns true when initializing a frozen object
    NsBool IsInitializingFrozen() const;

    /// Makes the Freezable object unmodifiable or tests whether it can be made unmodifiable.
    virtual NsBool FreezeCore(NsBool isChecking);

    /// Makes the instance a clone (deep copy) of the specified Freezable using base (non-animated) 
    /// property values.
    virtual void CloneCore(const Freezable* source);

    /// Makes the instance a modifiable clone (deep copy) of the specified Freezable using current 
    /// property values.
    virtual void CloneCurrentValueCore(const Freezable* source);

    /// Makes the instance a frozen clone of the specified Freezable using base (non-animated) 
    /// property values.
    virtual void GetAsFrozenCore(const Freezable* source);

    /// Makes the current instance a frozen clone of the specified Freezable. If the object has 
    /// animated dependency properties, their current animated values are copied.
    virtual void GetCurrentValueAsFrozenCore(const Freezable* source);

    /// Called at the end of CloneCommon (this implies this method is called at the end of 
    /// CloneCore, CloneCurrentValueCore, GetAsFrozenValue and GetCurrentValueAsFrozenCore
    virtual void CloneCommonCore(const Freezable* source);

    /// When implemented in a derived class, creates a new instance of the Freezable derived class.
    virtual Ptr<Freezable> CreateInstanceCore() const;

    /// Called when the current Freezable object is modified. 
    virtual void OnChanged(FreezableEventReason reason);

    /// Raises modification event
    void RaiseEvent(FreezableEventReason reason);

    /// From DependencyObject 
    //@{
    void OnInit();
    void OnPostInit();
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& e);
    //@}

private:
    Ptr<Freezable> CreateInstance() const;
    void CloneCommon(const Freezable* source, NsBool useBaseValue, NsBool cloneFreezables);

private:
    union
    {
        NsUInt8 mAllFlags;
        struct
        {
            NsBool isFrozen:1;
            NsBool isFrozenCache:2;
        } mFlags;
    };
    
    FreezableChangedEvent mFreezableChangedEvent;

    NS_DECLARE_REFLECTION(Freezable, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif