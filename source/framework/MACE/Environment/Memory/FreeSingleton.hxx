#pragma once

#include "MACE/Environment/Memory/Concept/FreeSingletonized.hxx"
#include "MACE/Environment/Memory/internal/FreeSingletonBase.hxx"
#include "MACE/Environment/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Environment/Memory/MuteSingleton.hxx"

#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Environment::Memory {

template<class ADerived>
class FreeSingleton : public Internal::FreeSingletonBase,
                      public MuteSingleton<ADerived> {
protected:
    FreeSingleton();
    ~FreeSingleton() = default;

public:
    static ADerived& Instance();

private:
    static void FindInstance();
};

} // namespace MACE::Environment::Memory

#include "MACE/Environment/Memory/FreeSingleton.inl"
