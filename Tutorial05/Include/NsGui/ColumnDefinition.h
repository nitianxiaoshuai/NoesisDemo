////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COLUMNDEFINITION_H__
#define __GUI_COLUMNDEFINITION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/BaseDefinition.h>


namespace Noesis
{
namespace Gui
{

// Forward declaration
class GridLength;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines column-specific properties that apply to Grid elements.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.columndefinition.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ColumnDefinition: public BaseDefinition
{
public:
    /// Constructor
    ColumnDefinition();

    /// Gets or sets column width
    /// \remarks Positive values indicates pixel units
    ///          Negative values indicates percentage of available space (where -1.0 is 100%)
    //@{
    const GridLength& GetWidth() const;
    void SetWidth(const GridLength& width);
    //@}

    /// Gets or sets column minimum width
    //@{
    NsFloat32 GetMinWidth() const;
    void SetMinWidth(NsFloat32 minWidth);
    //@}

    /// Gets or sets column maximum width
    //@{
    NsFloat32 GetMaxWidth() const;
    void SetMaxWidth(NsFloat32 maxWidth);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* WidthProperty;
    static const DependencyProperty* MinWidthProperty;
    static const DependencyProperty* MaxWidthProperty;
    //@}

private:
    NS_DECLARE_REFLECTION(ColumnDefinition, BaseDefinition)
};

}
}

#endif
