////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef NS_DELEGATE_PARAMS

#include <NsCore/StaticAssert.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>
#include <EASTL/fixed_vector.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Delegate
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret NS_DELEGATE_COMMA NS_DELEGATE_TEMPLATE_PARAMS>
class Delegate<Ret (NS_DELEGATE_PARAM_TYPES)>
{
public:
    /// Constructor
    Delegate()
    {
        Init();
    }

    /// Constructor from free function
    Delegate(Ret (*func)(NS_DELEGATE_PARAM_TYPES))
    {
        typedef Ret (*F)(NS_DELEGATE_PARAM_TYPES);
        NS_STATIC_ASSERT(sizeof(FreeFuncStub<F>) <= sizeof(data), INSUFFICIENT_SIZE);
        new(data) FreeFuncStub<F>(func);
    }

    /// Constructor from functor (lambdas)
    template<class F> Delegate(F f)
    {
        // TODO: size of functor is limited to the internal static buffer
        NS_STATIC_ASSERT(sizeof(FunctorStub<F>) <= sizeof(data), INSUFFICIENT_SIZE);
        new(data) FunctorStub<F>(f);
    }

    /// Constructor from member function and object
    template<class C> Delegate(C* obj, Ret (C::*func)(NS_DELEGATE_PARAM_TYPES))
    {
        FromMemberFunc(obj, func);
    }

    /// Constructor from member function and object
    template<class C> Delegate(const Ptr<C>& obj, Ret (C::*func)(NS_DELEGATE_PARAM_TYPES))
    {
        FromMemberFunc(obj.GetPtr(), func);
    }

    /// Constructor from member function and const object
    template<class C> Delegate(const Ptr<C>& obj, Ret (C::*func)(NS_DELEGATE_PARAM_TYPES) const)
    {
        FromMemberFunc(obj.GetPtr(), func);
    }

    /// Constructor from member function and const object
    template<class C> Delegate(const C* obj, Ret (C::*func)(NS_DELEGATE_PARAM_TYPES) const)
    {
        FromMemberFunc(obj, func);
    }

    /// Constructor from member function and const object
    template<class C> Delegate(const Ptr<const C>& obj, Ret (C::*func)(NS_DELEGATE_PARAM_TYPES) const)
    {
        FromMemberFunc(obj.GetPtr(), func);
    }

    /// Copy constructor
    Delegate(const Delegate& d)
    {
        Copy(d);
    }

    /// Destructor
    ~Delegate()
    {
        Destroy();
    }

    /// Copy operator
    Delegate& operator=(const Delegate& d)
    {
        if (this != &d)
        {
            Destroy();
            Copy(d);
        }

        return *this;
    }

    /// Reset
    void Reset()
    {
        Destroy();
        Init();
    }

    /// Check if delegate is null
    NsBool Empty() const
    {
        return GetImpl()->Empty();
    }

    /// Boolean conversion
    operator NsBool() const
    {
        return !Empty();
    }

    /// Equality
    NsBool operator==(const Delegate& d) const
    {
        return GetImpl()->Equal(d.GetImpl());
    }

    /// Non-equality
    NsBool operator!=(const Delegate& d) const
    {
        return !(*this == d);
    }

    /// Add delegate
    void Add(const Delegate& d)
    {
        GetImpl()->Add(d);
    }

    /// Add delegate
    void operator+=(const Delegate& d)
    {
        Add(d);
    }

    /// Remove delegate
    void Remove(const Delegate& d)
    {
        GetImpl()->Remove(d);
    }

    /// Remove delegate
    void operator-=(const Delegate& d)
    {
        Remove(d);
    }

    /// Numbers of contained delegates
    NsSize Size() const
    {
        return GetImpl()->Size();
    }

    /// Delegate invocation. In multidelegates the returned value corresponds to the last invocation
    Ret Invoke(NS_DELEGATE_PARAMS) const
    {
        return GetImpl()->Invoke(NS_DELEGATE_PARAM_NAMES);
    }

    /// Delegate invocation
    Ret operator()(NS_DELEGATE_PARAMS) const
    {
        return Invoke(NS_DELEGATE_PARAM_NAMES);
    }

    /// Manual invocation of the ith delegate
    Ret Invoke(NsSize i NS_DELEGATE_COMMA NS_DELEGATE_PARAMS) const
    {
        return GetImpl()->Invoke(i NS_DELEGATE_COMMA NS_DELEGATE_PARAM_NAMES);
    }

private:
    template<class C>
    void FromMemberFunc(C* obj, Ret (C::*func)(NS_DELEGATE_PARAM_TYPES))
    {
        typedef Ret (C::*F)(NS_DELEGATE_PARAM_TYPES);
        NS_STATIC_ASSERT(sizeof(MemberFuncStub<C, F>) <= sizeof(data), INSUFFICIENT_SIZE);
        new(data) MemberFuncStub<C, F>(obj, func);
    }

