#pragma once

#include "MACE/Env/Memory/MuteSingletonified.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "gsl/gsl"

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::MuteSingleton.
/// Not API.
class MuteSingletonPool final : public NonMoveableBase {
public:
    using Node = void*;

public:
    MuteSingletonPool();
    ~MuteSingletonPool();

    static MuteSingletonPool& Instance();

    template<MuteSingletonified AMuteSingleton>
    [[nodiscard]] std::optional<std::reference_wrapper<Node>> Find();
    template<MuteSingletonified AMuteSingleton>
    [[nodiscard]] auto Contains() const { return fInstanceMap.contains(typeid(AMuteSingleton)); }
    template<MuteSingletonified AMuteSingleton>
    [[nodiscard]] Node& Insert(gsl::not_null<AMuteSingleton*> instance);

private:
    std::map<std::type_index, Node> fInstanceMap;

    static MuteSingletonPool* fgInstance;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/MuteSingletonPool.inl"
