////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COLLECTIONVIEWSOURCE_H__
#define __GUI_COLLECTIONVIEWSOURCE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
template<class T> class TypedCollection;
class CollectionView;
class ResourceKeyType;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Proxy of CollectionView to be used from XAML files.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.data.collectionviewsource.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API CollectionViewSource: public DependencyObject, public IUITreeNode
{
public:
    CollectionViewSource();
    ~CollectionViewSource();

    /// Gets or sets the desired view type
    //@{
    ResourceKeyType* GetCollectionViewType() const;
    void SetCollectionViewType(ResourceKeyType* type);
    //@}
    
    /// Gets or sets the collection object from which to create this view
    //@{
    Core::BaseComponent* GetSource() const;
    void SetSource(Core::BaseComponent* source);
    //@}
    
    /// Gets the view object that is currently associated with this instance of CollectionViewSource
    //@{
    CollectionView* GetView() const;
    //@}
    
    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}
   
public:
    static const DependencyProperty* CollectionViewTypeProperty;
    static const DependencyProperty* SourceProperty;
    static const DependencyProperty* ViewProperty;
    
protected:
    /// From DependencyObject
    //@{
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue);
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

private:
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(CollectionViewSource, DependencyObject)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif