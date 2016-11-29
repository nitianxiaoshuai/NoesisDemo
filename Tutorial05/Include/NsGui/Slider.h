////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SLIDER_H__
#define __GUI_SLIDER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/RangeBase.h>
#include <NsGui/Enums.h>
#include <NsCore/Set.h>
#include <NsCore/ReflectionDeclareEnum.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
enum Orientation;
class Track;
class BaseButton;
class RepeatButton;
struct DragStartedEventArgs;
struct DragDeltaEventArgs;
struct CanExecuteRoutedEventArgs;
struct ExecutedRoutedEventArgs;
class RoutedCommand;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that lets the user select from a range of values by moving a Thumb
/// control along a Track.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.slider.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Slider: public RangeBase
{
public:
    Slider();
    ~Slider();

    /// Gets or sets the amount of time in milliseconds that a RepeatButton waits, while it is 
    /// pressed, before a command to move the Thumb executes, such as a DecreaseLarge command. 
    //@{
    NsInt32 GetDelay() const;
    void SetDelay(NsInt32 delay);
    //@}
    
    /// Gets or sets the amount of time in milliseconds between increase or decrease commands when
    /// a user clicks the RepeatButton of a Slider. 
    //@{
    NsInt32 GetInterval() const;
    void SetInterval(NsInt32 interval);
    //@}
    
    /// Gets or sets the direction of increasing value. 
    //@{
    NsBool GetIsDirectionReversed() const;
    void SetIsDirectionReversed(NsBool value);
    //@}
    
    /// Gets or sets a value that indicates whether the Thumb of a Slider moves immediately to the
    /// location of the mouse click that occurs while the mouse pointer pauses on the Slider track. 
    //@{
    NsBool GetIsMoveToPointEnabled() const;
    void SetIsMoveToPointEnabled(NsBool value);
    //@}
    
    /// Gets or sets a value that indicates whether the Slider displays a selection range along the
    /// Slider.
    //@{
    NsBool GetIsSelectionRangeEnabled() const;
    void SetIsSelectionRangeEnabled(NsBool value);
    //@}
    
    /// Gets or sets a value that indicates whether the Slider automatically moves the Thumb to the
    /// closest tick mark.
    //@{
    NsBool GetIsSnapToTickEnabled() const;
    void SetIsSnapToTickEnabled(NsBool value);
    //@}
    
    /// Gets or sets the orientation of a Slider. 
    //@{
    Orientation GetOrientation() const;
    void SetOrientation(Orientation orientation);
    //@}
    
    /// Gets or sets the largest value of a specified selection for a Slider.
    //@{
    NsFloat32 GetSelectionEnd() const;
    void SetSelectionEnd(NsFloat32 value);
    //@}
    
    /// Gets or sets the smallest value of a specified selection for a Slider.
    //@{
    NsFloat32 GetSelectionStart() const;
    void SetSelectionStart(NsFloat32 value);
    //@}
    
    /// Gets or sets the interval between tick marks. 
    //@{
    NsFloat32 GetTickFrequency() const;
    void SetTickFrequency(NsFloat32 value);
    //@}
    
    /// Gets or sets the position of tick marks with respect to the Track of the Slider. 
    //@{
    TickPlacement GetTickPlacement() const;
    void SetTickPlacement(TickPlacement placement);
    //@}
    
    /// Gets or sets the positions of the tick marks to display for a Slider. 
    //@{
    const NsChar* GetTicks() const;
    void SetTicks(const NsChar* value);
    //@}

    Track* GetTrack() const;

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* DelayProperty;
    static const DependencyProperty* IntervalProperty;
    static const DependencyProperty* IsDirectionReversedProperty;
    static const DependencyProperty* IsMoveToPointEnabledProperty;
    static const DependencyProperty* IsSelectionRangeEnabledProperty;
    static const DependencyProperty* IsSnapToTickEnabledProperty;
    static const DependencyProperty* OrientationProperty;
    static const DependencyProperty* SelectionEndProperty;
    static const DependencyProperty* SelectionStartProperty;
    static const DependencyProperty* TickFrequencyProperty;
    static const DependencyProperty* TickPlacementProperty;
    static const DependencyProperty* TicksProperty;
    //@}

    /// Routed Commands
    //@{
    static const RoutedCommand* DecreaseLargeCommand;
    static const RoutedCommand* DecreaseSmallCommand;
    static const RoutedCommand* IncreaseLargeCommand;
    static const RoutedCommand* IncreaseSmallCommand;
    static const RoutedCommand* MaximizeValueCommand;
    static const RoutedCommand* MinimizeValueCommand;
    //@}

protected:
    // Slider value changes
    //@{
    virtual void OnDecreaseLarge();
    virtual void OnIncreaseLarge();
    virtual void OnDecreaseSmall();
    virtual void OnIncreaseSmall();
    virtual void OnMinimizeValue();
    virtual void OnMaximizeValue();
    //@}

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnPreviewMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    //@}

    /// From Control
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    //@}

    /// From Slider
    //@{
    void OnValueChanged(NsFloat32 oldValue, NsFloat32 newValue);
    //@}

private:
    void OnThumbDragStarted(Core::BaseComponent* sender, const DragStartedEventArgs& e);
    void OnThumbDragDelta(Core::BaseComponent* sender, const DragDeltaEventArgs& e);

    void RegisterDelegates();
    void FreeDelegates();

    void InvalidateTicks();
    void EnsureTicks();

    void MoveToNearestTick(NsFloat32 newValue);
    void MoveToNextTick(NsFloat32 directionDelta);
    NsFloat32 FindNextTick(NsFloat32 currentValue);
    NsFloat32 FindPrevTick(NsFloat32 currentValue);

    static void OnDecreaseLargeCommand(Core::BaseComponent* sender,
        const ExecutedRoutedEventArgs& args);
    static void OnIncreaseLargeCommand(Core::BaseComponent* sender,
        const ExecutedRoutedEventArgs& args);
    static void OnDecreaseSmallCommand(Core::BaseComponent* sender,
        const ExecutedRoutedEventArgs& args);
    static void OnIncreaseSmallCommand(Core::BaseComponent* sender,
        const ExecutedRoutedEventArgs& args);
    static void OnMinimizeValueCommand(Core::BaseComponent* sender,
        const ExecutedRoutedEventArgs& args);
    static void OnMaximizeValueCommand(Core::BaseComponent* sender,
        const ExecutedRoutedEventArgs& args);

private:
    Ptr<Track> mTrackInternal;

    typedef NsSet<NsFloat32> Ticks;
    Ticks mTicksInternal;

    NS_DECLARE_REFLECTION(Slider, RangeBase)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
