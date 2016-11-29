////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_LOCALTEXTUREPROVIDER_H__
#define __DRAWING_LOCALTEXTUREPROVIDER_H__


#include <Noesis.h>
#include <NsDrawing/FileTextureProvider.h>

#include <limits.h>


namespace Noesis
{
namespace Drawing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A texture provider that searches textures in local directories
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_DRAWING_TEXTUREPROVIDER_API LocalTextureProvider: public FileTextureProvider
{
public:
    LocalTextureProvider(const NsChar* rootPath);

private:
    /// From FileTextureProvider
    //@{
    Ptr<Core::Stream> OpenStream(const NsChar* filename) const;
    //@}

private:
    NsChar mRootPath[PATH_MAX];
};

}
}

#endif
