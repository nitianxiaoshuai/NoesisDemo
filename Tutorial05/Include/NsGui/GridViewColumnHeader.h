////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRIDVIEWCOLUMNHEADER_H__
#define __GUI_GRIDVIEWCOLUMNHEADER_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/ControlsApi.h>
#include <NsGui/BaseButton.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class GridViewColumn;
class Thumb;
class Canvas;
struct DragStartedEventArgs;
struct DragCompletedEventArgs;
struct DragDeltaEventArgs;
struct MouseButtonEventArgs;
//@}

enum GridViewColumnHeaderRole
{
    /// The column header displays above its associated column
    GridViewColumnHeaderRole_Normal,
    /// The column header is the object of a drag-and-drop operation to move a column
    GridViewColumnHeaderRole_Floating,
    /// The column header is the last header in the row of column headers and is used for padding
    GridViewColumnHeaderRole_Padding 
};

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a column header for a GridViewColumn.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.gridviewcolumnheader.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CONTROLS_API GridViewColumnHeader: public BaseButton
{
public:
    GridViewColumnHeader();
    ~GridViewColumnHeader();
    
    /// Gets the GridViewColumn that is associated with the GridViewColumnHeader
    GridViewColumn* GetColumn() const;

    /// Gets the role of a GridViewColumnHeader
    GridViewColumnHeaderRole GetRole() const;
    
public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* ColumnProperty;
    static const DependencyProperty* RoleProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e);
    void OnMouseMove(const MouseEventArgs& e);
    //@}

    /// From FrameworkElement
    //@{
    void OnTemplateChanged(FrameworkTemplate* oldTemplate, FrameworkElement* oldRoot,
        FrameworkTemplate* newTemplate, FrameworkElement* newRoot);
    //@}

private:
    void OnColumnPropertyChanged(BaseComponent* sender, 
        const DependencyPropertyChangedEventArgs& args);

    void OnGripperDragStarted(Core::BaseComponent*, const DragStartedEventArgs&);
    void OnGripperDragCompleted(Core::BaseComponent*, const DragCompletedEventArgs&);
    void OnGripperDragDelta(Core::BaseComponent*, const DragDeltaEventArgs&);
    void OnGripperDoubleClick(Core::BaseComponent*, const MouseButtonEventArgs&);
    
    void RegisterGripperEvents();
    void UnregisterGripperEvents();
    
private:
    friend class GridViewHeaderRowPresenter;
    
    Ptr<Thumb> mHeaderGripper;
    Ptr<Canvas> mFloatingHeaderCanvas;
    
    NsFloat32 mStartDragWidth;

    NS_DECLARE_REFLECTION(GridViewColumnHeader, BaseButton)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

NS_DECLARE_ENUM(NS_GUI_CONTROLS_API, Noesis::Gui::GridViewColumnHeaderRole)

#endif