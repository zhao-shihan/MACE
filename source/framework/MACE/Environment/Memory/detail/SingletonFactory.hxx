#pragma once

#include "MACE/Environment/Memory/Concept/Singletonized.hxx"
#include "MACE/Environment/Memory/detail/SingletonPool.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include <string>
#include <typeinfo>

namespace MACE::Environment::Memory::Detail {

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonFactory final : public FreeSingleton<SingletonFactory> {
public:
    template<Concept::Singletonized ASingleton>
    [[nodiscard]] SingletonPool::Node& InstantiateOrFind();
};

} // namespace MACE::Environment::Memory::Detail

#include "MACE/Environment/Memory/detail/SingletonFactory.inl"