    template<class C>
    void FromMemberFunc(const C* obj, Ret (C::*func)(NS_DELEGATE_PARAM_TYPES) const)
    {
        typedef Ret (C::*F)(NS_DELEGATE_PARAM_TYPES) const;
        NS_STATIC_ASSERT(sizeof(MemberFuncStub<C, F>) <= sizeof(data), INSUFFICIENT_SIZE);
        new(data) MemberFuncStub<C, F>(const_cast<C*>(obj), func);
    }

    void Init()
    {
        NS_STATIC_ASSERT(sizeof(NullStub) <= sizeof(data), SIZEOF_BUFFER_TOO_SMALL);
        new(data) NullStub();
    }

    class Impl;

    Impl* GetImpl()
    {
        return reinterpret_cast<Impl*>(data);
    }

    const Impl* GetImpl() const
    {
        return reinterpret_cast<const Impl*>(data);
    }

    void Destroy()
    {
        GetImpl()->Destroy();
    }

    void Copy(const Delegate& d)
    {
        d.GetImpl()->Copy(GetImpl());
    }

    typedef Int2Type<0> _0;

    Delegate(const Impl* impl, _0)
    {
        impl->Copy(GetImpl());
    }

    enum Type
    {
        Type_Null,
        Type_FreeFunc,
        Type_Functor,
        Type_MemberFunc,
        Type_MultiDelegate
    };

    class Impl
    {
    public:
        virtual ~Impl() {};

        virtual Type GetType() const = 0;

        virtual NsBool Empty() const = 0;
        virtual NsSize Size() const = 0;

        virtual NsBool Equal(const Impl* impl) const = 0;

        virtual Ret Invoke(NS_DELEGATE_PARAMS) const = 0;
        virtual Ret Invoke(NsSize i NS_DELEGATE_COMMA NS_DELEGATE_PARAMS) const = 0;

        virtual void Copy(Impl* dest) const = 0;

        virtual void Add(const Delegate& delegate) = 0;
        virtual void Remove(const Delegate& delegate) = 0;

        void Destroy()
        {
            this->~Impl();
        }
    };

    /// Implementation for null delegates
    class NullStub: public Impl
    {
    public:
        Type GetType() const
        {
            return Type_Null;
        }

        NsBool Empty() const
        {
            return true;
        }

        NsSize Size() const
        {
            return 0;
        }

        NsBool Equal(const Impl* impl) const
        {
            return GetType() == impl->GetType();
        }

        Ret Invoke(NS_DELEGATE_PARAMS_NONAME) const
        {
            return Ret();
        }

        Ret Invoke(NsSize NS_DELEGATE_COMMA NS_DELEGATE_PARAMS_NONAME) const
        {
            return Ret();
        }

        void Copy(Impl* dest) const
        {
            new(dest) NullStub(*this);
        }

        void Add(const Delegate& d)
        {
            if (!d.Empty())
            {
                this->Destroy();
                d.GetImpl()->Copy(this);
            }
        }

        void Remove(const Delegate& d)
        {
            NS_ASSERT(d.Empty());
        }
    };

    /// Base class implementation for single delegates
    class SingleDelegate: public Impl
    {
    protected:
        NsBool Empty() const
        {
            return false;
        }

        NsSize Size() const
        {
            return 1;
        }

        void Add(const Delegate& d)
        {
            if (!d.Empty())
            {
                NS_ASSERT(!this->Equal(d.GetImpl()));

                Delegate self(this, _0());

                this->Destroy();

                MultiDelegate* multiDelegate = new(this) MultiDelegate();
                multiDelegate->Add(self);
                multiDelegate->Add(d);
            }
        }

        void Remove(const Delegate& d)
        {
            if (!d.Empty())
            {
                NS_ASSERT(this->Equal(d.GetImpl()));
                this->Destroy();
                new(this) NullStub();
            }
        }
    };

    /// Implementation for free functions
    template<class Func> class FreeFuncStub: public SingleDelegate
    {
    public:
        FreeFuncStub(Func func): mFunc(func) {}

        Type GetType() const
        {
            return Type_FreeFunc;
        }

        NsBool Equal(const Impl* impl) const
        {
            const FreeFuncStub* funcStub = static_cast<const FreeFuncStub*>(impl);
            return GetType() == impl->GetType() && mFunc == funcStub->mFunc;
        }

        Ret Invoke(NS_DELEGATE_PARAMS) const
        {
            return mFunc(NS_DELEGATE_PARAM_NAMES);
        }

        Ret Invoke(NsSize i NS_DELEGATE_COMMA NS_DELEGATE_PARAMS) const
        {
            NS_ASSERT(i == 0);
            return mFunc(NS_DELEGATE_PARAM_NAMES);
        }

        void Copy(Impl* dest) const
        {
            new(dest) FreeFuncStub(*this);
        }

    private:
        Func mFunc;
    };

