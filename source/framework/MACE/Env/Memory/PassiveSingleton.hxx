#pragma once

#include "MACE/Env/Memory/internal/WeakSingletonPool.hxx"
#include "MACE/Env/Memory/internal/PassiveSingletonBase.hxx"
#include "MACE/Env/Memory/WeakSingleton.hxx"
#include "MACE/Env/Memory/PassiveSingletonified.hxx"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Env::Memory {

template<class ADerived>
class PassiveSingleton : public internal::PassiveSingletonBase,
                         public WeakSingleton<ADerived> {
protected:
    PassiveSingleton();
    ~PassiveSingleton();

public:
    static ADerived& Instance();

private:
    static void FindInstance();

private:
    static ADerived* fgInstance;
};

} // namespace MACE::Env::Memory

#include "MACE/Env/Memory/PassiveSingleton.inl"
