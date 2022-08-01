#include "MACE/Environment/detail/EnvironmentBase.hxx"
#include "MACE/Environment/detail/SignalHandler.hxx"
#include "MACE/Environment/Memory/detail/MuteSingletonPool.hxx"
#include "MACE/Environment/Memory/detail/SingletonDeleter.hxx"
#include "MACE/Environment/Memory/detail/SingletonFactory.hxx"

#if MACE_SIGNAL_HANDLER
    #include <csignal>
#endif

namespace MACE::Environment::Detail {

EnvironmentBase::EnvironmentBase() :
    NonMoveableBase(),
    fMuteSingletonPool(nullptr),
    fSingletonPool(nullptr),
    fSingletonFactory(nullptr),
    fSingletonDeleter(nullptr) {

#if MACE_SIGNAL_HANDLER
    std::signal(SIGABRT, MACE_ISOC99_SIGABRT_Handler);
    std::signal(SIGFPE, MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGILL, MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGINT, MACE_ISOC99_SIGINT_SIGTERM_Handler);
    std::signal(SIGSEGV, MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGTERM, MACE_ISOC99_SIGINT_SIGTERM_Handler);
#endif

    if (static bool gInstantiated = false; gInstantiated) {
        throw std::logic_error("MACE::Environment::Detail::EnvironmentBase: Trying to construct environment twice");
    } else {
        gInstantiated = true;
    }

    fMuteSingletonPool = std::make_unique<Memory::Detail::MuteSingletonPool>();
    fSingletonPool = std::make_unique<Memory::Detail::SingletonPool>();
    fSingletonFactory = std::make_unique<Memory::Detail::SingletonFactory>();
    fSingletonDeleter = std::make_unique<Memory::Detail::SingletonDeleter>();
}

EnvironmentBase::~EnvironmentBase() = default;

} // namespace MACE::Environment::Detail
