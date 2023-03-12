#pragma once

#include <ctime>

namespace MACE::inline Utility::internal {

template<typename ATime>
class CPUTimer {
public:
    CPUTimer() noexcept;

    void Reset() noexcept { fT0 = std::clock(); }
    auto SecondsUsed() const noexcept { static_cast<ATime>(std::clock() - fT0) / CLOCKS_PER_SEC; }
    auto MillisecondsUsed() const noexcept { return SecondsUsed() * 1'000; }
    auto MicrosecondsUsed() const noexcept { return SecondsUsed() * 1'000'000; }
    auto NanosecondsUsed() const noexcept { return SecondsUsed() * 1'000'000'000; }

private:
    std::clock_t fT0;
};

} // namespace MACE::inline Utility::internal

#include "MACE/Utility/internal/CPUTimer/CPUTimer4Fallback.inl"
