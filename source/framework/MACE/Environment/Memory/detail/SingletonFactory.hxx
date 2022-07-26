#pragma once

#include "MACE/Environment/Memory/Concept/Singletonized.hxx"
#include "MACE/Environment/Memory/detail/SingletonPool.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Utility/NonCopyableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <string>
#include <typeinfo>

namespace MACE::Environment::Memory::Detail {

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonFactory final : public FreeSingleton<SingletonFactory> {
public:
    ~SingletonFactory();

    template<Concept::Singletonized ASingleton>
    [[nodiscard]] auto Instantiated() const { return fInstancePool.Contains<ASingleton>(); }
    template<Concept::Singletonized ASingleton>
    [[nodiscard]] SingletonPool::Node& InstantiateOrFind();

private:
    SingletonPool fInstancePool;
};

} // namespace MACE::Environment::Memory::Detail

#include "MACE/Environment/Memory/detail/SingletonFactory.inl"
