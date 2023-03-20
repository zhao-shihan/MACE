#pragma once

#include "MACE/Env/Memory/PassiveSingleton.hxx"
#include "MACE/Env/Memory/Singletonized.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "gsl/gsl"

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
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
    template<Singletonized ASingleton>
    [[nodiscard]] std::optional<std::reference_wrapper<Node>> Find();
    template<Singletonized ASingleton>
    [[nodiscard]] auto Contains() const { return fInstanceMap.contains(typeid(ASingleton)); }
    template<Singletonized ASingleton>
    [[nodiscard]] Node& Insert(gsl::not_null<ASingleton*> instance);
    [[nodiscard]] std::vector<BaseNode> GetUndeletedInReverseInsertionOrder() const;

private:
    std::map<const std::type_index, std::pair<Node, const std::pair<gsl::index, BaseNode>>> fInstanceMap;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/SingletonPool.inl"
