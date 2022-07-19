#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

namespace MACE::Environment::Resource::Detail {

using MACE::Utility::ObserverPtr;

/// @brief Implementation detail of MACE::Environment::Resource::Singleton.
/// Not API.
/// @details The direct base of Singleton<T>. This allow us to manage instances
/// using polymorphism mechanism.
class ISingletonBase {
    friend class SingletonFactory;

protected:
    ISingletonBase();
    virtual ~ISingletonBase() = 0;
    ISingletonBase(const ISingletonBase&) = delete;
    ISingletonBase& operator=(const ISingletonBase&) = delete;

private:
    ObserverPtr<ISingletonBase*> fInstanceBaseNodePtr; // Points to a node of instance list in SingletFactory
};

} // namespace MACE::Environment::Resource
