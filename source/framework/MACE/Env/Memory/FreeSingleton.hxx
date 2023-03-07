#pragma once

#include "MACE/Env/Memory/FreeSingletonized.hxx"
#include "MACE/Env/Memory/internal/FreeSingletonBase.hxx"
#include "MACE/Env/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Env/Memory/MuteSingleton.hxx"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Env::Memory {

template<class ADerived>
class FreeSingleton : public internal::FreeSingletonBase,
                      public MuteSingleton<ADerived> {
protected:
    FreeSingleton();
    ~FreeSingleton();

public:
    static ADerived& Instance();

private:
    static void FindInstance();

private:
    static ADerived* fgInstance;
};

} // namespace MACE::Env::Memory

#include "MACE/Env/Memory/FreeSingleton.inl"
