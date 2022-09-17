#pragma once

#include "MACE/Environment/Memory/MuteSingletonized.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>

namespace MACE::Environment::Memory::internal {

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Memory::MuteSingleton.
/// Not API.
class MuteSingletonPool final : public Utility::NonMoveableBase {
public:
    using Node = ObserverPtr<void>;

public:
    MuteSingletonPool();
    ~MuteSingletonPool();

    static MuteSingletonPool& Instance();

    template<MuteSingletonized AMuteSingleton>
    [[nodiscard]] std::optional<std::reference_wrapper<Node>> Find();
    template<MuteSingletonized AMuteSingleton>
    [[nodiscard]] auto Contains() const { return fInstanceMap.contains(typeid(AMuteSingleton)); }
    [[nodiscard]] Node& Insert(MuteSingletonized auto* instance);

private:
    std::map<const std::type_index, Node> fInstanceMap;

    static ObserverPtr<MuteSingletonPool> fgInstance;
};

} // namespace MACE::Environment::Memory::internal

#include "MACE/Environment/Memory/internal/MuteSingletonPool.inl"
