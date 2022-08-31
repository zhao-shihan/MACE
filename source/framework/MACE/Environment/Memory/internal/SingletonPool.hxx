#pragma once

#include "MACE/Environment/Memory/Concept/Singletonized.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace MACE::Environment::Memory::internal {

class ISingletonBase;

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonPool final : public FreeSingleton<SingletonPool> {
public:
    using Node = Utility::ObserverPtr<void>;
    using BaseNode = const ISingletonBase*;

public:
    template<Concept::Singletonized ASingleton>
    [[nodiscard]] std::optional<std::reference_wrapper<Node>> Find();
    template<Concept::Singletonized ASingleton>
    [[nodiscard]] auto Contains() const { return fInstanceMap.contains(typeid(ASingleton)); }
    [[nodiscard]] Node& Insert(Concept::Singletonized auto* instance);
    [[nodiscard]] std::vector<BaseNode> GetUndeletedInReverseInsertionOrder() const;

private:
    std::map<const std::type_index, std::pair<Node, const std::pair<std::size_t, BaseNode>>> fInstanceMap;
};

} // namespace MACE::Environment::Memory::internal

#include "MACE/Environment/Memory/internal/SingletonPool.inl"