    /// Implementation for functors
    template<class F> class FunctorStub: public SingleDelegate
    {
    public:
        FunctorStub(F f): mFunctor(f) {}

        Type GetType() const
        {
            return Type_Functor;
        }

        NsBool Equal(const Impl*) const
        {
            return false;
        }

        Ret Invoke(NS_DELEGATE_PARAMS) const
        {
            return mFunctor(NS_DELEGATE_PARAM_NAMES);
        }

        Ret Invoke(NsSize i NS_DELEGATE_COMMA NS_DELEGATE_PARAMS) const
        {
            NS_ASSERT(i == 0);
            return mFunctor(NS_DELEGATE_PARAM_NAMES);
        }

        void Copy(Impl* dest) const
        {
            new(dest) FunctorStub(*this);
        }

    private:
        F mFunctor;
    };

    /// Implementation for member functions
    template<class C, class Func> class MemberFuncStub: public SingleDelegate
    {
    public:
        MemberFuncStub(C* obj, Func func): mObj(obj), mFunc(func) {}

        Type GetType() const
        {
            return Type_MemberFunc;
        }

        NsBool Equal(const Impl* impl) const
        {
            const MemberFuncStub* memberStub = static_cast<const MemberFuncStub*>(impl);
            return GetType() == impl->GetType() && mObj == memberStub->mObj &&
                mFunc == memberStub->mFunc;
        }

        Ret Invoke(NS_DELEGATE_PARAMS) const
        {
            return (mObj->*mFunc)(NS_DELEGATE_PARAM_NAMES);
        }

        Ret Invoke(NsSize i NS_DELEGATE_COMMA NS_DELEGATE_PARAMS) const
        {
            NS_ASSERT(i == 0);
            return (mObj->*mFunc)(NS_DELEGATE_PARAM_NAMES);
        }

        void Copy(Impl* dest) const
        {
            new(dest) MemberFuncStub(*this);
        }

    protected:
        C* mObj;
        Func mFunc;
    };

    /// Implementation for MultiDelegates
    class MultiDelegate: public Impl
    {
    public:
        MultiDelegate(): mVector(*new DelegateVector()) {}
        MultiDelegate(const MultiDelegate& d): mVector(*new DelegateVector(*d.mVector.GetPtr())) {}

        Type GetType() const
        {
            return Type_MultiDelegate;
        }

        NsBool Empty() const
        {
            return mVector->v.empty();
        }

        NsSize Size() const
        {
            return mVector->v.size();
        }

        typedef eastl::fixed_vector<Delegate, 2> Delegates;

        NsBool Equal(const Impl* impl) const
        {
            if (GetType() == impl->GetType())
            {
                const MultiDelegate* multiDelegate = static_cast<const MultiDelegate*>(impl);
                return mVector->v == multiDelegate->mVector->v;
            }

            return false;
        }

        class DelegateVector: public BaseComponent
        {
        public:
            DelegateVector(): nestingCount(0), compactPending(0) {}
            DelegateVector(const DelegateVector& o): nestingCount(0), compactPending(0), v(o.v) {}

            struct IsNull
            {
                inline NsBool operator()(const Delegate& d) const
                {
                    return d.Empty();
                }
            };

            // Remove null delegates
            void Compact()
            {
                NS_ASSERT(compactPending == 1);
                NS_ASSERT(nestingCount == 0);
                v.erase(nstl::remove_if(v.begin(), v.end(), IsNull()), v.end());
                compactPending = 0;
            }

            NsUInt16 nestingCount;
            NsUInt16 compactPending;
            Delegates v;
        };

        struct InvokerGuard
        {
            InvokerGuard(const Ptr<DelegateVector>& v): _v(v)
            {
                _v->nestingCount++;
            }

            ~InvokerGuard()
            {
                if (--_v->nestingCount == 0 && _v->compactPending == 1)
                {
                    _v->Compact();
                }
            }

            Ptr<DelegateVector> _v;
        };

        Ret Invoke(NS_DELEGATE_PARAMS) const
        {
            // Hold reference to the vector to avoid it being destructed in the iteration loop
            InvokerGuard guard(mVector);

            const Delegates& v = mVector->v;

            if (v.empty())
            {
                return Ret();
            }
            else
            {
                NsSize numDelegates = v.size();
                for (NsSize i = 0; i < numDelegates - 1; ++i)
                {
                    (v[i])(NS_DELEGATE_PARAM_NAMES);
                }

                // last delegate is used to return a value
                return (v[numDelegates - 1])(NS_DELEGATE_PARAM_NAMES);
            }
        }

