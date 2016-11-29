////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BEGINSTORYBOARD_H__
#define __GUI_BEGINSTORYBOARD_H__


#include <Noesis.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/TriggerAction.h>
#include <NsGui/HandoffBehavior.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/String.h>


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
/// A trigger action that begins a Storyboard and distributes its animations to their targeted 
/// objects and properties.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.beginstoryboard.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API BeginStoryboard: public TriggerAction
{
public:
    BeginStoryboard();

    /// Gets or sets the proper hand-off behavior to start an animation clock in this storyboard
    //@{
    HandoffBehavior GetHandoffBehavior() const;
    void SetHandoffBehavior(HandoffBehavior behavior);
    //@}

    /// Gets or sets the name of the BeginStoryboard object. By naming the BeginStoryboard object,
    /// the Storyboard can be controlled after it is started
    //@{
    const NsChar* GetName() const;
    void SetName(const NsChar* name);
    //@}

    /// Gets or sets the Storyboard that this BeginStoryboard starts
    //@{
    Storyboard* GetStoryboard() const;
    void SetStoryboard(Storyboard* storyboard);
    //@}

    /// From TriggerAction
    //@{
    void Invoke(FrameworkElement* target, FrameworkElement* nameScope = 0);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* StoryboardProperty;
    //@}

private:
    HandoffBehavior mHandoffBehavior;
    NsString mName;

    NS_DECLARE_REFLECTION(BeginStoryboard, TriggerAction)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}


#endif
