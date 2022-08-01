#pragma once

#include "MACE/Environment/Memory/MuteSingleton.hxx"

namespace MACE::Environment::Memory::Detail {

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
class SingletonDeleter final : public MuteSingleton<SingletonDeleter> {
public:
    ~SingletonDeleter();
};

} // namespace MACE::Environment::Memory::Detail
