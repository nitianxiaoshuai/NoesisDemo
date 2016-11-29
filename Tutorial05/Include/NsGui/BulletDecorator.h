////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BULLETDECORATOR_H__
#define __GUI_BULLETDECORATOR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Decorator.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class Brush;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a layout control that aligns a bullet and another visual object.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.bulletdecorator.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BulletDecorator: public Decorator
{
public:
    /// Constructor
    BulletDecorator();

    /// Destructor
    ~BulletDecorator();

    /// Gets or sets the background color for a BulletDecorator control.
    //@{
    Brush* GetBackground() const;
    void SetBackground(Brush* brush);
    //@}
    
    /// Gets or sets the object to use as the bullet in a BulletDecorator.
    //@{
    UIElement* GetBullet() const;
    void SetBullet(UIElement* bullet);
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const;
    Visual* GetVisualChild(NsSize index) const;
    //@}

    /// From UIElement
    //@{
    void OnRender(DrawingContext* drawingContext);
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
    NsSize InternalGetNumChildren() const;
    Visual* InternalGetChild(NsSize index) const;

public:
    static const DependencyProperty* BackgroundProperty;

private:
    Ptr<UIElement> mBullet;

    NS_DECLARE_REFLECTION(BulletDecorator, Decorator)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif