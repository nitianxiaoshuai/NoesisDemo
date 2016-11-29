////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LINE_H__
#define __GUI_LINE_H__


#include <Noesis.h>
#include <NsGui/Shape.h>
#include <NsDrawing/Point.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class LineGeometry;
class MatrixTransform;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Draws a line.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.shapes.line.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Line: public Shape
{
public:
    /// Constructor
    Line();

    /// Destructor
    ~Line();

    /// Gets or sets the x-coordinate of the Line start point
    //@{
    NsFloat32 GetX1() const;
    void SetX1(NsFloat32 x1);
    //@}

    /// Gets or sets the y-coordinate of the Line start point
    //@{
    NsFloat32 GetY1() const;
    void SetY1(NsFloat32 y1);
    //@}

    /// Gets or sets the x-coordinate of the Line end point
    //@{
    NsFloat32 GetX2() const;
    void SetX2(NsFloat32 x2);
    //@}

    /// Gets or sets the y-coordinate of the Line end point
    //@{
    NsFloat32 GetY2() const;
    void SetY2(NsFloat32 y2);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* X1Property;
    static const DependencyProperty* Y1Property;
    static const DependencyProperty* X2Property;
    static const DependencyProperty* Y2Property;
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

private:
    Ptr<LineGeometry> mLineGeometry;
    Ptr<MatrixTransform> mStretchMatrix;

    NS_DECLARE_REFLECTION(Line, Shape)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
