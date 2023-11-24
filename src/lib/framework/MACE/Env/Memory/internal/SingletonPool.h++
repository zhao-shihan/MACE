#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Env/Memory/Singletonified.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "gsl/gsl"

#include "fmt/format.h"

#include <functional>
#include <optional>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

namespace MACE::Env::Memory::internal {

class SingletonBase;

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
class SingletonPool final : public PassiveSingleton<SingletonPool> {
public:
    using Node = void*;
    using BaseNode = gsl::owner<const SingletonBase*>;

public:
    template<Singletonified ASingleton>
    [[nodiscard]] auto Find() -> std::optional<std::reference_wrapper<Node>>;
    template<Singletonified ASingleton>
    [[nodiscard]] auto Contains() const -> auto { return fInstanceMap.contains(typeid(ASingleton)); }
    template<Singletonified ASingleton>
    [[nodiscard]] auto Insert(gsl::not_null<ASingleton*> instance) -> Node&;
    [[nodiscard]] auto GetUndeletedInReverseInsertionOrder() const -> std::vector<BaseNode>;

private:
    std::unordered_map<std::type_index, std::pair<Node, const std::pair<gsl::index, BaseNode>>> fInstanceMap;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/SingletonPool.inl"
