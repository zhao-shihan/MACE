#pragma once

#include "MACE/Environment/Resource/detail/ISingletonBase.hxx"
#include "MACE/Environment/Resource/detail/SingletonFactory.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Environment::Resource {

using MACE::Utility::ObserverPtr;

/// @brief A helper base class for constructing environmental singleton
/// classes via CRTP (Environmental: singleton in MACE environment).
/// @details This singleton provides a light weight, totally lazy (object
/// on heap), and high performance (Instance() call faster than magic static
/// pattern) method of constructing a (maybe series of) singleton class(es).
/// However it's not a traditional singleton but correlated to environment.
/// The MACE environment handles its object RAII-ly.
/// Usage:
/// Step1 (Inheritance): Inherit this class once (directly or indirectly)
/// and declare the constructor as private/protected. If you don't except
/// the singleton object to be explicitly deleted, also declare the destructor
/// as private/protected.
/// Step2 (Confirmation): Declare MACE::Environment::Resource::SingletonFactory
/// as a friend of your singleton class.
/// Step3 (Use the instance): YourSingletonClass::Instance(). This call (thread
/// unsafely) creates an instance of YourSingletonClass and returns the
/// reference to it.
/// Step4a (RAII delete, nothing need to do by you): The instance is stored in
/// an instance of MACE::Environment::Resource::SingletonFactory which is owned
/// by the instance of MACE::Environment::BasicEnvironment. When it destructs
/// (shoulde at the end of main function), the instance of YourSingletonClass
/// is deleted together with the deletion of singleton factory. If you need to
/// delete manually (not recommended), see below.
/// Step4b (Explicitly delete): Call (anything equivalent to)
/// ```delete std::addressof(YourSingletonClass::Instance())```. This action
/// explicitly deletes the instance of YourSingletonClass and sets the internal
/// pointer to nullptr (prevent RAII double free). This explicit delete action
/// might be done manually by you, or by other external libraries (G4, ROOT,
/// etc.). This requires a public destructor if virtual destuct not performs.
/// Note that once the instance is deleted, any following call to
/// YourSingletonClass::Instance() will throw an exception.
///
/// Example1 (Typical usage):
///
///   In Example1.hxx:
///
///     class Example1 : public Singleton<Example1> {
///         friend class SingletonFactory;
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
///         friend class SingletonFactory;
///     private:
///         Example2();
///         ~Example2();
///     };
///
///   User's code:
///
///     auto& example2 = Example2::Instance();
///
/// Example3 (Singleton CRTP with polymorphism support): The defect of Example2
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
///     class Example3SingletonBase : public Singleton<T>,
///                                   public Example3Base {
///     protected:
///         using Example3Base::Example3Base;
///     };
///
///     class Example3a : public Example3SingletonBase<Example3a> {
///         friend class SingletonFactory;
///     private:
///         Example3a();
///         ~Example3a();
///     public:
///         virtual void Hello() override {
///             std::cout << "Hello from 3a!" << std::endl;
///         }
///     };
///
///     class Example3b : public Example3SingletonBase<Example3b> {
///         friend class SingletonFactory;
///     private:
///         Example3b();
///         ~Example3b();
///     public:
///         virtual void Hello() override {
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
/// @attention Singleton constructed by this method is managed by
/// MACE::Environment::Resource::SingletonFactory, and shares lifetime with
/// MACE::Environment. Call to an Instance() without initialize an environment
/// has undefined behaviour. Use wisely, think wisely!
template<class ADerived>
class Singleton : public Detail::ISingletonBase {
    friend class Detail::SingletonFactory;

protected:
    Singleton();
    virtual ~Singleton();

public:
    static ADerived& Instance();

private:
    static ObserverPtr<ObserverPtr<void>> fgInstanceObjectNodePtr; // Points to a node of instance list in SingletFactory
};

using SingletonFactory = Detail::SingletonFactory;

} // namespace MACE::Environment::Resource

#include "MACE/Environment/Resource/Singleton.inl"
