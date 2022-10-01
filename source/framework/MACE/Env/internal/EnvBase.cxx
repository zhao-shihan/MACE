#include "MACE/Env/internal/EnvBase.hxx"
#include "MACE/Env/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Env/Memory/internal/SingletonDeleter.hxx"
#include "MACE/Env/Memory/internal/SingletonFactory.hxx"
#include "MACE/Env/Memory/internal/SingletonPool.hxx"

#if MACE_SIGNAL_HANDLER

#    include "MACE/Env/internal/ISOC99SignalHandler.hxx"

#    include <csignal>

#endif

namespace MACE::Env::internal {

EnvBase::EnvBase() :
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

    if (static bool gInstantiated = false;
        gInstantiated) {
        throw std::logic_error("MACE::Env::internal::EnvBase: Trying to construct environment twice");
    } else {
        gInstantiated = true;
    }

    fMuteSingletonPool = std::make_unique<Memory::internal::MuteSingletonPool>();
    fSingletonPool = std::make_unique<Memory::internal::SingletonPool>();
    fSingletonFactory = std::make_unique<Memory::internal::SingletonFactory>();
    fSingletonDeleter = std::make_unique<Memory::internal::SingletonDeleter>();
}

EnvBase::~EnvBase() = default;

} // namespace MACE::Env::internal
