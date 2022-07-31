#pragma once

#include "MACE/Environment/Memory/Concept/FreeSingletonized.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>

namespace MACE::Environment::Memory {

template<class ADerived>
class FreeSingleton;

namespace Detail {

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Memory::FreeSingleton.
/// Not API.
class FreeSingletonPool final : private Utility::NonMoveableBase {
public:
    using Node = ObserverPtr<void>;

public:
    FreeSingletonPool();
    ~FreeSingletonPool();

    static FreeSingletonPool& Instance();

    template<Concept::FreeSingletonized AFreeSingleton>
    [[nodiscard]] std::optional<std::reference_wrapper<Node>> Find();
    template<Concept::FreeSingletonized AFreeSingleton>
    [[nodiscard]] auto Contains() const { return fInstanceMap.contains(typeid(AFreeSingleton)); }
    template<Concept::FreeSingletonized AFreeSingleton>
    [[nodiscard]] Node& Insert(AFreeSingleton* instance);

private:
    std::map<const std::type_index, Node> fInstanceMap;

    static ObserverPtr<FreeSingletonPool> fgInstance;
};

} // namespace Detail

} // namespace MACE::Environment::Memory

#include "MACE/Environment/Memory/detail/FreeSingletonPool.inl"
