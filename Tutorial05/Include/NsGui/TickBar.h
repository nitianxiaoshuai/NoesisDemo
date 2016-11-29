////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TICKBAR_H__
#define __GUI_TICKBAR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/Enums.h>
#include <NsCore/Set.h>
#include <NsCore/Vector.h>
#include <NsCore/ReflectionDeclareEnum.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Math
{
template<class T> struct Vector2;
typedef Noesis::Math::Vector2<NsFloat32> Vector2f;
}
namespace Gui
{
class Brush;
class Pen;
}
//@}

namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that draws a set of tick marks for a Slider control.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.tickbar.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TickBar: public FrameworkElement
{
public:
    /// Constructor
    TickBar();
    
    /// Destructor
    ~TickBar();

    /// Gets or sets the Brush that is used to draw the tick marks
    //@{
    Brush* GetFill() const;
    void SetFill(Brush* fill);
    //@}

    /// Gets or sets the direction of increasing value of the tick marks
    //@{
    NsBool GetIsDirectionReversed() const;
    void SetIsDirectionReversed(NsBool directionReversed);
    //@}

    /// Gets or sets whether the TickBar displays a selection range
    //@{
    NsBool GetIsSelectionRangeEnabled() const;
    void SetIsSelectionRangeEnabled(NsBool selectionRangeEnabled);
    //@}

    /// Gets or sets the maximum value that is possible for a tick mark
    //@{
    NsFloat32 GetMaximum() const;
    void SetMaximum(NsFloat32 maximum);
    //@}

    /// Gets or sets the minimum value that is possible for a tick mark
    //@{
    NsFloat32 GetMinimum() const;
    void SetMinimum(NsFloat32 minimum);
    //@}

    /// Gets or sets where tick marks appear relative to a Track of a Slider control
    //@{
    TickBarPlacement GetPlacement() const;
    void SetPlacement(TickBarPlacement placement);
    //@}

    /// Gets or sets a space buffer for the area that contains the tick marks that are specified
    /// for a TickBar
    //@{
    NsFloat32 GetReservedSpace() const;
    void SetReservedSpace(NsFloat32 reservedSpace);
    //@}

    /// Gets or sets the end point of a selection
    //@{
    NsFloat32 GetSelectionEnd() const;
    void SetSelectionEnd(NsFloat32 selectionEnd);
    //@}

    /// Gets or sets the start point of a selection
    //@{
    NsFloat32 GetSelectionStart() const;
    void SetSelectionStart(NsFloat32 selectionStart);
    //@}

    /// Gets or sets the interval between tick marks
    //@{
    NsFloat32 GetTickFrequency() const;
    void SetTickFrequency(NsFloat32 tickFrequency);
    //@}

    /// Gets or sets the positions of the tick marks. For example, "0.5 1.0 43" or "0.5,1.0,43"
    //@{
    const NsChar* GetTicks() const;
    void SetTicks(const NsChar* ticks);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* FillProperty;
    static const DependencyProperty* IsDirectionReversedProperty;
    static const DependencyProperty* IsSelectionRangeEnabledProperty;
    static const DependencyProperty* MaximumProperty;
    static const DependencyProperty* MinimumProperty;
    static const DependencyProperty* PlacementProperty;
    static const DependencyProperty* ReservedSpaceProperty;
    static const DependencyProperty* SelectionEndProperty;
    static const DependencyProperty* SelectionStartProperty;
    static const DependencyProperty* TickFrequencyProperty;
    static const DependencyProperty* TicksProperty;
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
    void OnTemplatedParentChanged(FrameworkElement* oldParent, FrameworkElement* newParent);
    //@}

private:
    friend class TickBarTest;
    void GetRenderInfo(NsFloat32& range, NsFloat32& offset, NsFloat32& tickLength,
        Math::Vector2f& origin, Math::Vector2f& tickDirection, Math::Vector2f& tickBarDirection);
    void UpdateFixedTicks();
    void UpdateTicks(NsFloat32 range, NsFloat32 offset);
    void UpdateSelection(NsFloat32 range, NsFloat32 offset);

    void EnsurePen() const;
    Pen* GetPen() const;

    void RegisterBindings();
    void BindToTemplatedParent(const NsChar* path, const DependencyProperty* dp);
    void BindReservedSpace();

private:
    NsInt mUpdateFlags;

    NsFloat32 mPreviousRange;
    NsFloat32 mPreviousOffset;

    typedef NsSet<NsFloat32> FixedTicks;
    FixedTicks mFixedTicks;

    typedef NsVector<NsFloat32> Ticks;
    Ticks mTicksInternal;

    NsFloat32 mSelectionStartInternal;
    NsFloat32 mSelectionEndInternal;

    mutable Ptr<Pen> mPen;
    
    // Controls if the ReservedSpace has been binded
    NsBool mReservedSpaceBinded;

    NS_DECLARE_REFLECTION(TickBar, FrameworkElement)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
