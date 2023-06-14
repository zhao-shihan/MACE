#pragma once

#include "MACE/Utility/InlineMacro.h++"

#include <cinttypes>
#include <concepts>
#include <version>

#ifdef __cpp_lib_constexpr_cmath // C++2b
#    include <cmath>
#    include <cstdlib>
#else // backport
#    include "MACE/Compatibility/std2b/unreachable.h++"
#endif

namespace MACE::inline Compatibility::std2b {

///////////////////////////////////////////////////////////////////////////////
// floating point abs
///////////////////////////////////////////////////////////////////////////////

MACE_ALWAYS_INLINE constexpr auto abs(std::floating_point auto x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(x);
#else // backport
#    if defined __clang__ or defined __GNUC__
    if constexpr (std::same_as<decltype(x), double>) {
        return __builtin_fabs(x);
    } else if constexpr (std::same_as<decltype(x), float>) {
        return __builtin_fabsf(x);
    } else if constexpr (std::same_as<decltype(x), long double>) {
        return __builtin_fabsl(x);
    } else {
        return unreachable();
    }
#    else
    return x >= 0 ? x : -x;
#    endif
#endif
}

MACE_ALWAYS_INLINE constexpr auto fabs(std::floating_point auto x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabs(x);
#else // backport
    return abs(x);
#endif
}

MACE_ALWAYS_INLINE constexpr auto fabsf(float x) -> float {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabsf(x);
#else // backport
    return abs(x);
#endif
}

MACE_ALWAYS_INLINE constexpr auto fabsl(long double x) -> long double {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabsl(x);
#else // backport
    return abs(x);
#endif
}

MACE_ALWAYS_INLINE constexpr auto fabs(std::integral auto n) -> double {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabs(n);
#else // backport
    return abs(static_cast<double>(n));
#endif
}

///////////////////////////////////////////////////////////////////////////////
// integral abs
///////////////////////////////////////////////////////////////////////////////

MACE_ALWAYS_INLINE constexpr auto abs(int n) -> int {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(n);
#else // backport
    return n >= 0 ? n : -n;
#endif
}

MACE_ALWAYS_INLINE constexpr auto abs(long n) -> long {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(n);
#else // backport
    return n >= 0 ? n : -n;
#endif
}

MACE_ALWAYS_INLINE constexpr auto abs(long long n) -> long long {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(n);
#else // backport
    return n >= 0 ? n : -n;
#endif
}

MACE_ALWAYS_INLINE constexpr auto labs(long n) -> long {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::labs(n);
#else // backport
    return n >= 0 ? n : -n;
#endif
}

MACE_ALWAYS_INLINE constexpr auto llabs(long long n) -> long long {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::llabs(n);
#else // backport
    return n >= 0 ? n : -n;
#endif
}

// MACE_ALWAYS_INLINE constexpr std::intmax_t abs(std::intmax_t n) {
// #    ifdef __cpp_lib_constexpr_cmath // C++2b
//     return std::abs(n);
// #    else                            // backport
//     return n >= 0 ? n : -n;
// #    endif
// }

// MACE_ALWAYS_INLINE constexpr std::intmax_t imaxabs(std::intmax_t n) {
// #ifdef __cpp_lib_constexpr_cmath // C++2b
//     return std::imaxabs(n);
// #else                            // backport
//     return n >= 0 ? n : -n;
// #endif
// }

} // namespace MACE::inline Compatibility::std2b
