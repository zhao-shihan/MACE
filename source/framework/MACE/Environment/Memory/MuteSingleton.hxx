#pragma once

#include "MACE/Environment/Memory/Concept/MuteSingletonized.hxx"
#include "MACE/Environment/Memory/detail/MuteSingletonBase.hxx"
#include "MACE/Environment/Memory/detail/MuteSingletonPool.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace MACE::Environment::Memory {

template<class ADerived>
class FreeSingleton;

using Utility::ObserverPtr;

template<class ADerived>
class MuteSingleton : private Detail::MuteSingletonBase {
    friend class FreeSingleton<ADerived>;

protected:
    MuteSingleton();
    ~MuteSingleton();

private:
    static ObserverPtr<Detail::MuteSingletonPool::Node> fgInstanceNode;
};

} // namespace MACE::Environment::Memory

#include "MACE/Environment/Memory/MuteSingleton.inl"
