////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COMBINEDGEOMETRY_H__
#define __GUI_COMBINEDGEOMETRY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Geometry.h>
#include <NsGui/Enums.h>
#include <NsCore/ReflectionDeclareEnum.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a 2-D geometric shape defined by the combination of two 
/// Geometry objects. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.combinedgeometry.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API CombinedGeometry: public Geometry
{
public:
    CombinedGeometry();
    CombinedGeometry(Geometry* geometry1, Geometry* geometry2, GeometryCombineMode mode);

    /// Gets or sets the first Geometry object of this CombinedGeometry object.
    //@{
    Geometry* GetGeometry1() const;
    void SetGeometry1(Geometry* geometry);
    //@}
    
    /// Gets or sets the second Geometry object of this CombinedGeometry object.
    //@{
    Geometry* GetGeometry2() const;
    void SetGeometry2(Geometry* geometry);
    //@}
    
    /// Gets or sets the method by which the two geometries (specified by the Geometry1 and Geometry2 properties) are combined. 
    //@{
    GeometryCombineMode GetGeometryCombineMode() const;
    void SetGeometryCombineMode(GeometryCombineMode mode);
    //@}

    /// From Geometry
    //@{
    NsBool IsEmpty() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* Geometry1Property;
    static const DependencyProperty* Geometry2Property;
    static const DependencyProperty* GeometryCombineModeProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    NsBool OnSubPropertyChanged(const DependencyProperty* dp);
    //@}

    /// From Geometry
    //@{
    Drawing::Rect GetRenderBoundsOverride(Pen* pen) const;
    NsBool FillContainsOverride(const Drawing::Point& point) const;
    NsBool StrokeContainsOverride(Pen* pen, const Drawing::Point& point) const;
    //@}

private:
    NsBool ContainsPoint(NsBool pointInGeo1, NsBool pointInGeo2) const;

private:
    enum UpdateFlags
    {
        UpdateFlags_Geometry1 = Geometry::UpdateFlags_Sentinel,
        UpdateFlags_Geometry2,
        UpdateFlags_CombineMode
    };

    NS_DECLARE_REFLECTION(CombinedGeometry, Geometry)
};

}
}


#endif
