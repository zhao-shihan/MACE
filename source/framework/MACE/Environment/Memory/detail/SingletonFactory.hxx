#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <forward_list>
#include <map>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace MACE::Environment {

class BasicEnvironment;

namespace Memory {

template<class T>
class Singleton;

namespace Detail {

class ISingletonBase;

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonFactory final : public Utility::NonCopyableBase {
    friend class Environment::BasicEnvironment;
    template<class T>
    friend class Memory::Singleton;

private:
    using InstanceList = std::forward_list<std::pair<ObserverPtr<void>, ISingletonBase*>>;
    using InstanceNode = InstanceList::value_type;

private:
    SingletonFactory();
    ~SingletonFactory();

    static auto& Instance() { return *fgInstance; }
    template<class ASingleton>
    void Instantiate();

private:
    InstanceList fSingletonInstanceList;
    std::map<std::type_index, InstanceList::iterator> fSingletonTypeCollection;

    static ObserverPtr<SingletonFactory> fgInstance;
};

} // namespace Detail

} // namespace Memory

} // namespace MACE::Environment

#include "MACE/Environment/Memory/detail/SingletonFactory.inl"
