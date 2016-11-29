////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DECORATOR_H__
#define __GUI_DECORATOR_H__


#include <Noesis.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a base class for elements that apply effects onto or around a single child
/// element, such as Border or Viewbox.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.decorator.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Decorator: public FrameworkElement
{
public:
    /// Constructor
    Decorator(NsBool logicalChild = true);

    /// Destructor
    ~Decorator();

    /// Gets or sets child element
    //@{
    UIElement* GetChild() const;
    void SetChild(UIElement* child);
    //@}

protected:
    // Child property value changed event
    virtual void OnChildChanged(UIElement* oldChild, UIElement* newChild);

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    //@}

private:
    /// Indicates if child is also logical
    NsBool mIsLogicalChild;

    NS_DECLARE_REFLECTION(Decorator, FrameworkElement)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
