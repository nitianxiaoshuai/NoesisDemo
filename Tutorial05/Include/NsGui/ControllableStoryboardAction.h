////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONTROLLABLESTORYBOARDACTION_H__
#define __GUI_CONTROLLABLESTORYBOARDACTION_H__


#include <Noesis.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/TriggerAction.h>
#include <NsCore/String.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{
// Forward declarations
//@{
class Storyboard;
//@}

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Manipulates a Storyboard that has been applied by a BeginStoryboard action.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.controllablestoryboardaction.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API ControllableStoryboardAction: public TriggerAction
{
public:
    ControllableStoryboardAction();
    virtual ~ControllableStoryboardAction() = 0;

    /// Gets or sets the Name of the BeginStoryboard that began the Storyboard you want to
    /// interactively control
    //@{
    const NsChar* GetBeginStoryboardName() const;
    void SetBeginStoryboardName(const NsChar* name);
    //@}

    /// From TriggerAction
    //@{
    void Invoke(FrameworkElement* target, FrameworkElement* nameScope = 0);
    //@}

protected:
    virtual void Invoke(FrameworkElement* target, Storyboard* storyboard) = 0;

private:
    Storyboard* GetStoryboard(FrameworkElement* nameScope) const;

private:
    NsString mBeginStoryboardName;

    NS_DECLARE_REFLECTION(ControllableStoryboardAction, TriggerAction)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