        Ret Invoke(NsSize i NS_DELEGATE_COMMA NS_DELEGATE_PARAMS) const
        {
            NS_ASSERT(i < mVector->v.size());
            return mVector->v[i](NS_DELEGATE_PARAM_NAMES);
        }

        void Copy(Impl* dest) const
        {
            new(dest) MultiDelegate(*this);
        }

        void Add(const Delegate& d)
        {
            if (!d.Empty())
            {
                Delegates& v = mVector->v;
                NS_ASSERT(nstl::find(v.begin(), v.end(), d) == v.end());
                v.push_back(d);
            }
        }

        void Remove(const Delegate& d)
        {
            if (!d.Empty())
            {
                Delegates& v = mVector->v;
                typename Delegates::iterator it = nstl::find(v.begin(), v.end(), d);
                NS_ASSERT(it != v.end());
                it->Reset();
                mVector->compactPending = 1;
            }
        }

    private:
        Ptr<DelegateVector> mVector;

    private:
        MultiDelegate& operator=(const MultiDelegate&);
    };

    // All this trickery to avoid heap allocations from the delegate.
    // Only multidelegates are allocating heap memory. This could be optimized with a pool
    class Dummy0 {};
    class Dummy1 {};

    class SingleInheritance: public Dummy0 {};
    class MultipleInheritance: public Dummy0, public Dummy1 {};

    // http://www.gotw.ca/gotw/028.htm 
    union MaxAlign 
    {
        void* voidPointer;
        void (*voidPointerFunc)();
        void (SingleInheritance::*memberFunc0)();
        void (MultipleInheritance::*memberFunc1)();
    };

    static const NsSize MaxSize = sizeof(
        typename MaxSizeType<FreeFuncStub<Ret (*)(NS_DELEGATE_PARAM_TYPES)>,
            typename MaxSizeType<MemberFuncStub<SingleInheritance,
                    Ret (SingleInheritance::*)(NS_DELEGATE_PARAM_TYPES)>,
                MemberFuncStub<MultipleInheritance,
                    Ret (MultipleInheritance::*)(NS_DELEGATE_PARAM_TYPES)> >
                    ::Result >::Result);

    union
    {
        MaxAlign maxAlign;
        NsByte data[MaxSize];
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper functions to deduce automatically the type when creating a delegate
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Ret NS_DELEGATE_COMMA NS_DELEGATE_TEMPLATE_PARAMS>
Delegate<Ret (NS_DELEGATE_PARAM_TYPES)> MakeDelegate(Ret (*func)(NS_DELEGATE_PARAM_TYPES))
{
    return Delegate<Ret (NS_DELEGATE_PARAM_TYPES)>(func);
}

template<class C, class Ret NS_DELEGATE_COMMA NS_DELEGATE_TEMPLATE_PARAMS>
Delegate<Ret (NS_DELEGATE_PARAM_TYPES)> MakeDelegate(C* obj,
    Ret (C::*func)(NS_DELEGATE_PARAM_TYPES))
{
    return Delegate<Ret (NS_DELEGATE_PARAM_TYPES)>(obj, func);
}

template<class C, class Ret NS_DELEGATE_COMMA NS_DELEGATE_TEMPLATE_PARAMS>
Delegate<Ret (NS_DELEGATE_PARAM_TYPES)> MakeDelegate(const Ptr<C>& obj,
    Ret (C::*func)(NS_DELEGATE_PARAM_TYPES))
{
    return Delegate<Ret (NS_DELEGATE_PARAM_TYPES)>(obj, func);
}

template<class C, class Ret NS_DELEGATE_COMMA NS_DELEGATE_TEMPLATE_PARAMS>
Delegate<Ret (NS_DELEGATE_PARAM_TYPES)> MakeDelegate(const C* obj,
    Ret (C::*func)(NS_DELEGATE_PARAM_TYPES) const)
{
    return Delegate<Ret (NS_DELEGATE_PARAM_TYPES)>(obj, func);
}

template<class C, class Ret NS_DELEGATE_COMMA NS_DELEGATE_TEMPLATE_PARAMS>
Delegate<Ret (NS_DELEGATE_PARAM_TYPES)> MakeDelegate(const Ptr<C>& obj,
    Ret (C::*func)(NS_DELEGATE_PARAM_TYPES) const)
{
    return Delegate<Ret (NS_DELEGATE_PARAM_TYPES)>(obj, func);
}

template<class C, class Ret NS_DELEGATE_COMMA NS_DELEGATE_TEMPLATE_PARAMS>
Delegate<Ret (NS_DELEGATE_PARAM_TYPES)> MakeDelegate(const Ptr<const C>& obj,
    Ret (C::*func)(NS_DELEGATE_PARAM_TYPES) const)
{
    return Delegate<Ret (NS_DELEGATE_PARAM_TYPES)>(obj, func);
}

}
}

#endif
