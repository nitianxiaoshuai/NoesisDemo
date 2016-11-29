////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_FONTPROVIDER_H__
#define __DRAWING_FONTPROVIDER_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>
#include <NsDrawing/FontProperties.h>


NS_CFORWARD(Core, Stream)


namespace Noesis
{
namespace Drawing
{

struct FontSource
{
    Ptr<Core::Stream> file;
    NsSize faceIndex;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for implementing providers of fonts
////////////////////////////////////////////////////////////////////////////////////////////////////
class FontProvider: public Core::BaseComponent
{
public:
    /// Finds the font in the given folder that best matches the specified properties.
    /// Returns a null stream if no matching found
    virtual FontSource MatchFont(const NsChar* baseUri, const NsChar* familyName, FontWeight weight,
        FontStretch stretch, FontStyle style) = 0;
};

}
}

#endif
