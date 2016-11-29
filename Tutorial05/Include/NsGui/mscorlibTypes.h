////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MSCORESYSTEMTYPES_H__
#define __GUI_MSCORESYSTEMTYPES_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IMarkupExtension.h>


namespace Noesis
{
namespace Gui
{

#ifdef NS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4251 4275)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing bool values in xaml
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SystemBoolean: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    Ptr<BaseComponent> mValue;
    
    NS_DECLARE_REFLECTION(SystemBoolean, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing int values in xaml
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SystemInt16: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    Ptr<BaseComponent> mValue;

    NS_DECLARE_REFLECTION(SystemInt16, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing int values in xaml
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SystemInt32: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    Ptr<BaseComponent> mValue;

    NS_DECLARE_REFLECTION(SystemInt32, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing int values in xaml
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SystemUInt16: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    Ptr<BaseComponent> mValue;

    NS_DECLARE_REFLECTION(SystemUInt16, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing int values in xaml
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SystemUInt32: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    Ptr<BaseComponent> mValue;

    NS_DECLARE_REFLECTION(SystemUInt32, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing float values in xaml
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SystemSingle: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    Ptr<BaseComponent> mValue;

    NS_DECLARE_REFLECTION(SystemSingle, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing double values in xaml
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SystemDouble: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    Ptr<BaseComponent> mValue;

    NS_DECLARE_REFLECTION(SystemDouble, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing a string object in xaml
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API SystemString: public Core::BaseComponent, public IMarkupExtension
{
public:
    /// From IMarkupExtension
    //@{
    Ptr<BaseComponent> ProvideValue(const void* context);
    //@}

private:
    Ptr<BaseComponent> mValue;

    NS_DECLARE_REFLECTION(SystemString, Core::BaseComponent)
};

#ifdef NS_COMPILER_MSVC
#pragma warning(pop)
#endif

}
}

#endif
