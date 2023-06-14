#pragma once

#include "MACE/Utility/InlineMacro.h++"

#include <concepts>
#include <limits>
#include <version>

#ifdef __cpp_lib_constexpr_cmath // C++2b
#    include <cmath>
#endif

namespace MACE::inline Compatibility::std2b {

MACE_ALWAYS_INLINE constexpr auto isnan(const std::floating_point auto x) -> bool {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::isnan(x);
#else // backport
    return x != x;
#endif
}

MACE_ALWAYS_INLINE constexpr auto isnan(const std::integral auto n) -> bool {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::isnan(n);
#else // backport
    if constexpr (std::numeric_limits<double>::is_iec559) {
        return false;
    } else {
        return isnan(static_cast<double>(n));
    }
#endif
}

} // namespace MACE::inline Compatibility::std2b
