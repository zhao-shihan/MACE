#if MACE_SIGNAL_HANDLER

#    include "MACE/Env/internal/ISOC99SignalHandler.h++"
#    include "MACE/Env/MPIEnv.h++"
#    include "MACE/Utility/PrintStackTrace.h++"

#    include "backward.hpp"

#    include <chrono>
#    include <csignal>
#    include <cstdlib>
#    include <ctime>
#    include <iomanip>
#    include <iostream>
#    include <string_view>

namespace MACE::Env::internal {

extern "C" {

[[noreturn]] void MACE_ISOC99_SIGINT_SIGTERM_Handler(int sig) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << std::endl;
    switch (sig) {
    case SIGINT:
        std::clog << "***** INTERRUPT (SIGINT) received\n";
        break;
    case SIGTERM:
        std::clog << "***** TERMINATE (SIGTERM) received\n";
        break;
    }
    if (MPIEnv::Available()) {
        const auto& mpi = MPIEnv::Instance();
        std::clog << "***** on rank " << mpi.CommWorldRank() << " (node: " << mpi.LocalNode().name << ")\n";
    }
    std::clog << "***** at " << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
    backward::StackTrace stack;
    stack.load_here(64);
    PrintStackTrace(stack);
    std::clog << std::endl;
#    ifndef __MINGW32__
    std::quick_exit(EXIT_FAILURE);
#    else
    std::_Exit(EXIT_FAILURE);
#    endif
}

[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int) {
    std::signal(SIGABRT, SIG_DFL);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << std::endl;
    std::clog << "***** ABORT (SIGABRT) received\n";
    if (MPIEnv::Available()) {
        const auto& mpi = MPIEnv::Instance();
        std::clog << "***** on rank " << mpi.CommWorldRank() << " (node: " << mpi.LocalNode().name << ")\n";
    }
    std::clog << "***** at " << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
    backward::StackTrace stack;
    stack.load_here(64);
    PrintStackTrace(stack);
    std::clog << std::endl;
    std::abort();
}

[[noreturn]] void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) {
    std::signal(SIGABRT, SIG_DFL);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << std::endl;
    switch (sig) {
    case SIGFPE:
        std::clog << "***** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) received\n";
        break;
    case SIGILL:
        std::clog << "***** ILLEGAL INSTRUCTION (SIGILL) received\n";
        break;
    case SIGSEGV:
        std::clog << "***** SEGMENTATION VIOLATION (SIGSEGV) received\n";
        break;
    }
    if (MPIEnv::Available()) {
        const auto& mpi = MPIEnv::Instance();
        std::clog << "***** on rank " << mpi.CommWorldRank() << " (node: " << mpi.LocalNode().name << ")\n";
    }
    std::clog << "***** at " << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
    backward::StackTrace stack;
    stack.load_here(64);
    PrintStackTrace(stack);
    std::clog << std::endl;
    std::abort();
}

} // extern "C"

} // namespace MACE::Env::internal

#endif
