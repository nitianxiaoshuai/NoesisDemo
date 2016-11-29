////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #952]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEBINDING_H__
#define __GUI_BASEBINDING_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/String.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IMarkupExtension.h>
#include <NsGui/IComponentInitializer.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines the common features for Binding.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.data.bindingbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseBinding: public Core::BaseComponent, public IMarkupExtension,
    public IComponentInitializer
{
public:
    /// Constructor
    BaseBinding();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~BaseBinding() = 0;

    /// Gets or sets the value to use when the binding is unable to return a value
    //@{
    Core::BaseComponent* GetFallbackValue() const;
    void SetFallbackValue(Core::BaseComponent* value);
    //@}

    /// Gets or sets a string that specifies how to format the binding if it displays the bound 
    /// value as a string.
    ///
    /// Examples:
    ///
    /// .. code-block:: xml
    ///
    ///     <TextBlock Text="{Binding Amount, StringFormat=F2}" />
    ///     <TextBlock Text="{Binding Amount, StringFormat={}{0:F2}}" />
    ///     <TextBlock Text="{Binding Amount, StringFormat=Value is {0:F2} units}" />
    ///
    //@{
    const NsChar* GetStringFormat() const;
    void SetStringFormat(const NsChar* format);
    //@}

    /// From IComponentInitializer
    //@{
    NsBool IsInitialized() const;
    void Init();
    //@}

protected:
    virtual void OnInit();
    void CheckSealed() const;

protected:
    /// Indicates if this binding is unmodifiable. The binding becomes sealed the first time a
    /// binding expression is generated
    NsBool mSealed;

private:
    /// Base classes are non-copyable objects
    //@{
    BaseBinding(const BaseBinding&);
    BaseBinding& operator=(const BaseBinding&);
    //@}

private:
    /// Fallback value to return when the binding cannot be resolved
    Ptr<Core::BaseComponent> mFallbackValue;
    NsString mStringFormat;
    NsBool mIsInitialized;

    NS_DECLARE_REFLECTION(BaseBinding, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
