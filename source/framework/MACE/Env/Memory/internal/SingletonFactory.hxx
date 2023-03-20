#pragma once

#include "MACE/Env/Memory/PassiveSingleton.hxx"
#include "MACE/Env/Memory/internal/SingletonPool.hxx"
#include "MACE/Env/Memory/Singletonified.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include <string>
#include <typeinfo>

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
class SingletonFactory final : public PassiveSingleton<SingletonFactory> {
public:
    template<Singletonified ASingleton>
    [[nodiscard]] SingletonPool::Node& InstantiateOrFind();
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/SingletonFactory.inl"
