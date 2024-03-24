#if MACE_SIGNAL_HANDLER

#    include "MACE/Env/MPIEnv.h++"
#    include "MACE/Env/internal/ISOC99SignalHandler.h++"
#    include "MACE/Utility/InlineMacro.h++"
#    include "MACE/Utility/PrintStackTrace.h++"

#    include "fmt/chrono.h"
#    include "fmt/format.h"

#    include <chrono>
#    include <csignal>
#    include <cstdio>
#    include <cstdlib>
#    include <ctime>

namespace MACE::Env::internal {

extern "C" {

void MACE_ISOC99_SIGINT_SIGTERM_Handler(int sig) {
    std::signal(sig, SIG_DFL);
    if (static auto called{false};
        called) {
        std::abort();
    } else {
        called = true;
    }
    static struct Handler {
        MACE_ALWAYS_INLINE Handler(int sig) {
            const auto now{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
            const auto lineHeader{MPIEnv::Available() ?
                                      fmt::format("MPI{}> ", MPIEnv::Instance().CommWorldRank()) :
                                      ""};
            fmt::println(stderr, "");
            switch (sig) {
            case SIGINT:
                fmt::println(stderr, "{}***** INTERRUPT (SIGINT) received", lineHeader);
                break;
            case SIGTERM:
                fmt::println(stderr, "{}***** TERMINATE (SIGTERM) received", lineHeader);
                break;
            }
            if (MPIEnv::Available()) {
                const auto& mpi{MPIEnv::Instance()};
                fmt::println(stderr, "{}***** on MPI process {} (node: {})", lineHeader, mpi.CommWorldRank(), mpi.LocalNode().name);
            }
            fmt::println(stderr, "{}***** at {:%FT%T%z}", lineHeader, fmt::localtime(now));
            PrintStackTrace(64, 2);
            fmt::println(stderr, "");
            std::fflush(stderr);
            std::raise(sig);
        }
    } handler{sig};
}

[[noreturn]] void MACE_ISOC99_SIGABRT_Handler(int) {
    std::signal(SIGABRT, SIG_DFL);
    const auto now{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
    const auto lineHeader{MPIEnv::Available() ?
                              fmt::format("MPI{}> ", MPIEnv::Instance().CommWorldRank()) :
                              ""};
    fmt::println(stderr, "");
    fmt::println(stderr, "{}***** ABORT (SIGABRT) received", lineHeader);
    if (MPIEnv::Available()) {
        const auto& mpi{MPIEnv::Instance()};
        fmt::println(stderr, "{}***** on MPI process {} (node: {})", lineHeader, mpi.CommWorldRank(), mpi.LocalNode().name);
    }
    fmt::println(stderr, "{}***** at {:%FT%T%z}", lineHeader, fmt::localtime(now));
    PrintStackTrace(64, 2);
    fmt::println(stderr, "");
    std::fflush(stderr);
    std::abort();
}

void MACE_ISOC99_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) {
    std::signal(sig, SIG_DFL);
    if (static auto called{false};
        called) {
        std::abort();
    } else {
        called = true;
    }
    static struct Handler {
        MACE_ALWAYS_INLINE Handler(int sig) {
            const auto now{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
            const auto lineHeader{MPIEnv::Available() ?
                                      fmt::format("MPI{}> ", MPIEnv::Instance().CommWorldRank()) :
                                      ""};
            fmt::println(stderr, "");
            switch (sig) {
            case SIGFPE:
                fmt::println(stderr, "{}***** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) received", lineHeader);
                break;
            case SIGILL:
                fmt::println(stderr, "{}***** ILLEGAL INSTRUCTION (SIGILL) received", lineHeader);
                break;
            case SIGSEGV:
                fmt::println(stderr, "{}***** SEGMENTATION VIOLATION (SIGSEGV) received", lineHeader);
                break;
            }
            if (MPIEnv::Available()) {
                const auto& mpi{MPIEnv::Instance()};
                fmt::println(stderr, "{}***** on MPI process {} (node: {})", lineHeader, mpi.CommWorldRank(), mpi.LocalNode().name);
            }
            fmt::println(stderr, "{}***** at {:%FT%T%z}", lineHeader, fmt::localtime(now));
            PrintStackTrace(64, 2);
            fmt::println(stderr, "");
            std::fflush(stderr);
            std::raise(sig);
        }
    } handler{sig};
}

} // extern "C"

} // namespace MACE::Env::internal

#endif
