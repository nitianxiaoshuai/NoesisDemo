////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #911]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IMARKUPEXTENSION_H__
#define __GUI_IMARKUPEXTENSION_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{
// Forward declarations
//@{
namespace Core
{
class BaseComponent;
template<class T> class Ptr;
}
using Core::Ptr;
//@}

namespace Gui
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// IMarkupExtension: Markup extensions return objects based on string attribute values in XAML,
/// similar to type converters but more powerful. Markups are enclosed in curly braces {}
///
/// Example:
///      <Path Fill="{StaticResource GlyphBrush}"
///            Data="{Binding Path=Content, RelativeSource={RelativeSource TemplatedParent}}"/>
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IMarkupExtension: public Core::Interface
{
public:
    /// Gets the value resulting of evaluating the expression.
    /// \param context Markup extensions can require a context at runtime. For example, a
    ///                ValueTargetProvider or XamlReaderProvider
    /// \return Provided value; can be null.
    virtual Ptr<Core::BaseComponent> ProvideValue(const void* context) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IMarkupExtension, Core::Interface)
};

}
}

#endif