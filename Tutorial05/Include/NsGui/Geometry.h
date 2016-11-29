////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GEOMETRY_H__
#define __GUI_GEOMETRY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Drawing
{
struct Rect;
struct Point;
}
namespace Gui
{
class Transform;
class Pen;
struct GeometryProxy;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Classes that derive from this abstract base class define geometric shapes. Geometry
/// objects can be used for clipping, hit-testing, and rendering 2-D graphic data.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.geometry.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Geometry: public Animatable, public IRenderProxyCreator
{
public:
    /// Constructor
    Geometry();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~Geometry() = 0;

    /// Creates a new Geometry instance from the specified string
    static Ptr<Geometry> Parse(const NsChar* str);
    static NsBool TryParse(const NsChar* str, Ptr<BaseComponent>& result);

    /// Determines whether the object is empty
    virtual NsBool IsEmpty() const;

    /// Gets geometry bounds
    /// \prop
    Drawing::Rect GetBounds() const;

    /// Returns an axis-aligned rectangle that is exactly large enough to contain the geometry after it
    /// has been outlined with the specified Pen
    Drawing::Rect GetRenderBounds(Pen* pen) const;

    /// Indicates whether the geometry contains the specified Point
    NsBool FillContains(const Drawing::Point& point) const;
    
    /// Determines whether the specified Point is contained in the stroke produced by applying the
    /// specified Pen to the geometry
    NsBool StrokeContains(Pen* pen, const Drawing::Point& point) const;

    /// Gets or sets the Transform object applied to a Geometry
    //@{
    Transform* GetTransform() const;
    void SetTransform(Transform* transform);
    //@}

    /// From IRenderProxyCreator
    //@{
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UnregisterRenderer(ViewId viewId);
    //@}

public:
    /// Dependency Properties
    static const DependencyProperty* TransformProperty;

protected:
    /// Implements geometry render bounds calculation
    virtual Drawing::Rect GetRenderBoundsOverride(Pen* pen) const;

    /// Implements contain tests
    //@{
    virtual NsBool FillContainsOverride(const Drawing::Point& point) const;
    virtual NsBool StrokeContainsOverride(Pen* pen, const Drawing::Point& point) const;
    //@}

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    NsBool OnSubPropertyChanged(const DependencyProperty* dp);
    //@}

protected:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Transform,

        UpdateFlags_Sentinel
    };

private:
    /// Base classes are non-copyable objects
    //@{
    Geometry(const Geometry&);
    Geometry& operator=(const Geometry&);
    //@}

    NS_DECLARE_REFLECTION(Geometry, Animatable)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
