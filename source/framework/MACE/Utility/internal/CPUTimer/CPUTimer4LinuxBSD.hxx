#pragma once

#include <sys/time.h>
#include <time.h>

namespace MACE::Utility::internal {

template<typename ATime>
class CPUTimer {
public:
    CPUTimer() noexcept;

    void Reset() noexcept { clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fT0); }
    auto SecondsUsed() const noexcept { return NanosecondsUsed() / 1'000'000'000; }
    auto MillisecondsUsed() const noexcept { return NanosecondsUsed() / 1'000'000; }
    auto MicrosecondsUsed() const noexcept { return NanosecondsUsed() / 1'000; }
    ATime NanosecondsUsed() const noexcept;

private:
    struct timespec fT0;
};

} // namespace MACE::Utility::internal

#include "MACE/Utility/internal/CPUTimer/CPUTimer4LinuxBSD.inl"
