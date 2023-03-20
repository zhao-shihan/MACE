#pragma once

#include "MACE/Env/Memory/internal/MuteSingletonBase.hxx"
#include "MACE/Env/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Env/Memory/MuteSingletonified.hxx"

#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Env::Memory {

template<class ADerived>
class PassiveSingleton;

template<class ADerived>
class MuteSingleton : public internal::MuteSingletonBase {
    friend class PassiveSingleton<ADerived>;

protected:
    MuteSingleton();
    ~MuteSingleton();

private:
    static internal::MuteSingletonPool::Node* fgInstanceNode;
};

} // namespace MACE::Env::Memory

#include "MACE/Env/Memory/MuteSingleton.inl"
