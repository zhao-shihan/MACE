#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
/// @details The direct base of Singleton<T>. This allow us to manage instances
/// using polymorphism mechanism.
class SingletonBase : public NonMoveableBase {
    friend class SingletonDeleter;

protected:
    SingletonBase() = default;
    virtual ~SingletonBase() = default;
};

} // namespace MACE::Env::Memory::internal
