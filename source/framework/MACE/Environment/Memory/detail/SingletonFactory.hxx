#pragma once

#include "MACE/Environment/Memory/detail/SingletonPool.hxx"
#include "MACE/Utility/NonCopyableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <concepts>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace MACE::Environment::Memory::Detail {

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonFactory final : public Utility::NonCopyableBase {
public:
    SingletonFactory();
    ~SingletonFactory();

    static auto& Instance() { return *fgInstance; }
    template<class ASingleton>
    void Instantiate();

private:
    SingletonPool fInstancePool;

    static ObserverPtr<SingletonFactory> fgInstance;
};

} // namespace MACE::Environment::Memory::Detail

#include "MACE/Environment/Memory/detail/SingletonFactory.inl"
