
////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_LOCALFONTPROVIDER_H__
#define __DRAWING_LOCALFONTPROVIDER_H__


#include <Noesis.h>
#include <NsDrawing/CachedFontProvider.h>
#include <NsDrawing/LocalFontProviderApi.h>


namespace Noesis
{
namespace Drawing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A font provider that searches fonts in local directories
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_DRAWING_LOCALFONTPROVIDER_API LocalFontProvider: public CachedFontProvider
{
public:
    LocalFontProvider(const NsChar* rootPath);

private:
    /// From CachedFontProvider
    //@{
    void ScanFolder(const NsChar* folder);
    Ptr<Core::Stream> OpenFont(const NsChar* folder, const NsChar* filename) const;
    //@}

    void ScanFolder(const NsChar* path, const NsChar* folder, const NsChar* pattern);

private:
    NsChar mRootPath[PATH_MAX];
};

}
}

#endif
