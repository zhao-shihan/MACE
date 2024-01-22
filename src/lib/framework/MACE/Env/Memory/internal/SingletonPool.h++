#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Env/Memory/Singletonified.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "gsl/gsl"

#include "fmt/format.h"

#include <memory>
#include <stdexcept>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

namespace MACE::Env::Memory::internal {

class SingletonBase;

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
class SingletonPool final : public PassiveSingleton<SingletonPool> {
public:
    ~SingletonPool();

    template<Singletonified ASingleton>
    [[nodiscard]] auto Find() -> std::shared_ptr<void*>;
    template<Singletonified ASingleton>
    [[nodiscard]] auto Contains() const -> auto { return fInstanceMap.contains(typeid(ASingleton)); }
    template<Singletonified ASingleton>
    [[nodiscard]] auto Insert(gsl::not_null<ASingleton*> instance) -> std::shared_ptr<void*>;
    [[nodiscard]] auto GetUndeletedInReverseInsertionOrder() const -> std::vector<gsl::owner<const SingletonBase*>>;

private:
    std::unordered_map<std::type_index, const std::tuple<std::weak_ptr<void*>, gsl::index, gsl::owner<const SingletonBase*>>> fInstanceMap;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/SingletonPool.inl"
