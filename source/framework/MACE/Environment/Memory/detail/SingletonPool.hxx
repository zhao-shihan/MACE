#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <forward_list>
#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <typeindex>
#include <typeinfo>

namespace MACE::Environment::Memory {

template<class ADerived>
class Singleton;

namespace Detail {

class ISingletonBase;

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonPool final : public Utility::NonCopyableBase {
public:
    using InstanceList = std::forward_list<std::pair<ObserverPtr<void>, ISingletonBase*>>;
    using Node = InstanceList::value_type;
    using Iterator = InstanceList::iterator;
    using ConstIterator = InstanceList::const_iterator;

public:
    SingletonPool() = default;
    ~SingletonPool() = default;

    template<class ASingleton> // clang-format off
        requires std::is_base_of_v<Singleton<ASingleton>, ASingleton>
    std::optional<std::reference_wrapper<Node>> Find() const;                                // clang-format on
    template<class ASingleton> // clang-format off
        requires std::is_base_of_v<Singleton<ASingleton>, ASingleton>
    Node& Push(ASingleton* instance); // clang-format on

    auto begin() const { return fInstanceList.cbegin(); }
    auto end() const { return fInstanceList.cend(); }

private:
    InstanceList fInstanceList;
    std::map<std::type_index, Iterator> fTypeMap;
};

} // namespace Detail

} // namespace MACE::Environment::Memory

#include "MACE/Environment/Memory/detail/SingletonPool.inl"
