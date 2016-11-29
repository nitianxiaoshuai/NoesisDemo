////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SOLIDCOLORBRUSH_H__
#define __GUI_SOLIDCOLORBRUSH_H__


#include <Noesis.h>
#include <NsGui/Brush.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{

// Forward declaration
//@{
namespace Drawing
{
class Color;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Paints an area with a solid color.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.solidcolorbrush.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SolidColorBrush: public Brush
{
public:
    /// Constructor
    SolidColorBrush();

    /// Constructor with color
    SolidColorBrush(const Drawing::Color& color);

    /// Gets or sets the string content of a ContentControl
    //@{
    const Drawing::Color& GetColor() const;
    void SetColor(const Drawing::Color& color);
    //@}
    
    /// Parses a string value to create an instance of a solid color brush
    static Ptr<SolidColorBrush> Parse(const NsChar* str);
    static NsBool TryParse(const NsChar* str, Ptr<BaseComponent>& result);

    /// From BaseObject
    //@{
    NsString ToString() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ColorProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Brush
    //@{
    NsBool IsTransparentOverride() const;
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_Color = Brush::UpdateFlags_Sentinel
    };

    NS_DECLARE_REFLECTION(SolidColorBrush, Brush)
};

}
}

#endif
