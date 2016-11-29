////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VIRTUALIZATIONCACHELENGTH_H__
#define __GUI_VIRTUALIZATIONCACHELENGTH_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/NSTLForwards.h>


namespace Noesis
{

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum VirtualizationCacheLengthUnit
{
    /// The value is expressed as a pixel
    VirtualizationCacheLengthUnit_Pixel,
    /// The value is expressed as an item
    VirtualizationCacheLengthUnit_Item,
    /// The value is expressed as a page full of items
    VirtualizationCacheLengthUnit_Page
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the measurements for the VirtualizingPanel.CacheLength attached property.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.virtualizationcachelength.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API VirtualizationCacheLength
{
public:
    VirtualizationCacheLength();
    VirtualizationCacheLength(NsFloat32 cacheBeforeAndAfterViewport);
    VirtualizationCacheLength(NsFloat32 cacheBeforeViewport, NsFloat32 cacheAfterViewport);

    /// Gets the size of the cache before the viewport when the VirtualizingPanel is virtualizing
    /// \prop
    NsFloat32 GetCacheBeforeViewport() const;

    /// Gets the size of the cache after the viewport when the VirtualizingPanel is virtualizing
    /// \prop
    NsFloat32 GetCacheAfterViewport() const;

    // Copy operators
    //@{
    VirtualizationCacheLength(const VirtualizationCacheLength& other);
    VirtualizationCacheLength& operator=(const VirtualizationCacheLength& other);
    //@}

    // Comparison operators
    //@{
    NsBool operator==(const VirtualizationCacheLength& other) const;
    NsBool operator!=(const VirtualizationCacheLength& other) const;
    //@}

    // Creates a string representation of this VirtualizationCacheLength structure
    // The string has the following form: "beforeViewportLength,afterViewportLength"
    NsString ToString() const;

    // Returns a hash code
    NsUInt32 GetHashCode() const;

    // Converts a string into the equivalent VirtualizationCacheLength structure
    static VirtualizationCacheLength Parse(const NsChar* str);
    static NsBool TryParse(const NsChar* str, VirtualizationCacheLength& result);

private:
    NsFloat32 mCacheBeforeViewport;
    NsFloat32 mCacheAfterViewport;

    NS_DECLARE_REFLECTION(VirtualizationCacheLength, Core::NoParent)
};

}
}

NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::VirtualizationCacheLengthUnit)


#endif
