////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASESETTER_H__
#define __GUI_BASESETTER_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
class BaseSetter;
template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for value setters.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.setterbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseSetter: public Core::BaseComponent, public IComponentInitializer,
    public IUITreeNode
{
public:
    /// Constructor
    BaseSetter();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~BaseSetter() = 0;

    /// From IComponentInitializer
    //@{
    NsBool IsInitialized() const;
    void Init();
    //@}

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const;
    void SetNodeParent(IUITreeNode* parent);
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const;
    Core::BaseComponent* FindNodeName(const NsChar* name) const;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const;
    //@}

protected:
    virtual void OnInit();

private:
    /// Base classes are non-copyable objects
    //@{
    BaseSetter(const BaseSetter&);
    BaseSetter& operator=(const BaseSetter&);
    //@}

private:
    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(BaseSetter, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
