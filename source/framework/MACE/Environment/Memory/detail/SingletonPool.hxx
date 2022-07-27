#pragma once

#include "MACE/Environment/Memory/Concept/Singletonized.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Utility/NonCopyableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <forward_list>
#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace MACE::Environment::Memory::Detail {

class ISingletonBase;

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonPool final : public FreeSingleton<SingletonPool> {
private:
    using InstanceList = std::forward_list<std::pair<ObserverPtr<void>, ISingletonBase*>>;

public:
    using Node = InstanceList::value_type;
    using Iterator = InstanceList::iterator;
    using ConstIterator = InstanceList::const_iterator;

public:
    template<Concept::Singletonized ASingleton>
    [[nodiscard]] std::optional<std::reference_wrapper<Node>> Find();
    template<Concept::Singletonized ASingleton>
    [[nodiscard]] auto Contains() const { return fTypeMap.contains(typeid(ASingleton)); }
    template<Concept::Singletonized ASingleton>
    [[nodiscard]] Node& Insert(ASingleton* instance);

    auto begin() const { return fInstanceList.cbegin(); }
    auto end() const { return fInstanceList.cend(); }

private:
    InstanceList fInstanceList;
    std::map<const std::type_index, const Iterator> fTypeMap;
};

} // namespace MACE::Environment::Memory::Detail

#include "MACE/Environment/Memory/detail/SingletonPool.inl"
