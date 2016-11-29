////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GROUPBOX_H__
#define __GUI_GROUPBOX_H__


#include <Noesis.h>
#include <NsGui/HeaderedContentControl.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that creates a container that has a border and a header for user
/// interface (UI) content.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.forms.groupbox.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API GroupBox: public HeaderedContentControl
{
public:
    /// Constructor
    GroupBox();

    NS_DECLARE_REFLECTION(GroupBox, HeaderedContentControl)
};

}
}


#endif
