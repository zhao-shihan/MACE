#pragma once

// Linux/BSD implementation:
#if (defined linux or defined __linux__ or defined __linux) or \
    (defined __DragonFly__ or defined __FreeBSD__ or defined __NetBSD__ or defined __OpenBSD__)
#    include "MACE/Utility/internal/CPUTimeStopwatch/LinuxBSDCPUTimeStopwatch.h++"
// Windows implementation:
#elif defined _WIN32
#    include "MACE/Utility/internal/CPUTimeStopwatch/WindowsCPUTimeStopwatch.h++"
// Fallback implementation:
#else
#    include "MACE/Utility/internal/CPUTimeStopwatch/FallbackCPUTimeStopwatch.h++"
#endif

#include <concepts>
#include <limits>

namespace MACE::inline Utility {

/// @brief CPU stopwatch better than std::clock() when available.
template<std::floating_point ATime = double>
    requires(std::numeric_limits<ATime>::digits >= std::numeric_limits<double>::digits)
class CPUTimeStopwatch final : public internal::CPUTimeStopwatch<ATime> {};

} // namespace MACE::inline Utility
