////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IMAGEBRUSH_H__
#define __GUI_IMAGEBRUSH_H__


#include <Noesis.h>
#include <NsGui/TileBrush.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Gui
{
class ImageSource;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Paints an area with an image.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.imagebrush.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ImageBrush: public TileBrush
{
public:
    /// Default constructor
    ImageBrush();
    ImageBrush(ImageSource* imageSource);

    /// Destructor
    ~ImageBrush();

    /// Gets or sets image source file
    //@{
    ImageSource* GetImageSource() const;
    void SetImageSource(ImageSource* imageSource);
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ImageSourceProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    NsBool OnSubPropertyChanged(const DependencyProperty* dp);
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_ImageSource = TileBrush::UpdateFlags_Sentinel,
    };

    NS_DECLARE_REFLECTION(ImageBrush, TileBrush)
};

}
}

#endif
