#if MACE_SIGNAL_HANDLER

#    include "MACE/Environment/internal/ISOC99SignalHandler.hxx"
#    include "MACE/Environment/MPIEnvironment.hxx"
#    include "MACE/Utility/PrintStackTrace.hxx"

#    include "backward.hpp"

#    include <chrono>
#    include <csignal>
#    include <cstdlib>
#    include <ctime>
#    include <iomanip>
#    include <iostream>
#    include <string_view>

namespace MACE::Environment::internal {

extern "C" {

[[noreturn]] void MACE_ISOC99_SIGINT_SIGTERM_Handler(int sig) {
    using namespace std::string_view_literals;
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << std::endl;
    switch (sig) {
    case SIGINT:
        std::clog << "***** INTERRUPT (SIGINT) received\n"sv;
        break;
    case SIGTERM:
        std::clog << "***** TERMINATE (SIGTERM) received\n"sv;
        break;
    }
    if (MPIEnvironment::Available()) {
        const auto& mpi = MPIEnvironment::Instance();
        std::clog << "***** on rank "sv << mpi.WorldCommRank() << " (host: "sv << mpi.LocalHostName() << ")\n"sv;
    }
    std::clog << "***** at "sv << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
    backward::StackTrace stack;
    stack.load_here(64);
    Utility::PrintStackTrace(stack);
    std::clog << std::endl;
#    ifndef __MINGW32__
    std::quick_exit(EXIT_FAILURE);
#    else
    std::_Exit(EXIT_FAILURE);
#    endif
}

[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int) {
    using namespace std::string_view_literals;
    std::signal(SIGABRT, SIG_DFL);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << std::endl;
    std::clog << "***** ABORT (SIGABRT) received\n"sv;
    if (MPIEnvironment::Available()) {
        const auto& mpi = MPIEnvironment::Instance();
        std::clog << "***** on rank "sv << mpi.WorldCommRank() << " (host: "sv << mpi.LocalHostName() << ")\n"sv;
    }
    std::clog << "***** at "sv << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
    backward::StackTrace stack;
    stack.load_here(64);
    Utility::PrintStackTrace(stack);
    std::clog << std::endl;
    std::abort();
}

[[noreturn]] void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) {
    using namespace std::string_view_literals;
    std::signal(SIGABRT, SIG_DFL);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << std::endl;
    switch (sig) {
    case SIGFPE:
        std::clog << "***** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) received\n"sv;
        break;
    case SIGILL:
        std::clog << "***** ILLEGAL INSTRUCTION (SIGILL) received\n"sv;
        break;
    case SIGSEGV:
        std::clog << "***** SEGMENTATION VIOLATION (SIGSEGV) received\n"sv;
        break;
    }
    if (MPIEnvironment::Available()) {
        const auto& mpi = MPIEnvironment::Instance();
        std::clog << "***** on rank "sv << mpi.WorldCommRank() << " (host: "sv << mpi.LocalHostName() << ")\n"sv;
    }
    std::clog << "***** at "sv << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
    backward::StackTrace stack;
    stack.load_here(64);
    Utility::PrintStackTrace(stack);
    std::clog << std::endl;
    std::abort();
}

} // extern "C"

} // namespace MACE::Environment::internal

#endif
