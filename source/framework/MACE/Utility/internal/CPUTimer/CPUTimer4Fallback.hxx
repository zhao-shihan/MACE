#pragma once

#include <ctime>

namespace MACE::Utility::internal {

template<typename ATime>
class CPUTimer {
public:
    CPUTimer() noexcept;

    void Reset() noexcept { fT0 = std::clock(); }
    auto SecondsUsed() noexcept { static_cast<ATime>(std::clock() - fT0) / CLOCKS_PER_SEC; }
    auto MillisecondsUsed() noexcept { return SecondsUsed() * 1'000; }
    auto MicrosecondsUsed() noexcept { return SecondsUsed() * 1'000'000; }
    auto NanosecondsUsed() noexcept { return SecondsUsed() * 1'000'000'000; }

private:
    std::clock_t fT0;
};

} // namespace MACE::Utility::internal

#include "MACE/Utility/internal/CPUTimer/CPUTimer4Fallback.inl"
