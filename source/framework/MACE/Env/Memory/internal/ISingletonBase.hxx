#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::Singleton.
/// Not API.
/// @details The direct base of Singleton<T>. This allow us to manage instances
/// using polymorphism mechanism.
class ISingletonBase : public NonMoveableBase {
    friend class SingletonDeleter;

protected:
    ISingletonBase() = default;
    virtual ~ISingletonBase() = 0;
};

} // namespace MACE::Env::Memory::internal
