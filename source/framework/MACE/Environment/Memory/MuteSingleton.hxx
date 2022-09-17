#pragma once

#include "MACE/Environment/Memory/MuteSingletonized.hxx"
#include "MACE/Environment/Memory/internal/MuteSingletonBase.hxx"
#include "MACE/Environment/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Environment::Memory {

template<class ADerived>
class FreeSingleton;

using Utility::ObserverPtr;

template<class ADerived>
class MuteSingleton : public internal::MuteSingletonBase {
    friend class FreeSingleton<ADerived>;

protected:
    MuteSingleton();
    ~MuteSingleton();

private:
    static ObserverPtr<internal::MuteSingletonPool::Node> fgInstanceNode;
};

} // namespace MACE::Environment::Memory

#include "MACE/Environment/Memory/MuteSingleton.inl"
