#pragma once

#include "MACE/Utility/InlineMacro.hxx"

#include <cinttypes>
#include <concepts>
#include <version>

#ifdef __cpp_lib_constexpr_cmath // C++2b
#    include <cmath>
#    include <cstdlib>
#else // backport
#    include "MACE/Compatibility/std2b/unreachable.hxx"
#endif

namespace MACE::inline Compatibility::std2b {

///////////////////////////////////////////////////////////////////////////////
// floating point abs
///////////////////////////////////////////////////////////////////////////////

MACE_ALWAYS_INLINE constexpr auto abs(std::floating_point auto x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(x);
#else                            // backport
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
#else                            // backport
    return abs(x);
#endif
}

MACE_ALWAYS_INLINE constexpr float fabsf(float x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabsf(x);
#else                            // backport
    return abs(x);
#endif
}

MACE_ALWAYS_INLINE constexpr long double fabsl(long double x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabsl(x);
#else                            // backport
    return abs(x);
#endif
}

MACE_ALWAYS_INLINE constexpr double fabs(std::integral auto n) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabs(n);
#else                            // backport
    return abs(static_cast<double>(n));
#endif
}

///////////////////////////////////////////////////////////////////////////////
// integral abs
///////////////////////////////////////////////////////////////////////////////

MACE_ALWAYS_INLINE constexpr int abs(int n) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(n);
#else                            // backport
    return n >= 0 ? n : -n;
#endif
}

MACE_ALWAYS_INLINE constexpr long abs(long n) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(n);
#else                            // backport
    return n >= 0 ? n : -n;
#endif
}

MACE_ALWAYS_INLINE constexpr long long abs(long long n) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(n);
#else                            // backport
    return n >= 0 ? n : -n;
#endif
}

MACE_ALWAYS_INLINE constexpr long labs(long n) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::labs(n);
#else                            // backport
    return n >= 0 ? n : -n;
#endif
}

MACE_ALWAYS_INLINE constexpr long long llabs(long long n) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::llabs(n);
#else                            // backport
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
