////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LINEARGRADIENTBRUSH_H__
#define __GUI_LINEARGRADIENTBRUSH_H__


#include <Noesis.h>
#include <NsGui/GradientBrush.h>
#include <NsGui/IRenderProxyCreator.h>


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
/// Paints an area with a linear gradient.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.lineargradientbrush.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API LinearGradientBrush: public GradientBrush
{
public:
    /// Constructor
    LinearGradientBrush();

    /// Gets or sets the starting coordinates of the linear gradient
    //@{
    const Drawing::Point& GetStartPoint() const;
    void SetStartPoint(const Drawing::Point& startPoint);
    //@}

    /// Gets or sets the ending coordinates of the linear gradient
    //@{
    const Drawing::Point& GetEndPoint() const;
    void SetEndPoint(const Drawing::Point& endPoint);
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* EndPointProperty;
    static const DependencyProperty* StartPointProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_StartPoint = GradientBrush::UpdateFlags_Sentinel,
        UpdateFlags_EndPoint
    };

    NS_DECLARE_REFLECTION(LinearGradientBrush, GradientBrush)
};

}
}

#endif
