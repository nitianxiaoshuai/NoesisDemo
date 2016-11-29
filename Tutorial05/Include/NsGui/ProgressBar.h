////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PROGRESSBAR_H__
#define __GUI_PROGRESSBAR_H__


#include <Noesis.h>
#include <NsGui/RangeBase.h>


namespace Noesis
{
namespace Gui
{

// Forward declaration
enum Orientation;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Indicates the progress of an operation.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.progressbar.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ProgressBar: public RangeBase
{
public:
    ProgressBar();
    
    /// Gets or sets whether the ProgressBar shows actual values or generic, continuous progress 
    /// feedback
    //@{
    NsBool GetIsIndeterminate() const;
    void SetIsIndeterminate(NsBool value);
    //@}
    
    /// Gets or sets the orientation of a ProgressBar: horizontal or vertical.
    //@{
    Orientation GetOrientation() const;
    void SetOrientation(Orientation orientation);
    //@}
    
public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* IsIndeterminateProperty;
    static const DependencyProperty* OrientationProperty;
    //@}

protected:
    /// From RangeBase
    //@{
    void OnMaximumValueChanged(NsFloat32 oldMaximum, NsFloat32 newMaximum);
    void OnMinimumValueChanged(NsFloat32 oldMinimum, NsFloat32 newMinimum);
    void OnValueChanged(NsFloat32 oldValue, NsFloat32 newValue);
    //@}

    /// From FrameworkElement
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    void UpdateVisualStates();
    //@}

    /// From DependencyProperty
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:

    void OnTrackSizeChanged(Core::BaseComponent* o, const SizeChangedEventArgs& e);
    void UpdateIndicator();

private:
    Ptr<FrameworkElement> mTrack;
    Ptr<FrameworkElement> mIndicator;

    NS_DECLARE_REFLECTION(ProgressBar, RangeBase)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif