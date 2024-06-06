#pragma once

#include "MACE/Env/Memory/PassiveSingletonified.h++"
#include "MACE/Env/Memory/WeakSingleton.h++"
#include "MACE/Env/Memory/internal/PassiveSingletonBase.h++"
#include "MACE/Env/Memory/internal/WeakSingletonPool.h++"

#include "muc/utility"

#include "fmt/format.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Env::Memory {

template<typename ADerived>
class PassiveSingleton : public internal::PassiveSingletonBase,
                         public WeakSingleton<ADerived> {
protected:
    PassiveSingleton();
    ~PassiveSingleton() = default;

public:
    MACE_ALWAYS_INLINE static auto Instance() -> ADerived&;

private:
    using Base = WeakSingleton<ADerived>;
};

} // namespace MACE::Env::Memory

#include "MACE/Env/Memory/PassiveSingleton.inl"
