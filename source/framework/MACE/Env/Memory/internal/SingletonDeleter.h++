#pragma once

#include "MACE/Env/Memory/WeakSingleton.h++"

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
class SingletonDeleter final : public WeakSingleton<SingletonDeleter> {
public:
    ~SingletonDeleter();
};

} // namespace MACE::Env::Memory::internal
