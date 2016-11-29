////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PATH_H__
#define __GUI_PATH_H__


#include <Noesis.h>
#include <NsGui/Shape.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class Geometry;
class MatrixTransform;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Draws a series of connected lines and curves.
///
/// .. code-block:: c++
///
///    // Geometry
///    Ptr<StreamGeometry> geometry = *new StreamGeometry();
///    {
///        StreamGeometryContext context = geometry->Open();
///        context.BeginFigure(Point(260.0f, 200.0f), true);
///        context.ArcTo(Point(140.0f, 200.0f), Drawing::Size(60.0f, 60.0f), 0, false, true);
///        context.ArcTo(Point(260.0f, 200.0f), Drawing::Size(60.0f, 60.0f), 0, false, true);
///    }
///
///    // Path
///    Ptr<Gui::Path> path = *new Gui::Path();
///    Ptr<Brush> red = *new SolidColorBrush(Color::Red);
///    path->SetFill(red.GetPtr());
///    path->SetData(geometry.GetPtr());
///
///    // Root canvas
///    Ptr<Canvas> root = *new Canvas();
///    Ptr<Brush> gray = *new SolidColorBrush(Color::LightGray);
///    root->SetBackground(gray.GetPtr());
///    root->GetChildren()->Add(path.GetPtr());
///
/// http://msdn.microsoft.com/en-us/library/system.windows.shapes.path.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Path: public Shape
{
public:
    /// Constructor
    Path();

    /// Destructor
    ~Path();

    /// Gets or sets the geometry that specifies the shape to be drawn
    //@{
    Geometry* GetData() const;
    void SetData(Geometry* data);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* DataProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnRender(DrawingContext* context);
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    Drawing::Size GetMinimumSize() const;
    void OnGeometryChanged(Freezable* freezable, FreezableEventReason reason);

private:
    Ptr<Geometry> mRenderGeometry;
    Ptr<MatrixTransform> mRenderMatrix;
    Ptr<MatrixTransform> mStretchMatrix;

    NS_DECLARE_REFLECTION(Path, Shape)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
