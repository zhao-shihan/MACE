#if MACE_SIGNAL_HANDLER

#    include "MACE/Env/MPIEnv.h++"
#    include "MACE/Env/internal/ISOC99SignalHandler.h++"
#    include "MACE/Utility/PrintStackTrace.h++"

#    include <chrono>
#    include <csignal>
#    include <cstdlib>
#    include <ctime>
#    include <iomanip>
#    include <iostream>
#    include <string_view>

namespace MACE::Env::internal {

extern "C" {

void MACE_ISOC99_SIGINT_SIGTERM_Handler(int sig) {
    static auto called{false};
    static struct Handler {
        Handler(int sig) {
            if (called) {
                std::abort();
            } else {
                called = true;
            }
            std::signal(sig, SIG_DFL);
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
                std::clog << "***** on MPI process " << mpi.CommWorldRank() << " (node: " << mpi.LocalNode().name << ")\n";
            }
            std::clog << "***** at " << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
            PrintStackTrace(64, 2);
            std::clog << std::endl;
            std::raise(sig);
        }
    } handler{sig};
}

[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int) {
    std::signal(SIGABRT, SIG_DFL);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cerr << std::endl;
    std::clog << "***** ABORT (SIGABRT) received\n";
    if (MPIEnv::Available()) {
        const auto& mpi = MPIEnv::Instance();
        std::clog << "***** on MPI process " << mpi.CommWorldRank() << " (node: " << mpi.LocalNode().name << ")\n";
    }
    std::clog << "***** at " << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
    PrintStackTrace(64, 2);
    std::clog << std::endl;
    std::abort();
}

void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) {
    static auto called{false};
    static struct Handler {
        Handler(int sig) {
            if (called) {
                std::abort();
            } else {
                called = true;
            }
            std::signal(sig, SIG_DFL);
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
                std::clog << "***** on MPI process " << mpi.CommWorldRank() << " (node: " << mpi.LocalNode().name << ")\n";
            }
            std::clog << "***** at " << std::put_time(std::localtime(&now), "%FT%T%z") << std::endl;
            PrintStackTrace(64, 2);
            std::clog << std::endl;
            std::raise(sig);
        }
    } handler{sig};
}

} // extern "C"

} // namespace MACE::Env::internal

#endif
