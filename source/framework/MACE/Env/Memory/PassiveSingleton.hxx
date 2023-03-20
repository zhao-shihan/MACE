#pragma once

#include "MACE/Env/Memory/PassiveSingletonized.hxx"
#include "MACE/Env/Memory/internal/PassiveSingletonBase.hxx"
#include "MACE/Env/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Env/Memory/MuteSingleton.hxx"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Env::Memory {

template<class ADerived>
class PassiveSingleton : public internal::PassiveSingletonBase,
                      public MuteSingleton<ADerived> {
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
