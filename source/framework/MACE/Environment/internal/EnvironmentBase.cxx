#include "MACE/Environment/internal/EnvironmentBase.hxx"
#include "MACE/Environment/Memory/internal/MuteSingletonPool.hxx"
#include "MACE/Environment/Memory/internal/SingletonDeleter.hxx"
#include "MACE/Environment/Memory/internal/SingletonFactory.hxx"
#include "MACE/Environment/Memory/internal/SingletonPool.hxx"

#if MACE_SIGNAL_HANDLER

    #include "MACE/Environment/internal/ISOC99SignalHandler.hxx"

    #include <csignal>

#endif

namespace MACE::Environment::Internal {

EnvironmentBase::EnvironmentBase() :
    NonMoveableBase(),
    fMuteSingletonPool(nullptr),
    fSingletonPool(nullptr),
    fSingletonFactory(nullptr),
    fSingletonDeleter(nullptr) {

#if MACE_SIGNAL_HANDLER
    std::signal(SIGABRT, MACE_ISOC99SignalHandler);
    std::signal(SIGFPE, MACE_ISOC99SignalHandler);
    std::signal(SIGILL, MACE_ISOC99SignalHandler);
    std::signal(SIGINT, MACE_ISOC99SignalHandler);
    std::signal(SIGSEGV, MACE_ISOC99SignalHandler);
    std::signal(SIGTERM, MACE_ISOC99SignalHandler);
#endif

    if (static bool gInstantiated = false;
        gInstantiated) {
        throw std::logic_error("MACE::Environment::Internal::EnvironmentBase: Trying to construct environment twice");
    } else {
        gInstantiated = true;
    }

    fMuteSingletonPool = std::make_unique<Memory::Internal::MuteSingletonPool>();
    fSingletonPool = std::make_unique<Memory::Internal::SingletonPool>();
    fSingletonFactory = std::make_unique<Memory::Internal::SingletonFactory>();
    fSingletonDeleter = std::make_unique<Memory::Internal::SingletonDeleter>();
}

EnvironmentBase::~EnvironmentBase() = default;

} // namespace MACE::Environment::Internal
