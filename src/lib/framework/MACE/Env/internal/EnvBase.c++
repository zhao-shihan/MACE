#include "MACE/Env/Memory/internal/SingletonDeleter.h++"
#include "MACE/Env/Memory/internal/SingletonPool.h++"
#include "MACE/Env/Memory/internal/WeakSingletonPool.h++"
#include "MACE/Env/internal/EnvBase.h++"
#include "MACE/Utility/BitWidthOf.h++"

#include "fmt/format.h"

#include <limits>

#if MACE_SIGNAL_HANDLER

#    include "MACE/Env/internal/ISOC99SignalHandler.h++"

#    include <csignal>

#endif

namespace MACE::Env::internal {

EnvBase::EnvBase() :
    NonMoveableBase{},
    fWeakSingletonPool{},
    fSingletonPool{},
    fSingletonDeleter{} {

    static_assert("God bless no bugs");

    CheckFundamentalType();

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

    fWeakSingletonPool = std::make_unique_for_overwrite<Memory::internal::WeakSingletonPool>();
    fSingletonPool = std::make_unique_for_overwrite<Memory::internal::SingletonPool>();
    fSingletonDeleter = std::make_unique_for_overwrite<Memory::internal::SingletonDeleter>();
}

EnvBase::~EnvBase() = default;

auto EnvBase::CheckFundamentalType() -> void {
    constexpr auto lp32{BitWidthOf<char> == 8 and
                        BitWidthOf<short> == 16 and
                        BitWidthOf<int> == 16 and
                        BitWidthOf<long> == 32 and
                        BitWidthOf<long long> == 64 and
                        BitWidthOf<void*> == 32};
    constexpr auto ilp32{BitWidthOf<char> == 8 and
                         BitWidthOf<short> == 16 and
                         BitWidthOf<int> == 32 and
                         BitWidthOf<long> == 32 and
                         BitWidthOf<long long> == 64 and
                         BitWidthOf<void*> == 32};
    constexpr auto llp64{BitWidthOf<char> == 8 and
                         BitWidthOf<short> == 16 and
                         BitWidthOf<int> == 32 and
                         BitWidthOf<long> == 32 and
                         BitWidthOf<long long> == 64 and
                         BitWidthOf<void*> == 64};
    constexpr auto lp64{BitWidthOf<char> == 8 and
                        BitWidthOf<short> == 16 and
                        BitWidthOf<int> == 32 and
                        BitWidthOf<long> == 64 and
                        BitWidthOf<long long> == 64 and
                        BitWidthOf<void*> == 64};
    if constexpr (not lp64) {
        if constexpr (llp64) {
            fmt::println(stderr, "Warning: fundamental data model is LLP64 (not LP64)");
        } else if constexpr (ilp32) {
            fmt::println(stderr, "Warning: fundamental data model is ILP32 (not LP64)");
        } else if constexpr (lp32) {
            fmt::println(stderr, "Warning: fundamental data model is LP32 (not LP64)");
        } else {
            fmt::println(stderr, "Warning: using a rare fundamental data model "
                               "[{}-bits char, {}-bits short, {}-bits int, {}-bits long, {}-bits long long, {}-bits pointer], "
                               "run at your own risk",
                       BitWidthOf<char>, BitWidthOf<short>, BitWidthOf<int>, BitWidthOf<long>, BitWidthOf<long long>, BitWidthOf<void*>);
        }
    }
    if (not std::numeric_limits<float>::is_iec559) {
        fmt::println(stderr, "Warning: <float> does not fulfill the requirements of IEC 559 (IEEE 754)");
    }
    if (not std::numeric_limits<double>::is_iec559) {
        fmt::println(stderr, "Warning: <double> does not fulfill the requirements of IEC 559 (IEEE 754)");
    }
    if (not std::numeric_limits<long double>::is_iec559) {
        fmt::println(stderr, "Warning: <long double> does not fulfill the requirements of IEC 559 (IEEE 754)");
    }
}

} // namespace MACE::Env::internal
