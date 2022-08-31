#pragma once

#include "MACE/Environment/Memory/Concept/FreeSingletonized.hxx"
#include "MACE/Environment/Memory/internal/FreeSingletonBase.hxx"
#include "MACE/Environment/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Environment/Memory/MuteSingleton.hxx"

#include <cassert>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Environment::Memory {

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
    static ObserverPtr<ADerived> fgInstance;
};

} // namespace MACE::Environment::Memory

#include "MACE/Environment/Memory/FreeSingleton.inl"
