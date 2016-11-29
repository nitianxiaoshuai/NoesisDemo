////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GEOMETRYGROUP_H__
#define __GUI_GEOMETRYGROUP_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Geometry.h>
#include <NsGui/Enums.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
template<class T> class TypedFreezableCollection;
class DependencyProperty;
class BaseCollection;
struct NotifyCollectionChangedEventArgs;
//@}

typedef Noesis::Gui::TypedFreezableCollection<Noesis::Gui::Geometry> GeometryCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a composite geometry, composed of other Geometry objects. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.geometrygroup.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API GeometryGroup: public Geometry
{
public:
    GeometryGroup();
    ~GeometryGroup();

    /// Gets or sets the GeometryCollection that contains the objects that define this GeometryGroup
    // TODO [srodriguez] Create a GeometryCollection
    //@{
    GeometryCollection* GetChildren() const;
    void SetChildren(GeometryCollection* collection);
    //@}

    /// Gets or sets how the intersecting areas of the objects contained in this GeometryGroup are 
    /// combined.
    //@{
    Gui::FillRule GetFillRule() const;
    void SetFillRule(Gui::FillRule rule);
    //@}

    /// From Geometry
    //@{
    NsBool IsEmpty() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ChildrenProperty;
    static const DependencyProperty* FillRuleProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From Freezable
    //@{
    NsBool FreezeCore(NsBool isChecking);
    //@}

    /// From Geometry
    //@{
    Drawing::Rect GetRenderBoundsOverride(Pen* pen) const;
    NsBool FillContainsOverride(const Drawing::Point& point) const;
    NsBool StrokeContainsOverride(Pen* pen, const Drawing::Point& point) const;
    //@}

private:
    void OnChildrenChanged(Core::BaseComponent* sender,
        const Gui::NotifyCollectionChangedEventArgs& args);
    void RegisterChildren(GeometryCollection* children);
    void RegisterChild(Core::BaseComponent* child);
    void UnregisterChildren(GeometryCollection* children);
    void UnregisterChild(Core::BaseComponent* child);

    void OnChildChanged(Freezable* obj, FreezableEventReason reason);

    void DisconnectChildren();

private:
    enum UpdateFlags
    {
        UpdateFlags_Children = Geometry::UpdateFlags_Sentinel,
        UpdateFlags_FillRule
    };

    typedef NsVector<NsSize> IndexList;
    IndexList mChildIndices;

    NS_DECLARE_REFLECTION(GeometryGroup, Geometry)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
