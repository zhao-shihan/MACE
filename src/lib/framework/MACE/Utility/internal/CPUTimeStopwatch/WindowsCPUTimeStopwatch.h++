#pragma once

#if defined _MSC_VER and not defined __clang__ and not defined __GNUC__ and not defined NOMINMAX
#    define NOMINMAX // Otherwise MS compilers act like idiots when using std::numeric_limits<>::max() and including windows.h
#endif
#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
#    undef WIN32_LEAN_AND_MEAN
#else
#    include <windows.h>
#endif

#include <cstring>

namespace MACE::inline Utility::internal {

template<typename ATime>
class CPUTimeStopwatch {
public:
    CPUTimeStopwatch() noexcept;

    auto SecondsUsed() const noexcept -> auto { return HectonanosecondsUsed() / 10'000'000; }
    auto MillisecondsUsed() const noexcept -> auto { return HectonanosecondsUsed() / 10'000; }
    auto MicrosecondsUsed() const noexcept -> auto { return HectonanosecondsUsed() / 10; }
    auto NanosecondsUsed() const noexcept -> auto { return HectonanosecondsUsed() * 100; }

private:
    auto HectonanosecondsUsed() const noexcept -> auto { return static_cast<ATime>(ClockIn100ns().QuadPart - fT0.QuadPart); }
    auto ClockIn100ns() const noexcept -> ULARGE_INTEGER;

private:
    HANDLE fCurrentProcess;
    ULARGE_INTEGER fT0;
};

} // namespace MACE::inline Utility::internal

#include "MACE/Utility/internal/CPUTimeStopwatch/WindowsCPUTimeStopwatch.inl"
