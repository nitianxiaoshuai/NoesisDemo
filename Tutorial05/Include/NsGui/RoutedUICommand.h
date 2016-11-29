////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ROUTEDUICOMMAND_H__
#define __GUI_ROUTEDUICOMMAND_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/RoutedCommand.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A command that is routed through the element tree and contains a text property.
///
/// The following built-in commands are available in the *ApplicationCommands* class:
///
/// * CancelPrint, Close, ContextMenu, Copy, CorrectionList, Cut, Delete, Find, Help, New, Open,
///   Paste, Print, PrintPreview, Properties, Redo, Replace, Save, SaveAs, SelectAll, Stop, Undo
///
/// The following built-in commands are available in the *ComponentCommands* class:
///
/// * ExtendSelectionDown, ExtendSelectionLeft, ExtendSelectionRight, ExtendSelectionUp,
///   MoveDown, MoveFocusBack, MoveFocusDown, MoveFocusForward, MoveFocusPageDown, MoveFocusPageUp,
///   MoveFocusUp, MoveLeft, MoveRight, MoveToEnd, MoveToHome, MoveToPageDown, MoveToPageUp,
///   MoveUp, ScrollByLine, ScrollPageDown, ScrollPageLeft, ScrollPageRight, ScrollPageUp,
///   SelectToEnd, SelectToHome, SelectToPageDown, SelectToPageUp
///
/// .. code-block:: xml
///
///     <Grid
///       xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///       xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
///         <DockPanel Width="300" Height="300" Background="#505860">
///             <Menu DockPanel.Dock="Top">
///                 <MenuItem Header="File"/>
///                 <MenuItem Header="Edit">
///                     <MenuItem Header="Copy" Command="ApplicationCommands.Copy"/>
///                     <MenuItem Header="Cut" Command="ApplicationCommands.Cut"/>
///                     <MenuItem Header="Paste" Command="ApplicationCommands.Paste"/>
///                 </MenuItem>
///                 <MenuItem Header="Help"/>
///             </Menu>
///         </DockPanel>
///     </Grid>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.input.routeduicommand.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RoutedUICommand: public RoutedCommand
{
public:
    /// Constructor
    /// \remarks Argument text must be a static string, because only pointer is stored
    RoutedUICommand(const NsChar* text, NsSymbol name, const Core::TypeClass* owner,
        InputGestureCollection* inputGestures);

    /// Destructor
    ~RoutedUICommand();

    /// Creates an UI routed command
    //@{
    static Ptr<RoutedUICommand> Create(const NsChar* name, const NsChar* text,
        const Core::TypeClass* owner);
    static Ptr<RoutedUICommand> Create(const NsChar* name, const NsChar* text,
        const Core::TypeClass* owner, InputGesture* inputGesture);
    static Ptr<RoutedUICommand> Create(const NsChar* name, const NsChar* text,
        const Core::TypeClass* owner, InputGesture* inputGesture1, InputGesture* inputGesture2);
    //@}

    /// Gets or sets the text that describes this command
    //@{
    const NsChar* GetText() const;
    void SetText(const NsChar* text);
    //@}

private:
    const NsChar* mText;

    NS_DECLARE_REFLECTION(RoutedUICommand, RoutedCommand)
};

}
}


#endif
