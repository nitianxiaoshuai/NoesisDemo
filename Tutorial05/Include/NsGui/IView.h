////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IVIEW_H__
#define __GUI_IVIEW_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/InputEnums.h>
#include <NsCore/Interface.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/DelegateForward.h>


NS_SFORWARD(Drawing, Sizei)
NS_CFORWARD(Gui, FrameworkElement)
NS_CFORWARD(Gui, ResourceDictionary)
NS_IFORWARD(Gui, IRenderer)
NS_IFORWARD(Gui, IView)


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum AntialiasingMode
{
    /// Indicates that the antialising algorithm that will be used rely on the multisampling that
    /// is active in the target surface, if any.
    AntialiasingMode_MSAA,

    /// Indicates that besides the multisampling in the target surface a per-primitive algorithm
    /// will be used. PPA implements antialiasing by extruding the contours of the triangles
    /// smoothing them
    AntialiasingMode_PPAA
};


////////////////////////////////////////////////////////////////////////////////////////////////////
enum TessellationQuality
{
    /// The lowest tessellation quality for curves
    TessellationQuality_Low,

    /// Medium tessellation quality for curves
    TessellationQuality_Medium,

    /// The highest tessellation quality for curves
    TessellationQuality_High
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum TessellationMode
{
    /// Tessellation is done only the first time the geometry is rendered
    TessellationMode_Once,

    /// Tessellates geometry always
    TessellationMode_Always,

    /// Tessellates geometry when scale changes by a certain factor
    TessellationMode_Threshold
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum RenderFlags
{
    /// Toggles wireframe mode when rendering triangles
    RenderFlags_Wireframe = 1,
    
    /// Each batch submitted to the GPU is given a unique solid color
    RenderFlags_ColorBatches = 2,

    /// Display pixel overdraw using blending layers. Different colors are used for each type
    /// of triangle. Green for normal, Red for opacities and Blue for clipping masks
    RenderFlags_Overdraw = 4,

    /// Inverts the render vertically
    RenderFlags_FlipY = 8,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct ViewStats
{
    NsFloat32 frameTime;
    NsFloat32 updateTime;
    NsFloat32 renderTime;

    NsSize batches;

    NsSize paths;
    NsSize images;
    NsSize texts;
    NsSize glyphs;
    NsSize masks;

    NsSize triangles;
    NsSize maskTriangles;
    NsSize solidTriangles;
    NsSize linearTriangles;
    NsSize radialTriangles;
    NsSize patternTriangles;

    NsSize fills;
    NsSize strokes;

    NsSize rasterizedGlyphs;
    NsSize uploadedRamps;

    NsSize renderTargetSwitches;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Views manage UI trees
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IView: public Core::Interface
{
    /// Returns the renderer, to be used in the render thread
    virtual IRenderer* GetRenderer() = 0;

    /// Returns the root element
    virtual FrameworkElement* GetContent() const = 0;

    /// Returns the theme resources assigned to this view
    virtual const ResourceDictionary* GetThemeResources() const = 0;

    /// Returns the surface size where this view is being rendered
    virtual const Drawing::Sizei& GetSize() const = 0;

    /// Sets the size of the surface where UI elements will layout and render
    virtual void SetSize(NsSize width, NsSize height) = 0;

    /// Sets antialiasing mode. MSAA is the default
    virtual void SetAntialiasingMode(AntialiasingMode mode) = 0;

    /// Sets tessellation quality. Medium is the default
    virtual void SetTessellationQuality(TessellationQuality quality) = 0;

    /// Sets tessellation mode. Threshold is the default
    virtual void SetTessellationMode(TessellationMode mode) = 0;

    /// Enables debugging flags. No debug flags are active by default
    virtual void SetFlags(NsUInt32 flags) = 0;

    /// Resets mouse, touch and keyboard internal state
    virtual void ResetInputState() = 0;

    /// Notifies that a mouse button was pressed. Origin is in the upper-left corner
    virtual void MouseButtonDown(NsInt x, NsInt y, MouseButton button) = 0;

    /// Notifies that a mouse button was released. Origin is in the upper-left corner
    virtual void MouseButtonUp(NsInt x, NsInt y, MouseButton button) = 0;

    /// Notifies that a mouse button was double clicked. Origin is in the upper-left corner
    virtual void MouseDoubleClick(NsInt x, NsInt y, MouseButton button) = 0;

    /// Notifies that mouse was moved. Origin is in the upper-left corner
    virtual void MouseMove(NsInt x, NsInt y) = 0;

    /// Notifies that mouse wheel was rotated. Origin is in the upper-left corner
    virtual void MouseWheel(NsInt x, NsInt y, NsInt wheelRotation) = 0;

    /// Notifies that a finger touched the screen. Origin is in the upper-left corner
    virtual void TouchDown(NsInt x, NsInt y, NsUInt32 id) = 0;

    /// Notifies that a finger moved on the screen. Origin is in the upper-left corner
    virtual void TouchMove(NsInt x, NsInt y, NsUInt32 id) = 0;

    /// Notifies that a finger raised off of the screen. Origin is in the upper-left corner
    virtual void TouchUp(NsInt x, NsInt y, NsUInt32 id) = 0;

    /// Notifies that a key was pressed
    virtual void KeyDown(Key key) = 0;

    /// Notifies that a key was released
    virtual void KeyUp(Key key) = 0;

    /// Notifies that a key was translated to the corresponding character
    virtual void Char(NsUInt32 ch) = 0;

    /// Performs a layout pass and sends updates to the render tree
    virtual void Update(NsFloat64 timeInSeconds) = 0;

    /// Rendering event occurs after animation and layout have been applied to the composition
    /// tree, just before objects in the composition tree are rendered
    typedef Core::Delegate<void(IView* view)> RenderingEventHandler;
    virtual RenderingEventHandler& Rendering() = 0;

    /// Gets stats counters
    virtual ViewStats GetStats() const = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IView, Core::Interface)
};

}
}


NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::TessellationQuality)


#endif
