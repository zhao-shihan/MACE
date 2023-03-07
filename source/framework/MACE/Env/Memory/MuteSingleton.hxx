#pragma once

#include "MACE/Env/Memory/internal/MuteSingletonBase.hxx"
#include "MACE/Env/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Env/Memory/MuteSingletonized.hxx"

#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Env::Memory {

template<class ADerived>
class FreeSingleton;

template<class ADerived>
class MuteSingleton : public internal::MuteSingletonBase {
    friend class FreeSingleton<ADerived>;

protected:
    MuteSingleton();
    ~MuteSingleton();

private:
    static internal::MuteSingletonPool::Node* fgInstanceNode;
};

} // namespace MACE::Env::Memory

#include "MACE/Env/Memory/MuteSingleton.inl"
