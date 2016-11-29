////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ADORNERDECORATOR_H__
#define __GUI_ADORNERDECORATOR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Decorator.h>
#include <NsGui/ILayerManager.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides an adorner layer for elements beneath it in the visual tree.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.documents.adornerdecorator.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API AdornerDecorator: public Decorator, public ILayerManager
{
public:
    /// Constructor
    AdornerDecorator(NsBool logicalChild = true);

    /// Destructor
    ~AdornerDecorator();

    /// From ILayerManager
    //@{
    void AddLayer(Visual* layerRoot);
    void RemoveLayer(Visual* layerRoot);
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit();
    //@}

    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const;
    Visual* GetVisualChild(NsSize index) const;
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

    /// From Decorator
    //@{
    void OnChildChanged(UIElement* oldChild, UIElement* newChild);
    //@}

private:
    struct AdornerLayers;
    Ptr<AdornerLayers> mLayers;

    NS_DECLARE_REFLECTION(AdornerDecorator, Decorator);
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
