////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SHAPE_H__
#define __GUI_SHAPE_H__


#include <Noesis.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class Brush;
class Pen;
class Geometry;
class Transform;
class MatrixTransform;
enum PenLineCap;
enum PenLineJoin;
enum Stretch;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a base class for shape elements.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.shapes.shape.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Shape: public FrameworkElement
{
public:
    /// Constructor
    Shape();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~Shape() = 0;

    /// Gets or sets the Brush that specifies how the shape's interior is painted
    //@{
    Brush* GetFill() const;
    void SetFill(Brush* fill);
    //@}

    /// Gets or sets a Stretch value that describes how the shape fills its allocated space
    //@{
    Stretch GetStretch() const;
    void SetStretch(Stretch stretch);
    //@}

    /// Gets or sets the Brush that specifies how the Shape outline is painted
    //@{
    Brush* GetStroke() const;
    void SetStroke(Brush* stroke);
    //@}

    /// Gets or sets a collection of float values that indicate the pattern of dashes and gaps that
    /// is used to outline shapes
    //@{
    const NsChar* GetStrokeDashArray() const;
    void SetStrokeDashArray(const NsChar* dashArray);
    //@}

    /// Gets or sets a PenLineCap enumeration value that specifies how the ends of a dash are drawn
    //@{
    PenLineCap GetStrokeDashCap() const;
    void SetStrokeDashCap(PenLineCap cap);
    //@}

    /// Gets or sets a float that specifies the distance within the dash pattern where a dash begins
    //@{
    NsFloat32 GetStrokeDashOffset() const;
    void SetStrokeDashOffset(NsFloat32 offset);
    //@}

    /// Gets or sets a PenLineCap enumeration value that describes the Shape at the end of a line
    //@{
    PenLineCap GetStrokeEndLineCap() const;
    void SetStrokeEndLineCap(PenLineCap cap);
    //@}

    /// Gets or sets a PenLineJoin enumeration value that specifies the type of join that is used
    /// at the vertices of a Shape
    //@{
    PenLineJoin GetStrokeLineJoin() const;
    void SetStrokeLineJoin(PenLineJoin join);
    //@}

    /// Gets or sets a limit on the ratio of the miter length to half the StrokeThickness of a
    /// Shape element
    //@{
    NsFloat32 GetStrokeMiterLimit() const;
    void SetStrokeMiterLimit(NsFloat32 limit);
    //@}

    /// Gets or sets a PenLineCap enumeration value describing the Shape at the start of a Stroke
    //@{
    PenLineCap GetStrokeStartLineCap() const;
    void SetStrokeStartLineCap(PenLineCap cap);
    //@}

    /// Gets or sets the width of the Shape outline
    //@{
    NsFloat32 GetStrokeThickness() const;
    void SetStrokeThickness(NsFloat32 thickness);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* FillProperty;
    static const DependencyProperty* StretchProperty;
    static const DependencyProperty* StrokeProperty;
    static const DependencyProperty* StrokeDashArrayProperty;
    static const DependencyProperty* StrokeDashCapProperty;
    static const DependencyProperty* StrokeDashOffsetProperty;
    static const DependencyProperty* StrokeEndLineCapProperty;
    static const DependencyProperty* StrokeLineJoinProperty;
    static const DependencyProperty* StrokeMiterLimitProperty;
    static const DependencyProperty* StrokeStartLineCapProperty;
    static const DependencyProperty* StrokeThicknessProperty;
    //@}

protected:
    /// Gets stroke thickness validating stroke brush and thickness size
    NsFloat32 GetValidStrokeThickness() const;

    /// Gets a pen with the shape stroke params set
    Pen* GetPen() const;

    /// Calculates stretching parameters for the given geometry bounds
    void GetStretchInfo(const Drawing::Rect& bounds, const Drawing::Size& availableSize,
        Drawing::Point& offset, Drawing::Point& scale) const;

    /// Calculates stretched size for the given geometry bounds
    //@{
    Drawing::Size GetStretchSize(const Drawing::Rect& bounds,
        const Drawing::Size& availableSize);
    Drawing::Size GetStretchSize(const Drawing::Rect& bounds, const Drawing::Point& scale);
    //@}

    /// Calculates stretch matrix and returns final arrange size for the given geometry
    Drawing::Size GetArrangeStretch(Geometry* geometry,
        MatrixTransform* stretchMatrix, const Drawing::Size& finalSize);

    /// Calculates bounds of the shape for the final size
    Drawing::Rect GetFinalBounds(const Drawing::Size& finalSize) const;

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From FrameworkElement
    //@{
    NsSize GetLogicalChildrenCount() const;
    BaseComponent* GetLogicalChild(NsSize index) const;
    //@}

private:
    /// Base classes are non-copyable objects
    //@{
    Shape(const Shape&);
    Shape& operator=(const Shape&);
    //@}

    void EnsurePen() const;

private:
    mutable Ptr<Pen> mPen;

    NS_DECLARE_REFLECTION(Shape, FrameworkElement)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
