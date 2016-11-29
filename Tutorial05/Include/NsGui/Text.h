
////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TEXT_H__
#define __GUI_TEXT_H__


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
/// Adds stroke capabilities to text controls.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API Text
{
    /// Dependency properties
    //@{
    static const DependencyProperty* StrokeProperty;
    static const DependencyProperty* StrokeThicknessProperty;
    //@}

    NS_DECLARE_REFLECTION(Text, Core::NoParent)
};

}
}

#endif
