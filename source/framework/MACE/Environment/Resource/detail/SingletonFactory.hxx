#pragma once

#include "MACE/Environment/Resource/detail/ISingletonBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <forward_list>
#include <map>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace MACE::Environment {

class BasicEnvironment; // Just a kawaii forward declaration

namespace Resource::Detail {

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Resource::Singleton.
/// Not API.
class SingletonFactory final {
    friend class MACE::Environment::BasicEnvironment;

private:
    SingletonFactory();
    ~SingletonFactory();
    SingletonFactory(const SingletonFactory&) = delete;
    SingletonFactory& operator=(const SingletonFactory&) = delete;

public: // Expose to MACE::Environment::Resource::Singleton
    static auto& Instance() { return *fgInstance; }
    template<class ASingleton>
    void Instantiate();

private:
    std::forward_list<std::pair<ISingletonBase*, ObserverPtr<void>>> fSingletonInstanceList;
    std::map<std::type_index, decltype(fSingletonInstanceList)::iterator> fSingletonTypeCollection;

    static ObserverPtr<SingletonFactory> fgInstance;
};

} // namespace Resource

} // namespace MACE::Environment

#include "MACE/Environment/Resource/detail/SingletonFactory.inl"
