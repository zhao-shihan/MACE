#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

namespace MACE::Environment::Memory::Internal {

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
/// @details The direct base of Singleton<T>. This allow us to manage instances
/// using polymorphism mechanism.
class ISingletonBase : public Utility::NonMoveableBase {
    friend class SingletonDeleter;

protected:
    ISingletonBase() = default;
    virtual ~ISingletonBase() = 0;
};

} // namespace MACE::Environment::Memory::Detail
