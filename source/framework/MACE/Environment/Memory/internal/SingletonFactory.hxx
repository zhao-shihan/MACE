#pragma once

#include "MACE/Environment/Memory/Singletonized.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Environment/Memory/internal/SingletonPool.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include <string>
#include <typeinfo>

namespace MACE::Environment::Memory::internal {

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonFactory final : public FreeSingleton<SingletonFactory> {
public:
    template<Singletonized ASingleton>
    [[nodiscard]] SingletonPool::Node& InstantiateOrFind();
};

} // namespace MACE::Environment::Memory::internal

#include "MACE/Environment/Memory/internal/SingletonFactory.inl"
