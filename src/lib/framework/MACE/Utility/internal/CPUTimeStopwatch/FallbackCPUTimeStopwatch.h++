#pragma once

#include <ctime>

namespace MACE::inline Utility::internal {

template<typename ATime>
class CPUTimeStopwatch {
public:
    CPUTimeStopwatch() noexcept;

    auto SecondsUsed() const noexcept -> auto { static_cast<ATime>(std::clock() - fT0) / CLOCKS_PER_SEC; }
    auto MillisecondsUsed() const noexcept -> auto { return SecondsUsed() * 1'000; }
    auto MicrosecondsUsed() const noexcept -> auto { return SecondsUsed() * 1'000'000; }
    auto NanosecondsUsed() const noexcept -> auto { return SecondsUsed() * 1'000'000'000; }

private:
    std::clock_t fT0;
};

} // namespace MACE::inline Utility::internal

#include "MACE/Utility/internal/CPUTimeStopwatch/FallbackCPUTimeStopwatch.inl"
