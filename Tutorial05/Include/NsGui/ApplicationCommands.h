////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_APPLICATIONCOMMANDS_H__
#define __GUI_APPLICATIONCOMMANDS_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class RoutedUICommand;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a standard set of application related commands.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ApplicationCommands
{
    /// Commands
    //@{
    static const RoutedUICommand* CancelPrintCommand;
    static const RoutedUICommand* CloseCommand;
    static const RoutedUICommand* ContextMenuCommand;
    static const RoutedUICommand* CopyCommand;
    static const RoutedUICommand* CorrectionListCommand;
    static const RoutedUICommand* CutCommand;
    static const RoutedUICommand* DeleteCommand;
    static const RoutedUICommand* FindCommand;
    static const RoutedUICommand* HelpCommand;
    static const RoutedUICommand* NewCommand;
    static const RoutedUICommand* OpenCommand;
    static const RoutedUICommand* PasteCommand;
    static const RoutedUICommand* PrintCommand;
    static const RoutedUICommand* PrintPreviewCommand;
    static const RoutedUICommand* PropertiesCommand;
    static const RoutedUICommand* RedoCommand;
    static const RoutedUICommand* ReplaceCommand;
    static const RoutedUICommand* SaveCommand;
    static const RoutedUICommand* SaveAsCommand;
    static const RoutedUICommand* SelectAllCommand;
    static const RoutedUICommand* StopCommand;
    static const RoutedUICommand* UndoCommand;
    //@}

    NS_DECLARE_REFLECTION(ApplicationCommands, Core::NoParent)
};

}
}


#endif
