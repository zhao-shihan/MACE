#pragma once

#include <ctime>
#include <sys/time.h>

namespace MACE::inline Utility::internal {

template<typename ATime>
class CPUTimeStopwatch {
public:
    CPUTimeStopwatch() noexcept;

    auto SecondsUsed() const noexcept -> auto { return NanosecondsUsed() / 1'000'000'000; }
    auto MillisecondsUsed() const noexcept -> auto { return NanosecondsUsed() / 1'000'000; }
    auto MicrosecondsUsed() const noexcept -> auto { return NanosecondsUsed() / 1'000; }
    auto NanosecondsUsed() const noexcept -> ATime;

private:
    std::timespec fT0;
};

} // namespace MACE::inline Utility::internal

#include "MACE/Utility/internal/CPUTimeStopwatch/LinuxBSDCPUTimeStopwatch.inl"
