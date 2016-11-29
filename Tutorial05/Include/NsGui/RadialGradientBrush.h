////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RADIALGRADIENTBRUSH_H__
#define __GUI_RADIALGRADIENTBRUSH_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/GradientBrush.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Drawing
{
struct Point;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Paints an area with a radial gradient. A focal point defines the beginning 
/// of the gradient, and a circle defines the end point of the gradient. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.radialgradientbrush.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RadialGradientBrush: public GradientBrush
{
public:
    /// Constructor
    RadialGradientBrush();
    
    /// Gets or sets the center of the outermost circle of the radial gradient
    //@{
    const Drawing::Point& GetCenter() const;
    void SetCenter(const Drawing::Point& center);
    //@}
    
    /// Gets or sets the location of the two-dimensional focal point that defines the beginning of 
    /// the gradient
    //@{
    const Drawing::Point& GetGradientOrigin() const;
    void SetGradientOrigin(const Drawing::Point& origin);
    //@}
    
    /// Gets or sets the horizontal radius of the outermost circle of the radial gradient
    //@{
    NsFloat32 GetRadiusX() const;
    void SetRadiusX(NsFloat32 radius);
    //@}
    
    /// Gets or sets the vertical radius of the outermost circle of a radial gradient
    //@{
    NsFloat32 GetRadiusY() const;
    void SetRadiusY(NsFloat32 radius);
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* CenterProperty;
    static const DependencyProperty* GradientOriginProperty;
    static const DependencyProperty* RadiusXProperty;
    static const DependencyProperty* RadiusYProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_Center = GradientBrush::UpdateFlags_Sentinel,
        UpdateFlags_Origin,
        UpdateFlags_RadiusX,
        UpdateFlags_RadiusY
    };

    NS_DECLARE_REFLECTION(RadialGradientBrush, GradientBrush)
};

}
}

#endif