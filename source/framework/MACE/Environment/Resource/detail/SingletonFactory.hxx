#pragma once

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

namespace Memory::Detail {

class ISingletonBase;

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonFactory final {
    friend class Environment::BasicEnvironment;

private:
    SingletonFactory();
    ~SingletonFactory();
    SingletonFactory(const SingletonFactory&) = delete;
    SingletonFactory& operator=(const SingletonFactory&) = delete;

public: // Expose to MACE::Environment::Memory::Singleton
    using InstanceList = std::forward_list<std::pair<ObserverPtr<void>, ISingletonBase*>>;
    using InstanceNode = InstanceList::value_type;

    static auto& Instance() { return *fgInstance; }
    template<class ASingleton>
    void Instantiate();

private:
    InstanceList fSingletonInstanceList;
    std::map<std::type_index, InstanceList::iterator> fSingletonTypeCollection;

    static ObserverPtr<SingletonFactory> fgInstance;
};

} // namespace Memory::Detail

} // namespace MACE::Environment

#include "MACE/Environment/Resource/detail/SingletonFactory.inl"
