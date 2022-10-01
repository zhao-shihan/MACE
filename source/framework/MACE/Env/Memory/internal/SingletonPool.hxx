#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"
#include "MACE/Env/Memory/Singletonized.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace MACE::Env::Memory::internal {

class ISingletonBase;

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
class SingletonPool final : public FreeSingleton<SingletonPool> {
public:
    using Node = Utility::ObserverPtr<void>;
    using BaseNode = const ISingletonBase*;

public:
    template<Singletonized ASingleton>
    [[nodiscard]] std::optional<std::reference_wrapper<Node>> Find();
    template<Singletonized ASingleton>
    [[nodiscard]] auto Contains() const { return fInstanceMap.contains(typeid(ASingleton)); }
    [[nodiscard]] Node& Insert(Singletonized auto* instance);
    [[nodiscard]] std::vector<BaseNode> GetUndeletedInReverseInsertionOrder() const;

private:
    std::map<const std::type_index, std::pair<Node, const std::pair<std::size_t, BaseNode>>> fInstanceMap;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/SingletonPool.inl"
