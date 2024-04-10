#include "MACE/Env/Memory/internal/SingletonDeleter.h++"
#include "MACE/Env/Memory/internal/SingletonPool.h++"
#include "MACE/Env/Memory/internal/WeakSingletonPool.h++"
#include "MACE/Env/internal/EnvBase.h++"
#include "MACE/Utility/BitWidthOf.h++"

#include "fmt/format.h"

#include <limits>

#if MACE_SIGNAL_HANDLER

#    include "MACE/Env/MPIEnv.h++"
#    include "MACE/Env/Print.h++"
#    include "MACE/Utility/InlineMacro.h++"
#    include "MACE/Utility/PrintStackTrace.h++"

#    include "fmt/chrono.h"

#    include <chrono>
#    include <csignal>
#    include <cstdlib>
#    include <ctime>
#    include <exception>
#    include <iostream>

#endif

namespace MACE::Env::internal {

#if MACE_SIGNAL_HANDLER

namespace {

extern "C" {

auto MACE_SIGINT_SIGTERM_Handler(int sig) -> void {
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

[[noreturn]] auto MACE_SIGABRT_Handler(int) -> void {
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

auto MACE_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) -> void {
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

std::terminate_handler DefaultTerminateHandler{};

auto TerminateHandler() -> void {
    std::signal(SIGABRT, SIG_DFL);
    if (DefaultTerminateHandler) {
        DefaultTerminateHandler();
    } else {
        Env::PrintLnError("std::terminate called");
        std::abort();
    }
}

} // namespace

#endif

EnvBase::EnvBase() :
    NonMoveableBase{},
    fWeakSingletonPool{},
    fSingletonPool{},
    fSingletonDeleter{} {

    static_assert("三清庇佑 运行稳定 结果无偏");
    static_assert("God bless no bugs");

    CheckFundamentalType();

#if MACE_SIGNAL_HANDLER
    std::signal(SIGABRT, MACE_SIGABRT_Handler);
    std::signal(SIGFPE, MACE_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGILL, MACE_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGINT, MACE_SIGINT_SIGTERM_Handler);
    std::signal(SIGSEGV, MACE_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGTERM, MACE_SIGINT_SIGTERM_Handler);
    DefaultTerminateHandler = std::set_terminate(TerminateHandler);
#endif

    if (static bool gInstantiated = false;
        gInstantiated) {
        throw std::logic_error("MACE::Env::internal::EnvBase: Trying to construct environment twice");
    } else {
        gInstantiated = true;
    }

    fWeakSingletonPool = std::make_unique_for_overwrite<Memory::internal::WeakSingletonPool>();
    fSingletonPool = std::make_unique_for_overwrite<Memory::internal::SingletonPool>();
    fSingletonDeleter = std::make_unique_for_overwrite<Memory::internal::SingletonDeleter>();
}

EnvBase::~EnvBase() = default;

auto EnvBase::CheckFundamentalType() -> void {
    constexpr auto lp32{BitWidthOf<char>() == 8 and
                        BitWidthOf<short>() == 16 and
                        BitWidthOf<int>() == 16 and
                        BitWidthOf<long>() == 32 and
                        BitWidthOf<long long>() == 64 and
                        BitWidthOf<void*>() == 32};
    constexpr auto ilp32{BitWidthOf<char>() == 8 and
                         BitWidthOf<short>() == 16 and
                         BitWidthOf<int>() == 32 and
                         BitWidthOf<long>() == 32 and
                         BitWidthOf<long long>() == 64 and
                         BitWidthOf<void*>() == 32};
    constexpr auto llp64{BitWidthOf<char>() == 8 and
                         BitWidthOf<short>() == 16 and
                         BitWidthOf<int>() == 32 and
                         BitWidthOf<long>() == 32 and
                         BitWidthOf<long long>() == 64 and
                         BitWidthOf<void*>() == 64};
    constexpr auto lp64{BitWidthOf<char>() == 8 and
                        BitWidthOf<short>() == 16 and
                        BitWidthOf<int>() == 32 and
                        BitWidthOf<long>() == 64 and
                        BitWidthOf<long long>() == 64 and
                        BitWidthOf<void*>() == 64};
    if constexpr (not lp64) {
        if constexpr (llp64) {
            fmt::println(stderr, "Warning: The fundamental data model is LLP64 (not LP64)");
        } else if constexpr (ilp32) {
            fmt::println(stderr, "Warning: The fundamental data model is ILP32 (not LP64)");
        } else if constexpr (lp32) {
            fmt::println(stderr, "Warning: The fundamental data model is LP32 (not LP64)");
        } else {
            fmt::println(stderr, "Warning: Using a rare fundamental data model "
                                 "[{}-bits char, {}-bits short, {}-bits int, {}-bits long, {}-bits long long, {}-bits pointer], "
                                 "run at your own risk",
                         BitWidthOf<char>(), BitWidthOf<short>(), BitWidthOf<int>(), BitWidthOf<long>(), BitWidthOf<long long>(), BitWidthOf<void*>());
        }
    }
    if (not std::numeric_limits<float>::is_iec559) {
        fmt::println(stderr, "Warning: 'float' does not fulfill the requirements of IEC 559 (IEEE 754)");
    }
    if (not std::numeric_limits<double>::is_iec559) {
        fmt::println(stderr, "Warning: 'double' does not fulfill the requirements of IEC 559 (IEEE 754)");
    }
    if (not std::numeric_limits<long double>::is_iec559) {
        fmt::println(stderr, "Warning: 'long double' does not fulfill the requirements of IEC 559 (IEEE 754)");
    }
}

} // namespace MACE::Env::internal
