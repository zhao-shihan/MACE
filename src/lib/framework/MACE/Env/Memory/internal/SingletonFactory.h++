#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Env/Memory/Singletonified.h++"
#include "MACE/Env/Memory/internal/SingletonPool.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include <string>
#include <typeinfo>

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
class SingletonFactory final : public PassiveSingleton<SingletonFactory> {
public:
    template<Singletonified ASingleton>
    [[nodiscard]] auto InstantiateOrFind() -> SingletonPool::Node&;
};

} // namespace MACE::Env::Memory::internal

#include "MACE/Env/Memory/internal/SingletonFactory.inl"
