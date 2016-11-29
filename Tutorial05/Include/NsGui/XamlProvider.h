////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_XAMLPROVIDER_H__
#define __GUI_XAMLPROVIDER_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/PtrForward.h>


NS_CFORWARD(Core, Stream);


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for implementing providers of XAMLs
////////////////////////////////////////////////////////////////////////////////////////////////////
class XamlProvider: public Core::BaseComponent
{
public:
    // Loads the specified XAML file. Returns null if no xaml found
    virtual Ptr<Core::Stream> LoadXaml(const NsChar* filename) = 0;
};

}
}

#endif
