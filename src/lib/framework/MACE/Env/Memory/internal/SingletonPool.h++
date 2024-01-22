#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Env/Memory/Singletonified.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "gsl/gsl"

#include "fmt/format.h"

#include <functional>
#include <optional>
#include <stdexcept>
#include <tuple>
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
    template<Singletonified ASingleton>
    [[nodiscard]] auto Find() -> std::optional<std::reference_wrapper<void*>>;
    template<Singletonified ASingleton>
    [[nodiscard]] auto Contains() const -> auto { return fInstanceMap.contains(typeid(ASingleton)); }
    template<Singletonified ASingleton>
    [[nodiscard]] auto Insert(gsl::not_null<ASingleton*> instance) -> void*&;
    [[nodiscard]] auto GetUndeletedInReverseInsertionOrder() const -> std::vector<gsl::owner<const SingletonBase*>>;

private:
    std::unordered_map<std::type_index, std::tuple<void*, const gsl::index, const gsl::owner<const SingletonBase*>>> fInstanceMap;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/SingletonPool.inl"
