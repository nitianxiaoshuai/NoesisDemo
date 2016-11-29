////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPECLASSCREATOR_H__
#define __CORE_TYPECLASSCREATOR_H__


#include <Noesis.h>


namespace Noesis
{
namespace Core
{

/// Forward declarations
//@{
class Type;
class TypeInfo;
class TypeClassBuilder;
class TypeProperty;
class TypeMetaData;
class Symbol;
template<NsInt N> struct Int2Type;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeClassCreator. Helps in the creation of TypeClass reflection.
////////////////////////////////////////////////////////////////////////////////////////////////////
class TypeClassCreator
{
public:
    /// Functions needed to register a new reflection type
    //@{
    /// Creates a TypeClass for the specified class
    template<class ClassT> 
    static Type* Create(const TypeInfo& typeInfo);

    /// Fills TypeClass with members of the class
    template<class ClassT, class BaseT> 
    static void Fill(Type* type);
    //@}

    /// Adds meta data to the type class
    //@{
    template<class T>
    Ptr<T> Meta();

    template<class T, class T1>
    Ptr<T> Meta(T1 t1);

    template<class T, class T1, class T2>
    Ptr<T> Meta(T1 t1, T2 t2);

    template<class T, class T1, class T2, class T3>
    Ptr<T> Meta(T1 t1, T2 t2, T3 t3);

    template<class T, class T1, class T2, class T3, class T4>
    Ptr<T> Meta(T1 t1, T2 t2, T3 t3, T4 t4);
    //@}

    /// Specifies that the class implements the interface T
    template<class ClassT, class T>
    void Impl();

    /// Helper returned to add metadata to properties if needed
    class TypePropertyCreator
    {
    public:
        /// Constructor
        inline TypePropertyCreator(TypeProperty* typeProperty);

        /// Adds meta data to the type property
        //@{
        template<class T>
        TypePropertyCreator& Meta();

        template<class T, class T1>
        TypePropertyCreator& Meta(T1 t1);

        template<class T, class T1, class T2>
        TypePropertyCreator& Meta(T1 t1, T2 t2);

        template<class T, class T1, class T2, class T3>
        TypePropertyCreator& Meta(T1 t1, T2 t2, T3 t3);
        //@}

    private:
        TypeProperty* mTypeProperty;
    };

    /// Adds a property to the type class
    //@{
    template<class ClassT, class T>
    TypePropertyCreator Prop(const NsChar* name, T ClassT::* prop);

    template<class ClassT, class T, NsInt N>
    TypePropertyCreator Prop(const NsChar* name, T (ClassT::* prop)[N]);

    template<class ClassT, class T, NsInt N>
    TypePropertyCreator Prop(const NsChar* name, T (ClassT::* prop)[N], NsSize index);

    template<class T>
    TypePropertyCreator Prop(const NsChar* name, NsSize offset);

    template<class ClassT, class T>
    TypePropertyCreator Prop(const NsChar* name, T (ClassT::*getter)() const);

    template<class ClassT, class T>
    TypePropertyCreator Prop(const NsChar* name, T (ClassT::*getter)() const,
        void (ClassT::*setter)(T));
    //@}

private:
    /// Constructor
    inline TypeClassCreator(TypeClassBuilder* typeClass);

    /// Adds base parent to the type class (only if T is different of NoParent)
    //@{
    template<class ClassT, class T>
    void Base(Int2Type<0>);

    template<class ClassT, class T>
    void Base(Int2Type<1>);
    //@}

private:
    friend class TypeClassTest;

    TypeClassBuilder* mTypeClass;
};

}
}


/// Inline include
#include <NsCore/TypeClassCreator.inl>


#endif
