
////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ELEMENT_H__
#define __GUI_ELEMENT_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DependencyProperty;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Adds projection capabilities to UI elements.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API Element
{
    /// Dependency properties
    //@{
    static const DependencyProperty* ProjectionProperty;
    //@}

    NS_DECLARE_REFLECTION(Element, Core::NoParent)
};

}
}

#endif
