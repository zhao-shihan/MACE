#pragma once

#include "MACE/Environment/Resource/ISingletonBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <forward_list>
#include <map>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace MACE::Environment::Resource {

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of Singleton<T>. Not API.
class SingletonFactory final {
public:
    SingletonFactory();
    ~SingletonFactory();
    SingletonFactory(const SingletonFactory&) = delete;
    SingletonFactory& operator=(const SingletonFactory&) = delete;

    template<class ASingleton>
    void Instantiate();

private:
    std::forward_list<std::pair<ISingletonBase*, ObserverPtr<void>>> fSingletonInstanceList;
    std::map<std::type_index, decltype(fSingletonInstanceList)::iterator> fSingletonTypeCollection;
};

} // namespace MACE::Environment::Resource

#include "MACE/Environment/Resource/SingletonFactory.inl"
