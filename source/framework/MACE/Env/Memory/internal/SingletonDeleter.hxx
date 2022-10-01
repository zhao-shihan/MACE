#pragma once

#include "MACE/Env/Memory/MuteSingleton.hxx"

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
class SingletonDeleter final : public MuteSingleton<SingletonDeleter> {
public:
    ~SingletonDeleter();
};

} // namespace MACE::Env::Memory::internal
