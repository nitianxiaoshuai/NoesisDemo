////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_USERCONTROL_H__
#define __GUI_USERCONTROL_H__


#include <Noesis.h>
#include <NsGui/ContentControl.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a simple way to create a composition of controls.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.forms.usercontrol.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API UserControl: public ContentControl
{
protected:
    /// From FrameworkElement
    //@{
    FrameworkElement* GetStateGroupsRoot() const;
    //@}

    NS_DECLARE_REFLECTION(UserControl, ContentControl)
};

}
}

#endif
