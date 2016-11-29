////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_VISUALTREEHELPER_H__
#define __GUI_VISUALTREEHELPER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Core
{
class TypeClass;
template<class T> class Delegate;
}
namespace Gui
{
class Visual;
class Geometry;
struct HitTestResult;
typedef Noesis::Core::Delegate<void (Visual*)> HitTestDelegate;
}
namespace Drawing
{
struct Rect;
struct Point;
struct Size;
}
//@}

namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides utility methods that perform common tasks involving nodes in a visual tree.
///
/// http://msdn.microsoft.com/en-us/library/System.Windows.Media.VisualTreeHelper.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API VisualTreeHelper
{
    /// Returns the root of the visual tree where the specified visual is
    static Visual* GetRoot(const Visual* visual);

    /// Returns a DependencyObject value that represents the parent of the visual object
    static Visual* GetParent(const Visual* visual);

    /// Returns the number of children that a parent visual contains
    static NsSize GetChildrenCount(const Visual* visual);

    /// Returns the child visual object of a parent at the specified index
    static Visual* GetChild(const Visual* visual, NsSize childIndex);

    /// Returns the cached bounding box rectangle for the Visual
    static Drawing::Rect GetContentBounds(const Visual* visual);
    
    /// Returns the union of all the content bounding boxes for all the descendants of the visual
    /// object, which includes the content bounding box of the Visual
    static Drawing::Rect GetDescendantBounds(const Visual* visual);

    /// Returns the offset of the Visual
    static const Drawing::Point& GetOffset(const Visual* visual);

    /// Returns the offset of the Visual
    static const Drawing::Size& GetSize(const Visual* visual);

    /// Returns the offset of the Visual
    static Geometry* GetClip(const Visual* visual);

    /// Returns the top-most Visual object of a hit test
    static HitTestResult HitTest(Visual* visual, const Drawing::Point& point);
    static HitTestResult HitTest(Visual* visual, const Drawing::Point& point, 
        const HitTestDelegate& hitTestDelegate);
};

}
}

#endif
