#if MACE_SIGNAL_HANDLER

#    include "MACE/Env/MPIEnv.h++"
#    include "MACE/Env/Print.h++"
#    include "MACE/Env/internal/ISOC99SignalHandler.h++"
#    include "MACE/Utility/InlineMacro.h++"
#    include "MACE/Utility/PrintStackTrace.h++"

#    include "fmt/chrono.h"
#    include "fmt/format.h"

#    include <chrono>
#    include <csignal>
#    include <cstdlib>
#    include <ctime>
#    include <iostream>

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
            PrintLn(std::clog, "");
            switch (sig) {
            case SIGINT:
                PrintLn(std::clog, "{}***** INTERRUPT (SIGINT) received", lineHeader);
                break;
            case SIGTERM:
                PrintLn(std::clog, "{}***** TERMINATE (SIGTERM) received", lineHeader);
                break;
            }
            if (MPIEnv::Available()) {
                const auto& mpi{MPIEnv::Instance()};
                PrintLn(std::clog, "{}***** on MPI process {} (node: {})", lineHeader, mpi.CommWorldRank(), mpi.LocalNode().name);
            }
            PrintLn(std::clog, "{}***** at {:%FT%T%z}", lineHeader, fmt::localtime(now));
            PrintStackTrace(64, 2);
            PrintLn(std::clog, "");
            flush(std::clog);
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
    PrintLn(std::clog, "");
    PrintLn(std::clog, "{}***** ABORT (SIGABRT) received", lineHeader);
    if (MPIEnv::Available()) {
        const auto& mpi{MPIEnv::Instance()};
        PrintLn(std::clog, "{}***** on MPI process {} (node: {})", lineHeader, mpi.CommWorldRank(), mpi.LocalNode().name);
    }
    PrintLn(std::clog, "{}***** at {:%FT%T%z}", lineHeader, fmt::localtime(now));
    PrintStackTrace(64, 2);
    PrintLn(std::clog, "");
    flush(std::clog);
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
            PrintLn(std::clog, "");
            switch (sig) {
            case SIGFPE:
                PrintLn(std::clog, "{}***** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) received", lineHeader);
                break;
            case SIGILL:
                PrintLn(std::clog, "{}***** ILLEGAL INSTRUCTION (SIGILL) received", lineHeader);
                break;
            case SIGSEGV:
                PrintLn(std::clog, "{}***** SEGMENTATION VIOLATION (SIGSEGV) received", lineHeader);
                break;
            }
            if (MPIEnv::Available()) {
                const auto& mpi{MPIEnv::Instance()};
                PrintLn(std::clog, "{}***** on MPI process {} (node: {})", lineHeader, mpi.CommWorldRank(), mpi.LocalNode().name);
            }
            PrintLn(std::clog, "{}***** at {:%FT%T%z}", lineHeader, fmt::localtime(now));
            PrintStackTrace(64, 2);
            PrintLn(std::clog, "");
            flush(std::clog);
            std::raise(sig);
        }
    } handler{sig};
}

} // extern "C"

} // namespace MACE::Env::internal

#endif
