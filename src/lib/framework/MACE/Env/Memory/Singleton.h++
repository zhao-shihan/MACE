#pragma once

#include "MACE/Env/Memory/Singletonified.h++"
#include "MACE/Env/Memory/internal/SingletonBase.h++"
#include "MACE/Env/Memory/internal/SingletonPool.h++"
#include "MACE/Utility/InlineMacro.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

#include "fmt/format.h"

#include <stdexcept>
#include <typeinfo>

namespace MACE::Env::Memory {

template<typename ADerived>
class Singleton : public internal::SingletonBase {
protected:
    Singleton();
    virtual ~Singleton() override;

public:
    MACE_ALWAYS_INLINE static auto Instance() -> ADerived&;
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

    MACE_ALWAYS_INLINE static auto UpdateInstance() -> Status;

private:
    static void** fgInstance;
};

class SingletonInstantiator final : NonConstructibleBase {
    template<typename ASingleton>
    friend auto Singleton<ASingleton>::Instance() -> ASingleton&;

    template<Singletonified ASingleton>
    static auto New() { return new ASingleton; }
};

} // namespace MACE::Env::Memory

#include "MACE/Env/Memory/Singleton.inl"
