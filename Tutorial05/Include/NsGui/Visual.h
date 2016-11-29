////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1213]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VISUAL_H__
#define __GUI_VISUAL_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/Enums.h>
#include <NsDrawing/Point.h>
#include <NsDrawing/Size.h>
#include <NsDrawing/Rect.h>
#include <NsCore/List.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Gui
{
class Visual;
class DrawingCommands;
class Geometry;
class Brush;
class Transform;
class Projection;
class RenderTreeUpdater;
NS_INTERFACE IView;
}
namespace Math
{
template<class T> class Matrix4;
typedef Noesis::Math::Matrix4<NsFloat32> Matrix4f;
template<class T> class Transform2;
typedef Noesis::Math::Transform2<NsFloat32> Transform2f;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Indicates the visual that was hit in a HitTest operation
////////////////////////////////////////////////////////////////////////////////////////////////////
struct HitTestResult
{
    Visual* visualHit;

    HitTestResult() : visualHit(0) { }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Callback that is called each time a visual is hit in a HitTest operation
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Delegate<void (Visual*)> HitTestDelegate;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides support for: output display (rendering the persisted, serialized drawing 
/// content of a visual), transformations (performing transformations on a visual), clipping 
/// (providing clipping region support for a visual), hit testing (determining whether a 
/// coordinate or geometry is contained within the bounds of a visual), and bounding box
/// calculations (determining the bounding rectangle of a visual).
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.visual.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Visual: public DependencyObject
{
public:
    /// Default constructor
    Visual();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~Visual() = 0;

    /// Determines whether the visual object is an ancestor of the descendant visual object
    /// \remarks This object is not considered to be an ancestor of "visual" if they are the same
    NsBool IsAncestorOf(const Visual* visual) const;

    /// Determines whether the visual object is a descendant of the ancestor visual object
    /// \remarks This object is not considered to be a descendant of "visual" if they are the same
    NsBool IsDescendantOf(const Visual* visual) const;

    /// Finds the common ancestor of two visuals objects
    /// \remarks If "visual" is the same object as this, the common ancestor will be the parent
    Visual* FindCommonVisualAncestor(const Visual* visual) const;

    /// Converts a Point in screen coordinates into a Point that represents the current coordinate
    /// system of the Visual
    Drawing::Point PointFromScreen(const Drawing::Point& point) const;
    
    /// Converts a Point that represents the current coordinate system of the Visual into a Point
    /// in screen coordinates
    Drawing::Point PointToScreen(const Drawing::Point& point) const;

    /// Returns a transform that can be used to transform coordinates from the Visual to the
    /// specified ancestor of the visual object
    Noesis::Math::Matrix4f TransformToAncestor(const Visual* ancestor) const;

    /// Returns a transform that can be used to transform coordinates from the Visual to the
    /// specified visual object descendant
    Noesis::Math::Matrix4f TransformToDescendant(const Visual* descendant) const;

    /// Returns a transform that can be used to transform coordinates from the Visual to the
    /// specified visual object
    Noesis::Math::Matrix4f TransformToVisual(const Visual* visual) const;

    // Raise subtree render commands changed
    typedef Noesis::Core::Delegate<void ()> SubtreeDrawingCommandsChangedDelegate;
    SubtreeDrawingCommandsChangedDelegate& SubtreeDrawingCommandsChanged();

    /// Indicates if this visual is invalidated and should send updates to the render tree
    NsBool IsInvalidated() const;

    /// Indicates if this visual has been connected to a View
    NsBool IsConnectedToView() const;

    /// Enables or disables visual for render
    //@{
    void ConnectToView(IView* view);
    void DisconnectFromView();
    //@}

    /// Gets the view where this visual is connected to
    IView* GetView() const;

    /// Indicates if a render node has been created in the RenderTree for this visual
    NsBool IsInRenderTree() const;

    /// Gets render tree id
    NsSize GetRenderTreeId() const;

    // Pushes all the layout updates into the UI render thread queue to update render nodes
    void UpdateRender(RenderTreeUpdater& updater);

    /// Sets the flag that indicates that this Visual contains a VisualBrush
    void SetVisualBrushFlag();

    /// Disable debug rendering (wireframe, overdraw, etc) for this node and children
    void DisableDebugFlags();

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Protected functions used by child classes or VisualTreeHelper
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //@{
    /// Gets the parent of the visual object
    Visual* GetVisualParent() const;

    /// Sets up the parent-child relationship between two visuals
    void AddVisualChild(Visual* child);

    /// Removes the parent-child relationship between two visuals
    void RemoveVisualChild(Visual* child);

    /// Gets the bounding box rectangle
    Drawing::Rect GetContentBounds() const;

    /// Returns a bounding box that encloses this visual and all its children
    Drawing::Rect GetDescendantBounds() const;

    /// Gets the root of the View tree where this visual is connected to
    /// \return Null if this visual is not connected to a View
    Visual* GetRoot() const;

    /// Gets the surface size of the View where this visual is connected to
    Drawing::Size GetSurfaceSize() const;

    /// Gets or sets the BitmapScalingMode for the Visual
    //@{
    BitmapScalingMode GetVisualBitmapScalingMode() const;
    void SetVisualBitmapScalingMode(BitmapScalingMode mode);
    //@}

    /// Gets or sets the clip region of the Visual as a Geometry value
    //@{
    Geometry* GetVisualClip() const;
    void SetVisualClip(Geometry* clip);
    //@}

    /// Gets or sets the offset value of the visual object
    //@{
    const Drawing::Point& GetVisualOffset() const;
    void SetVisualOffset(const Drawing::Point& offset);
    //@}

    /// Gets or sets the size value of the visual object
    //@{
    const Drawing::Size& GetVisualSize() const;
    void SetVisualSize(const Drawing::Size& size);
    //@}

    /// Gets or sets the opacity of the Visual
    //@{
    NsFloat32 GetVisualOpacity() const;
    void SetVisualOpacity(NsFloat32 opacity);
    //@}

    /// Gets or sets the Brush value that represents the opacity mask of the Visual
    //@{
    Brush* GetVisualOpacityMask() const;
    void SetVisualOpacityMask(Brush* mask);
    //@}

    /// Gets or sets the Transform value for the Visual
    //@{
    Transform* GetVisualTransform() const;
    void SetVisualTransform(Transform* transform);
    //@}

    /// Gets or sets the Transform value for the Visual
    //@{
    Projection* GetVisualProjection() const;
    void SetVisualProjection(Projection* projection);
    //@}

    /// Invalidate visual render commands
    void InvalidateDrawingCommands() const;

    /// Indicates to the visual that content bounds changed
    void InvalidateContentBounds() const;

    /// Invalidates visual if the visual or its children intersect the invalidation rectangle
    void InvalidateRect(const Drawing::Rect& rect) const;

    /// Invalidates children Z-order
    void InvalidateChildrenZOrder() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Protected virtual functions to be reimplemented by child classes
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //@{
    /// Gets the number of child elements for the Visual
    /// \remarks Each visual implementation will decide how to store visual children
    virtual NsSize GetVisualChildrenCount() const;

    /// Returns the specified Visual in the parent VisualCollection
    /// \remarks Each visual implementation will decide how to store visual children
    virtual Visual* GetVisualChild(NsSize index) const;

    /// Called when the VisualCollection of the visual object is modified
    virtual void OnVisualChildrenChanged(Visual* added, Visual* removed);

    /// Called when the parent of the visual object is changed
    virtual void OnVisualParentChanged(Visual* oldParent);

    /// Called when this visual is connected/disconnected to/from a parent that belongs to a View
    //@{
    virtual void OnConnectToView(IView* view);
    virtual void OnDisconnectFromView();
    //@}

    /// Called when children of this visual are connected/disconnected to/from render tree
    //@{
    virtual void OnConnectToViewChildren();
    virtual void OnDisconnectFromViewChildren();
    //@}

    /// Called when the VisualOffset of the visual object is modified
    virtual void OnVisualOffsetChanged();

    /// Called when the VisualSize of the visual object is modified
    virtual void OnVisualSizeChanged();

    /// Called when the VisualTransform of the visual object is modified
    virtual void OnVisualTransformChanged();

    /// Called when the VisualProjection of the visual object is modified
    virtual void OnVisualProjectionChanged();

    /// Gets the bounding box rectangle
    virtual Drawing::Rect GetContentBoundsCore() const;

    /// Function to be implemented by Inheriting classes. This function is invoked whenever
    /// the content bound is hit in a HitTest operation
    virtual HitTestResult HitTestCore(const Drawing::Point& point);

    /// Updates render commands in the corresponding render node
    virtual DrawingCommands* GetDrawingCommands() const;
    //@}

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    NsBool OnSubPropertyChanged(const DependencyProperty* prop);
    //@}

    // Layout requests are stored in the element
    typedef Core::nstl::ListNodeBase* LayoutRequest;

private:
    /// Base classes are non-copyable objects
    //@{
    Visual(const Visual&);
    Visual& operator=(const Visual&);
    //@}

    friend struct VisualTreeHelper;
    friend class VisualCollection;
    friend class ViewLayout;

    void Invalidate();

    /// Invalidates descendant bounds on a branch
    void InvalidateBranchBounds(NsBool raiseDrawingCommandsChanged) const;

    /// Fires SubtreeDrawingCommandsChanged event
    void RaiseSubtreeDrawingCommandsChanged() const;

    Drawing::Point ToProjectedSurface(const Drawing::Point& point, const Math::Matrix4f& m) const;
    Drawing::Point FromProjectedSurface(const Drawing::Point& point, const Math::Matrix4f& m) const;

    Math::Matrix4f InternalTransformToRoot() const;
    Math::Matrix4f InternalTransformToAncestor(const Visual* ancestor,
        const Drawing::Size& surface) const;
    Math::Matrix4f InternalTransformToParent(const Drawing::Size& surface) const;

    /// Returns the topmost Visual object of a hit test by specifying a Point in screen coordinates
    HitTestResult HitTest(const Drawing::Point& point);
    HitTestResult InternalHitTest(const Drawing::Point& point, NsBool isProjectionIdentity,
        const Drawing::Size& surface);

    /// Initiates a hit test on this Visual, with caller-defined HitTestDelegate allowing to
    /// retrieve all of the visuals under the specified point, not just the topmost one.
    HitTestResult HitTest(const Drawing::Point& point, const HitTestDelegate& hitTestDelegate);
    HitTestResult InternalHitTest(const Drawing::Point& point, NsBool isProjectionIdentity,
        const Drawing::Size& surface, const HitTestDelegate& hitTestDelegate);

    // Pushes all the necessary commands into the UI render thread queue to update corresponding
    // render nodes
    //@{
    void UpdateRenderTree(RenderTreeUpdater& updater);
    void UpdateFlags(RenderTreeUpdater& updater);
    void UpdateBounds(RenderTreeUpdater& updater);
    void UpdateTransform(RenderTreeUpdater& updater);
    void UpdateProjection(RenderTreeUpdater& updater);
    void UpdateBitmapScalingMode(RenderTreeUpdater& updater);
    void UpdateClip(RenderTreeUpdater& updater);
    void UpdateOffset(RenderTreeUpdater& updater);
    void UpdateSize(RenderTreeUpdater& updater);
    void UpdateOpacity(RenderTreeUpdater& updater);
    void UpdateOpacityMask(RenderTreeUpdater& updater);
    void UpdateDrawingCommands(RenderTreeUpdater& updater);
    void UpdateChildren(RenderTreeUpdater& updater);

    void CreateRenderNode(RenderTreeUpdater& updater);
    void DestroyRenderNode(RenderTreeUpdater& updater);
    void AddNode(RenderTreeUpdater& updater);
    void RemoveNode(RenderTreeUpdater& updater, NsSize parentIndex);
    void RemoveAllNodes(RenderTreeUpdater& updater);
    //@}

    /// Visual flag management
    //@{
    void SetVisualFlag(NsUInt32 flag) const;
    void ClearVisualFlag(NsUInt32 flag) const;
    NsBool CheckVisualFlag(NsUInt32 flag) const;
    //@}

    /// Manages invalidation of visual in renderer for next update
    //@{
    void AddInvalidatedVisual() const;
    void RemoveInvalidatedVisual() const;
    void CancelUpdateRequest();
    //@}

private:
    IView* mView;
    NsSize mIndex;

    Visual* mVisualParent;
    Drawing::Point mVisualOffset;
    Drawing::Size mVisualSize;

    mutable Drawing::Rect mContentBoundsCache;
    mutable Drawing::Rect mDescendantBoundsCache;

    mutable NsUInt32 mVisualFlags;

    LayoutRequest mUpdateRequest;

    SubtreeDrawingCommandsChangedDelegate mSubtreeDrawingCommandsChanged;

    /// Private properties
    //@{
    static const DependencyProperty* VisualBitmapScalingModeProperty;
    static const DependencyProperty* VisualClipProperty;
    static const DependencyProperty* VisualOpacityProperty;
    static const DependencyProperty* VisualOpacityMaskProperty;
    static const DependencyProperty* VisualTransformProperty;
    static const DependencyProperty* VisualProjectionProperty;
    //@}

    NS_DECLARE_REFLECTION(Visual, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif


}
}

#endif
