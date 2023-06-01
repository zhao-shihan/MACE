#pragma once

#include "MACE/Env/Memory/WeakSingletonified.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "gsl/gsl"

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::WeakSingleton.
/// Not API.
class WeakSingletonPool final : public NonMoveableBase {
public:
    using Node = void*;

public:
    WeakSingletonPool();
    ~WeakSingletonPool();

    static WeakSingletonPool& Instance();

    template<WeakSingletonified AWeakSingleton>
    [[nodiscard]] std::optional<std::reference_wrapper<Node>> Find();
    template<WeakSingletonified AWeakSingleton>
    [[nodiscard]] auto Contains() const { return fInstanceMap.contains(typeid(AWeakSingleton)); }
    template<WeakSingletonified AWeakSingleton>
    [[nodiscard]] Node& Insert(gsl::not_null<AWeakSingleton*> instance);

private:
    std::map<std::type_index, Node> fInstanceMap;

    static WeakSingletonPool* fgInstance;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/WeakSingletonPool.inl"
