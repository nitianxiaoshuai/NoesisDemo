////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LOCALXAMLPROVIDER_H__
#define __GUI_LOCALXAMLPROVIDER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/XamlProvider.h>

#include <limits.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A XAML provider that searches in local directories
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API LocalXamlProvider: public XamlProvider
{
public:
    LocalXamlProvider(const NsChar* rootPath);

private:
    /// From XamlProvider
    //@{
    Ptr<Core::Stream> LoadXaml(const NsChar* filename);
    //@}

private:
    NsChar mRootPath[PATH_MAX];
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
