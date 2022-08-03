#pragma once

#include "MACE/Environment/Memory/Concept/FreeSingletonized.hxx"
#include "MACE/Environment/Memory/detail/FreeSingletonBase.hxx"
#include "MACE/Environment/Memory/detail/MuteSingletonPool.hxx"
#include "MACE/Environment/Memory/MuteSingleton.hxx"

#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Environment::Memory {

template<class ADerived>
class FreeSingleton : public Detail::FreeSingletonBase,
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
