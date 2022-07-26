#pragma once

#include "MACE/Environment/Memory/detail/SingletonFactory.hxx"
#include "MACE/Utility/NonCopyableBase.hxx"

namespace MACE::Environment::Memory::Detail {

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
/// @details The direct base of Singleton<T>. This allow us to manage instances
/// using polymorphism mechanism.
class ISingletonBase : public Utility::NonCopyableBase {
    friend SingletonFactory::~SingletonFactory();

protected:
    ISingletonBase() = default;
    virtual ~ISingletonBase() = 0;
};

} // namespace MACE::Environment::Memory::Detail
