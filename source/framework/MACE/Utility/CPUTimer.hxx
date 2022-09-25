#pragma once

// Linux/BSD implementation:
#if (defined linux or defined __linux__ or defined __linux) or \
    (defined __DragonFly__ or defined __FreeBSD__ or defined __NetBSD__ or defined __OpenBSD__)
#    include "MACE/Utility/internal/CPUTimer/CPUTimer4LinuxBSD.hxx"
// Windows implementation:
#elif defined _WIN32
#    include "MACE/Utility/internal/CPUTimer/CPUTimer4Windows.hxx"
// Fallback implementation:
#else
#    include "MACE/Utility/internal/CPUTimer/CPUTimer4Fallback.hxx"
#endif

#include <concepts>
#include <limits>

namespace MACE::Utility {

/// @brief CPU timer better than std::clock() when available.
template<std::floating_point ATime = double>
    requires(std::numeric_limits<ATime>::digits >= std::numeric_limits<double>::digits)
class CPUTimer final : public internal::CPUTimer<ATime> {};

} // namespace MACE::Utility
