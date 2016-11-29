////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VIEWBOX_H__
#define __GUI_VIEWBOX_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/Enums.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Drawing
{
struct Size;
struct Point;
}
namespace Gui
{
class Decorator;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a content decorator that can stretch and scale a single child to fill the available 
/// space.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.viewbox.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Viewbox: public FrameworkElement
{
public:
    /// Constructor
    Viewbox();

    /// Destructor
    ~Viewbox();

    /// Returns the scale necessary to stretch element size to the available size
    static Drawing::Point GetStretchScale(const Drawing::Size& elementSize,
        const Drawing::Size& availableSize, Stretch stretch,
        StretchDirection stretchDirection = StretchDirection_Both);

    /// Gets or sets the StretchDirection, which determines how scaling is applied to the contents
    /// of a Viewbox
    //@{
    StretchDirection GetStretchDirection() const;
    void SetStretchDirection(StretchDirection stretchDirection);
    //@}
    
    /// Gets or sets the Viewbox Stretch mode, which determines how content fits into the available
    /// space
    //@{
    Stretch GetStretch() const;
    void SetStretch(Stretch stretch);
    //@}

    /// Gets or sets the single child of a Viewbox element.
    /// \prop
    //@{
    UIElement* GetChild() const;
    void SetChild(UIElement* child);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* StretchDirectionProperty;
    static const DependencyProperty* StretchProperty;
    //@}

protected:
    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const;
    Visual* GetVisualChild(NsSize index) const;
    //@}

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const;
    NsSize GetLogicalChildrenCount() const;
    Core::BaseComponent* GetLogicalChild(NsSize index) const;
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    Drawing::Size GetStretchSize(const Drawing::Size& childSize,
        const Drawing::Size& availableSize, Drawing::Point& scale);

    Decorator* GetStretchDecorator() const;

private:
    NS_DECLARE_REFLECTION(Viewbox, FrameworkElement)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
