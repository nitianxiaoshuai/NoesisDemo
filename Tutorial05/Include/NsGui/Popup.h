////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_POPUP_H__
#define __GUI_POPUP_H__


#include <Noesis.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/Enums.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/DelegateForward.h>


NS_SFORWARD(Drawing, Point)
NS_SFORWARD(Drawing, Size)
NS_SFORWARD(Drawing, Rect)
NS_CFORWARD(Gui, PopupLayer)
NS_CFORWARD(Gui, Transform)
NS_CFORWARD(Gui, DependencyProperty)
NS_CFORWARD(Gui, RoutedEvent)


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a pop-up window that has content.
/// 
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.popup.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Popup: public FrameworkElement
{
public:
    /// Constructor
    Popup();

    /// Destructor
    ~Popup();

    /// Gets or sets a value that indicates whether a Popup control can contain transparent content
    //@{
    NsBool GetAllowsTransparency() const;
    void SetAllowsTransparency(NsBool allowsTransparency);
    //@}

    /// Gets or sets content of the Popup control
    //@{
    UIElement* GetChild() const;
    void SetChild(UIElement* child);
    //@}

    /// Gets or sets a value that indicates whether the control has a drop shadow
    //@{
    NsBool GetHasDropShadow() const;
    void SetHasDropShadow(NsBool hasShadow);
    //@}

    /// Get or sets the horizontal distance between the target origin and the popup alignment point
    //@{
    NsFloat32 GetHorizontalOffset() const;
    void SetHorizontalOffset(NsFloat32 offset);
    //@}

    /// Gets or sets a value that indicates whether a ToolTip is visible
    //@{
    NsBool GetIsOpen() const;
    void SetIsOpen(NsBool isOpen);
    //@}

    /// Gets or sets the orientation of the ToolTip control when it opens, and specifies how the
    /// ToolTip control behaves when it overlaps screen boundaries
    //@{
    PlacementMode GetPlacement() const;
    void SetPlacement(PlacementMode placement);
    //@}

    /// Gets or sets the rectangular area relative to which the ToolTip control is positioned when
    /// it opens
    //@{
    const Drawing::Rect& GetPlacementRectangle() const;
    void SetPlacementRectangle(const Drawing::Rect& rect);
    //@}

    /// Gets or sets the UIElement relative to which the ToolTip is positioned when it opens
    //@{
    UIElement* GetPlacementTarget() const;
    void SetPlacementTarget(UIElement* target);
    //@}

    /// Gets or sets an animation for the opening and closing of a Popup control
    //@{
    PopupAnimation GetPopupAnimation() const;
    void SetPopupAnimation(PopupAnimation animation);
    //@}

    /// Gets or sets a value that indicates whether the Popup control closes when the control is no
    /// longer in focus. True if the Popup control closes when IsOpen property is set to false;
    /// False if the Popup control closes when a mouse or keyboard event occurs outside the Popup
    /// control. The default is true.
    //@{
    NsBool GetStaysOpen() const;
    void SetStaysOpen(NsBool staysOpen);
    //@}

    /// Get or sets the vertical distance between the target origin and the popup alignment point
    //@{
    NsFloat32 GetVerticalOffset() const;
    void SetVerticalOffset(NsFloat32 offset);
    //@}

    /// Determines if an element is descendant of another in a tree with Popups
    static NsBool IsDescendantOf(Visual* ancestor, Visual* child);

    /// Events
    //@{
    DelegateEvent_<EventHandler> Closed();
    DelegateEvent_<EventHandler> Opened();
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* AllowsTransparencyProperty;
    static const DependencyProperty* ChildProperty;
    static const DependencyProperty* HasDropShadowProperty;
    static const DependencyProperty* HorizontalOffsetProperty;
    static const DependencyProperty* IsOpenProperty;
    static const DependencyProperty* PlacementProperty;
    static const DependencyProperty* PlacementRectangleProperty;
    static const DependencyProperty* PlacementTargetProperty;
    static const DependencyProperty* PopupAnimationProperty;
    static const DependencyProperty* StaysOpenProperty;
    static const DependencyProperty* VerticalOffsetProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Visual
    //@{
    void OnConnectToView(IView* view);
    void OnDisconnectFromView();
    //@}

    /// From UIElement
    //@{
    void OnPreviewMouseLeftButtonDown(const MouseButtonEventArgs& e);
    void OnPreviewMouseLeftButtonUp(const MouseButtonEventArgs& e);
    void OnPreviewMouseRightButtonDown(const MouseButtonEventArgs& e);
    void OnPreviewMouseRightButtonUp(const MouseButtonEventArgs& e);
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
    void OnIsOpenChanged(NsBool isOpen);
    void OnStaysOpenChanged(NsBool staysOpen);
    void OnPreviewMouseButton(const MouseButtonEventArgs& e);

    static void StaticOnPopupLostMouseCapture(BaseComponent* obj, const EventArgs& e);
    void OnPopupLostMouseCapture(const MouseEventArgs& e);

    NsBool IsPopupOpen() const;
    void ShowPopup();
    void HidePopup();

    NsBool CanFireAnimation();
    void FireShowAnimation();
    void FireHideAnimation();

    void MouseCapture();
    void MouseRelease();

    NsBool CoerceIsOpen(const void* isOpen, void* coercedIsOpen) const;
    static NsBool StaticCoerceIsOpen(const DependencyObject* object, const void* isOpen,
        void* coercedIsOpen);
    static NsBool StaticCoerceVisibility(const DependencyObject* object, const void* visibility,
        void* coercedVisibility);

private:
    Ptr<PopupLayer> mPopupLayer;

    EventHandler mClosedEvent;
    EventHandler mOpenedEvent;

    NS_DECLARE_REFLECTION(Popup, FrameworkElement)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
