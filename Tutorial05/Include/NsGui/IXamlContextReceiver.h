////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IXAMLCONTEXTRECEIVER_H__
#define __GUI_IXAMLCONTEXTRECEIVER_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{
namespace Gui
{

// Forward declaration
//@{
NS_INTERFACE IXamlContext;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Receives the current context of a XAML tree parsing process. Classes implementing this
/// interface may need extra information while parsing or when the parsing process is done
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IXamlContextReceiver: public Core::Interface
{
    virtual void SetContext(const IXamlContext* context) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IXamlContextReceiver, Core::Interface)
};

}
}

#endif
