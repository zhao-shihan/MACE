#pragma once

#include "MACE/Env/Memory/WeakSingletonified.h++"
#include "MACE/Env/Memory/internal/WeakSingletonBase.h++"
#include "MACE/Env/Memory/internal/WeakSingletonPool.h++"
#include "MACE/Utility/InlineMacro.h++"

#include "fmt/format.h"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace MACE::Env::Memory {

template<typename ADerived>
class PassiveSingleton;

template<typename ADerived>
class WeakSingleton : public internal::WeakSingletonBase {
    friend class PassiveSingleton<ADerived>;

protected:
    WeakSingleton();
    ~WeakSingleton();

public:
    MACE_ALWAYS_INLINE static auto NotInstantiated() -> bool { return UpdateInstance() == Status::NotInstantiated; }
    MACE_ALWAYS_INLINE static auto Available() -> bool { return UpdateInstance() == Status::Available; }
    MACE_ALWAYS_INLINE static auto Expired() -> bool { return UpdateInstance() == Status::Expired; }
    MACE_ALWAYS_INLINE static auto Instantiated() -> bool;

private:
    enum class Status {
        NotInstantiated,
        Available,
        Expired
    };

    static auto UpdateInstance() -> Status;

private:
    static void** fgInstance;
};

} // namespace MACE::Env::Memory

#include "MACE/Env/Memory/WeakSingleton.inl"
