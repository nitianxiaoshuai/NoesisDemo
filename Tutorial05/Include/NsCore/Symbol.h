////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #518]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_SYMBOL_H__
#define __CORE_SYMBOL_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/NSTLForwards.h>
#include <NsCore/Functional.h>


// These functions are to be used from the debugger Watch Window to convert symbols to strings
//  and vice versa while debugging.
// Use the following syntax in Microsoft Visual Studio:
//
//  {,,Core.Kernel.dll}NsSymbolToString(1146)
//  {,,Core.Kernel.dll}NsStringToSymbol("DiskFileSystem")
//@{
extern "C" NS_CORE_KERNEL_API const NsChar* NsSymbolToString(NsUInt32 id);
extern "C" NS_CORE_KERNEL_API NsUInt32 NsStringToSymbol(const NsChar* str);
//@}


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper macros for using symbols. The macro NS_DECLARE_SYMBOL implements a static symbol and
/// the NSS macro reuse that symbol.
///
/// NS_DECLARE_SYMBOL(name)
/// 
/// void Test()
/// {
///     NsSymbol sym = NSS(name);
/// }
///
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_DECLARE_SYMBOL(id) \
    namespace \
    { \
        Noesis::Core::Symbol __sSymbol##id; \
    }

#define NSS(id) ((__sSymbol##id) == 0 ? ((__sSymbol##id.SetId( \
    Noesis::Core::Symbol::IdOfStaticString(#id)))): (__sSymbol##id))

/// Enumeration used when a symbol is created from a string
enum CreationMode
{
    // This mode indicates that a new symbol is created if it doesn't exist previously
    CreationMode_Add,
    // This mode indicates that if the symbol is not found it is not created and a null symbol is
    //  returned
    CreationMode_Dont_Add
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A symbol represents a shared string that is stored in a symbol table. Each string stored in that
/// table is represented uniquely by an index. A symbol stores that index. That way the size of a
/// symbol is sizeof(NsUInt32) and comparison operators can be implemented very efficiently.
///
/// Symbols are used in Noesis to represent strings defined at compile time.
///
/// Symbols are case-insensitive.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API Symbol
{
public:
    /// Constructor
    inline Symbol();
    
    /// Constructor
    explicit Symbol(const NsChar* str, CreationMode creationMode = CreationMode_Add);

    /// Constructor
    explicit Symbol(const NsString& str, CreationMode creationMode = CreationMode_Add);

    /// Constructor
    explicit Symbol(NsUInt32 index);

    /// Gets symbol string
    const NsChar* GetStr() const;

    /// Gets symbol identifier
    inline NsUInt32 GetId() const;
    
    /// Sets symbol identifier
    inline Symbol& SetId(NsUInt32 id);

    /// Checks if this symbol is the empty string
    inline NsBool IsNull() const;

    /// Comparison operators
    //@{
    inline NsBool operator==(const Symbol& symbol) const;
    inline NsBool operator!=(const Symbol& symbol) const;
    inline NsBool operator<(const Symbol& symbol) const;
    inline NsBool operator>(const Symbol& symbol) const;
    inline NsBool operator<=(const Symbol& symbol) const;
    inline NsBool operator>=(const Symbol& symbol) const;
    //@}
    
    /// conversion to int
    inline operator NsUInt32() const;

    /// Gets the null symbol (representing an empty string)
    inline static Symbol Null();
    
    /// Returns the identifier associated to the static string str (creates a new one if it doesn't 
    /// exist). Function used by the NSS macro
    static NsUInt32 IdOfStaticString(const NsChar* str);

private:
    NsUInt32 mIndex;
};

/// Dump information to the console about the symbols currently generated
NS_CORE_KERNEL_API void DumpSymbols();

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Hash function
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace eastl
{
template<> struct hash<Noesis::Core::Symbol>
{
    size_t operator()(const Noesis::Core::Symbol& s) const
    {
        return s.GetId();
    }
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Global access of symbol type.
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Core::Symbol NsSymbol;

// Inline include
#include <NsCore/Symbol.inl>

#endif
