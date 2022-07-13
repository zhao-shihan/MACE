#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include <mutex>
#include <vector>

namespace MACE::Utility {

namespace Detail {

class ISingletonBase; // Just a kawaii forward declaration

/// @brief Implementation detail of Singleton<T>. Not API.
class SingletonGC final {
    friend class ISingletonBase;

private:
    SingletonGC();
    ~SingletonGC() = default;
    SingletonGC(const SingletonGC&) = delete;
    SingletonGC& operator=(const SingletonGC&) = delete;

    static void AddInstance(ObserverPtr<ISingletonBase*> ptrToStaticInstancePtr);
    static void DoSingletonGC();

private:
    static std::vector<ObserverPtr<ISingletonBase*>> fgInstancesCollection;
};

/// @brief Implementation detail of Singleton<T>. Not API.
/// @details The direct base of Singleton<T>. Allow to delete instances using
/// polymorphism mechanism early (early: lazy registration of SingletonEarlyGC
/// to std::atexit).
class ISingletonBase {
    friend void SingletonGC::DoSingletonGC();

protected:
    ISingletonBase(ObserverPtr<ISingletonBase*> ptrToStaticInstancePtr);
    virtual ~ISingletonBase() = 0;
    ISingletonBase(const ISingletonBase&) = delete;
    ISingletonBase& operator=(const ISingletonBase&) = delete;
};

} // namespace Detail

/// @brief A helper base class for constructing singleton classes via CRTP.
/// @attention Singleton constructed by this method will create many
/// instances over many dynamic-libraries/executables (or we say the
/// singletoness is dynamic-library-level), since each binary target
/// (library/executable) has its own instance of template specialization.
/// Therefore, there is NO guarantee of singletoness for cross-dynamic-
/// library usage. Use wisely, think wisely!
/// @details This singleton provides a light weight, totally lazy (singleton
/// on heap), and high performance (very fast Instance() call) method of
/// constructing a (maybe series of) singleton class(es). However with som
/// intrinsic defects (see attention).
/// Usage:
/// Step1 (Injection): Inherit this class once (directly or inheritly)
/// and declare the constructor as private/protected. If you don't except
/// the singleton object to be deleted, also declare the destructor as
/// private/protected.
/// Step2 (Confirmation): Declare Singleton<YourSingletonClass>
/// as friend.
/// Step3 (Use the instance): YourSingletonClass::Instance(). This call (thread
/// safely) creates an instance of YourSingletonClass and returns the reference
/// to it.
/// Step4a (RAII delete, nothing need to do by you): The instance is stored in
/// a static manager object Singleton<YourSingletonClass>. When it
/// destructs (at the end of the program), the instance of YourSingletonClass
/// is deleted. If you need to delete manually (not recommended), see below.
/// Step4b (Explicitly delete): Call (anything equivalent to)
/// delete std::addressof(YourSingletonClass::Instance()). This action
/// explicitly deletes the instance of YourSingletonClass and sets the internal
/// pointer to nullptr (prevent RAII double free). This might be done
/// explicitly by you, or by other external libraries. This requires the
/// destructor visible to the public domain. Note that once the instance is
/// deleted, any following call to YourSingletonClass::Instance() has undefined
/// behavior (null pointer dereference).
///
/// Example1 (Typical usage):
///
///   In Example1.hxx:
///
///     class Example1 : public Singleton<Example1> {
///         friend Singleton<Example1>;
///     private:
///         Example1();
///         ~Example1();
///     };
///
///   User's code:
///
///     auto& example1 = Example1::Instance();
///
/// Example2 (Singleton CRTP): Template base class inherits Singleton<T>
/// and inject the actual singleton (daughter) class into the inherited
/// Singleton template. Note that the constructor of base classes also
/// need to be protected, otherwise the singletoness is inconsistent.
///
///   In Example2.hxx:
///
///     template<class T>
///     class Example2Base : public Singleton<T> {
///     protected:
///         Example2Base();
///         ~Example2Base();
///     };
///
///     class Example2 : public Example2Base<Example2> {
///         friend Singleton<Example2>;
///     private:
///         Example2();
///         ~Example2();
///     };
///
///   User's code:
///
///     auto& example2 = Example2::Instance();
///
/// Example3 (Singleton CRTP w/ polymorphism support): The defect of Example2
/// is that when we need to use the polymorphism, since base class Example2Base
/// is a template, the template specializations differs. Therefore there is no
/// way of using the polymorphism of Example2Base. The solution to this is to
/// isolate the CRTP with base class implementation. like this:
///
///   In Example3.hxx:
///
///     // Support of polymorphism preserved
///     class Example3Base {
///     protected:
///         Example3Base();
///         virtual ~Example3Base();
///     public:
///         virtual void Hello() {
///             std::cout << "Hello from base!" << std::endl;
///         }
///     };
///
///     // The true CRTP
///     template<class T>
///     class Example3SingletonBase : public Example3Base
///                                   public Singleton<T> {
///     protected:
///         // using Singleton<T> // useful when at another namespace
///         using Example3Base::Example3Base;
///     };
///
///     class Example3a : public Example3SingletonBase<Example3a> {
///         friend Singleton<Example3a>;
///     private:
///         Example3a();
///         ~Example3a();
///     public:
///         virtual void Hello() {
///             std::cout << "Hello from 3a!" << std::endl;
///         }
///     };
///
///     class Example3b : public Example3SingletonBase<Example3b> {
///         friend Singleton<Example3b>;
///     private:
///         Example3b();
///         ~Example3b();
///     public:
///         virtual void Hello() {
///             std::cout << "Hello from 3b!" << std::endl;
///         }
///     };
///
///   User's code:
///
///     void Foo(Example3Base& bar) { bar.Hello(); }
///
///     Foo(Example3a::Instance()) // Hello from 3a!
///     Foo(Example3b::Instance()) // Hello from 3b!
///
template<class DerivedT>
class Singleton : public Detail::ISingletonBase {
protected:
    Singleton();
    ~Singleton() { fgInstance = nullptr; }

public:
    static bool Instantiated() { return fgInstance != nullptr; }
    static DerivedT& Instance();

private:
    static std::once_flag fgInstantiateOnceFlag;
    static DerivedT* fgInstance;
};

} // namespace MACE::Utility

#include "MACE/Utility/Singleton.inl"
