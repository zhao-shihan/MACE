#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
#    undef WIN32_LEAN_AND_MEAN
#else
#    include <windows.h>
#endif

#include <cstring>

namespace MACE::Utility::internal {

template<typename ATime>
class CPUTimer {
public:
    CPUTimer() noexcept;

    void Reset() noexcept { fT0 = ClockIn100ns(); }
    auto SecondsUsed() const noexcept { HectonanosecondsUsed() / 10'000'000; }
    auto MillisecondsUsed() const noexcept { return HectonanosecondsUsed() / 10'000; }
    auto MicrosecondsUsed() const noexcept { return HectonanosecondsUsed() / 10; }
    auto NanosecondsUsed() const noexcept { return HectonanosecondsUsed() * 100; }

private:
    auto HectonanosecondsUsed() const noexcept { return static_cast<ATime>(ClockIn100ns().QuadPart - fT0.QuadPart); }
    ULARGE_INTEGER ClockIn100ns() const noexcept;

private:
    const HANDLE fCurrentProcess;
    ULARGE_INTEGER fT0;
};

} // namespace MACE::Utility::internal

#include "MACE/Utility/internal/CPUTimer/CPUTimer4Windows.inl"
