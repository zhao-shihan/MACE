#pragma once

#include "MACE/Env/Memory/WeakSingleton.hxx"

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
class SingletonDeleter final : public WeakSingleton<SingletonDeleter> {
public:
    ~SingletonDeleter();
};

} // namespace MACE::Env::Memory::internal
