////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VISUALBRUSH_H__
#define __GUI_VISUALBRUSH_H__


#include <Noesis.h>
#include <NsGui/TileBrush.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class Visual;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Paints an area with a Visual.
///
/// Current VisualBrush implementation only works when the referred Visual is contained within
/// the logical tree.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.visualbrush.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API VisualBrush: public TileBrush
{
public:
    /// Default constructor
    VisualBrush();
    
    /// Destructor
    ~VisualBrush();

    /// Gets or sets the brush's content
    //@{
    Visual* GetVisual() const;
    void SetVisual(Visual* visual);
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* VisualProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    void OnVisualChanged();
    NsSize UpdateVisual(RenderTreeUpdater& updater);

private:
    enum UpdateFlags
    {
        UpdateFlags_Visual = TileBrush::UpdateFlags_Sentinel
    };

    NsBool mUpdatingVisual;

    NS_DECLARE_REFLECTION(VisualBrush, TileBrush)
};

}
}

#endif
