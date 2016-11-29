////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_CACHEDFONTPROVIDER_H__
#define __DRAWING_CACHEDFONTPROVIDER_H__


#include <Noesis.h>
#include <NsDrawing/FontProvider.h>
#include <NsDrawing/LocalFontProviderApi.h>
#include <NsCore/Vector.h>
#include <NsCore/Map.h>

#include <EASTL/fixed_string.h>
#include <EASTL/fixed_vector.h>


namespace Noesis
{
namespace Drawing
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275 4251)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for font providers caching font information found in each folder. Inheritors must
/// implement ScanFolder() and OpenFont() functions.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_DRAWING_LOCALFONTPROVIDER_API CachedFontProvider: public FontProvider
{
protected:
    virtual void ScanFolder(const NsChar* folder) = 0;
    virtual Ptr<Core::Stream> OpenFont(const NsChar* folder, const NsChar* id) const = 0;

    void RegisterFont(const NsChar* folder, const NsChar* filename);

private:
    /// From FontProvider
    //@{
    FontSource MatchFont(const NsChar* baseUri, const NsChar* familyName, FontWeight weight,
        FontStretch stretch, FontStyle style);
    //@}

    typedef eastl::fixed_string<NsChar, 128> Filename;

    struct Face
    {
        Filename filename;
        NsSize faceIndex;

        FontWeight weight;
        FontStretch stretch;
        FontStyle style;
    };

    struct FindStretch
    {
        FindStretch(NsInt32 stretch): _stretch(stretch) {}
        FindStretch& operator=(const FindStretch&) { NS_ASSERT_UNREACHABLE; }

        NsBool operator()(const Face& face)
        {
            return _stretch == face.stretch;
        }
        
        const NsInt32 _stretch;
    };

    struct FilterStretch
    {
        FilterStretch(NsInt32 stretch): _stretch(stretch) {}
        FilterStretch& operator=(const FilterStretch&) { NS_ASSERT_UNREACHABLE; }

        NsBool operator()(const Face& face)
        {
            return _stretch != face.stretch;
        }

        const NsInt32 _stretch;
    };

    struct SortStyle
    {
        SortStyle(const NsUInt32* scores): _scores(scores) {}
        SortStyle& operator=(const SortStyle&) { NS_ASSERT_UNREACHABLE; }

        NsBool operator()(const Face& f0, const Face& f1) const
        {
            return _scores[f0.style] < _scores[f1.style];
        }

        const NsUInt32* const _scores;
    };

    struct FindWeight
    {
        FindWeight(NsInt32 weight): _weight(weight) {}
        FindWeight& operator=(const FindWeight&) { NS_ASSERT_UNREACHABLE; }

        NsBool operator()(const Face& face)
        {
            return _weight == face.weight;
        }

        const NsInt32 _weight;
    };
    
    struct ILess
    {
        NsBool operator()(const Filename& a, const Filename& b)
        {
            return a.comparei(b) < 0;
        }
    };

    typedef NsVector<Face> Family;
    typedef NsMap<Filename, Family, ILess> Families;
    typedef NsMap<Filename, Families, ILess> Folders;
    Folders mFolders;

    Folders::iterator GetFolder(const NsChar* folder);

    typedef eastl::fixed_vector<Face, 8> Family_;
    FontSource FindBestMatch(const NsChar* baseUri, Family_& family, FontWeight weight,
        FontStretch stretch, FontStyle style) const;
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
