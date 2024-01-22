#pragma once

#include "MACE/Env/Memory/WeakSingletonified.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "gsl/gsl"

#include "fmt/format.h"

#include <cstdio>
#include <stdexcept>
#include <string>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::WeakSingleton.
/// Not API.
class WeakSingletonPool final : public NonMoveableBase {
public:
    WeakSingletonPool();
    ~WeakSingletonPool();

    static auto Instance() -> WeakSingletonPool&;

    template<WeakSingletonified AWeakSingleton>
    [[nodiscard]] auto Find() -> std::shared_ptr<void*>;
    template<WeakSingletonified AWeakSingleton>
    [[nodiscard]] auto Contains() const -> auto { return fInstanceMap.contains(typeid(AWeakSingleton)); }
    template<WeakSingletonified AWeakSingleton>
    [[nodiscard]] auto Insert(gsl::not_null<AWeakSingleton*> instance) ->  std::shared_ptr<void*>;

private:
    std::unordered_map<std::type_index, const std::weak_ptr<void*>> fInstanceMap;

    static WeakSingletonPool* fgInstance;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/WeakSingletonPool.inl"
