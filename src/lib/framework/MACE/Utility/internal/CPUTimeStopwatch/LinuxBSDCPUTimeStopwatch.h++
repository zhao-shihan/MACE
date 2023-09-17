#pragma once

#include <ctime>
#include <sys/time.h>

namespace MACE::inline Utility::internal {

template<typename ATime>
class CPUTimeStopwatch {
public:
    CPUTimeStopwatch() noexcept;

    void Reset() noexcept { clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fT0); }
    auto SecondsUsed() const noexcept { return NanosecondsUsed() / 1'000'000'000; }
    auto MillisecondsUsed() const noexcept { return NanosecondsUsed() / 1'000'000; }
    auto MicrosecondsUsed() const noexcept { return NanosecondsUsed() / 1'000; }
    ATime NanosecondsUsed() const noexcept;

private:
    std::timespec fT0;
};

} // namespace MACE::inline Utility::internal

#include "MACE/Utility/internal/CPUTimeStopwatch/LinuxBSDCPUTimeStopwatch.inl"
