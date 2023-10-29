#pragma once

#include "MACE/Utility/InlineMacro.h++"

#include <cinttypes>
#include <concepts>
#include <cstdlib>
#include <limits>
#include <type_traits>
#include <version>

#ifdef __cpp_lib_constexpr_cmath // C++2b
#    include <cmath>
#endif

namespace MACE::inline Compatibility::std2b {

///////////////////////////////////////////////////////////////////////////////
// div
///////////////////////////////////////////////////////////////////////////////

constexpr auto div(int x, int y) -> std::div_t {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::div(x, y);
#else // backport
    return {.quot = x / y, .rem = x % y};
#endif
}

constexpr auto div(long x, long y) -> std::ldiv_t {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::div(x, y);
#else // backport
    return {.quot = x / y, .rem = x % y};
#endif
}

constexpr auto div(long long x, long long y) -> std::lldiv_t {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::div(x, y);
#else // backport
    return {.quot = x / y, .rem = x % y};
#endif
}

constexpr auto ldiv(long x, long y) -> std::ldiv_t {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::ldiv(x, y);
#else // backport
    return div(x, y);
#endif
}

constexpr auto lldiv(long long x, long long y) -> std::lldiv_t {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::lldiv(x, y);
#else // backport
    return div(x, y);
#endif
}

// constexpr auto div(std::intmax_t x, std::intmax_t y) -> std::imaxdiv_t {
// #ifdef __cpp_lib_constexpr_cmath // C++2b
//     return std::div(x, y);
// #else // backport
//     return {.quot = x / y, .rem = x % y};
// #endif
// }

constexpr auto imaxdiv(std::intmax_t x, std::intmax_t y) -> std::imaxdiv_t {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::imaxdiv(x, y);
#else // backport
    return {.quot = x / y, .rem = x % y};
#endif
}

///////////////////////////////////////////////////////////////////////////////
// floating point abs
///////////////////////////////////////////////////////////////////////////////

MACE_ALWAYS_INLINE constexpr auto abs(std::floating_point auto x) -> decltype(x) {
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
    }
#    else
    return x >= 0 ? x : -x;
#    endif
#endif
}

MACE_ALWAYS_INLINE constexpr auto fabs(std::floating_point auto x) -> decltype(x) {
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
    return abs(n);
#endif
}

MACE_ALWAYS_INLINE constexpr auto llabs(long long n) -> long long {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::llabs(n);
#else // backport
    return abs(n);
#endif
}

// MACE_ALWAYS_INLINE constexpr auto abs(std::intmax_t n) -> std::intmax_t {
// #ifdef __cpp_lib_constexpr_cmath // C++2b
//     return std::abs(n);
// #else // backport
//     return n >= 0 ? n : -n;
// #endif
// }

MACE_ALWAYS_INLINE constexpr auto imaxabs(std::intmax_t n) -> std::intmax_t {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::imaxabs(n);
#else // backport
    return n >= 0 ? n : -n;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// isnan
///////////////////////////////////////////////////////////////////////////////

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
