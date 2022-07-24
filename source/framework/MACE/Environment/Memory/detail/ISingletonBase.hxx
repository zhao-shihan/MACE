#pragma once

namespace MACE::Environment::Memory::Detail {

/// @brief Implementation detail of MACE::Environment::Memory::Singleton.
/// Not API.
/// @details The direct base of Singleton<T>. This allow us to manage instances
/// using polymorphism mechanism.
class ISingletonBase {
    friend class SingletonFactory;

protected:
    ISingletonBase() = default;
    virtual ~ISingletonBase() = 0;
    ISingletonBase(const ISingletonBase&) = delete;
    ISingletonBase& operator=(const ISingletonBase&) = delete;
};

} // namespace MACE::Environment::Memory::Detail
