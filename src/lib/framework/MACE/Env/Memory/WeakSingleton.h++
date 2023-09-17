#pragma once

#include "MACE/Env/Memory/internal/WeakSingletonBase.h++"
#include "MACE/Env/Memory/internal/WeakSingletonPool.h++"
#include "MACE/Env/Memory/WeakSingletonified.h++"

#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Env::Memory {

template<class ADerived>
class PassiveSingleton;

template<class ADerived>
class WeakSingleton : public internal::WeakSingletonBase {
    friend class PassiveSingleton<ADerived>;

protected:
    WeakSingleton();
    ~WeakSingleton();

private:
    static internal::WeakSingletonPool::Node* fgInstanceNode;
};

} // namespace MACE::Env::Memory

#include "MACE/Env/Memory/WeakSingleton.inl"
