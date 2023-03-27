#pragma once

#include <version>

#ifdef __cpp_lib_constexpr_cmath // C++2b
#    include <cmath>
#else // backport
#    include <concepts>
#endif

namespace MACE::inline Compatibility::std2b {

constexpr auto abs(std::floating_point auto x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::abs(x);
#else // backport
    return x < 0 ? -x : x;
#endif
}

constexpr auto fabs(std::floating_point auto x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabs(x);
#else // backport
    return abs(x);
#endif
}

float fabsf(float x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabsf(x);
#else // backport
    return abs(x);
#endif
}

long double fabsl(long double x) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabsl(x);
#else // backport
    return abs(x);
#endif
}

double fabs(std::integral auto n) {
#ifdef __cpp_lib_constexpr_cmath // C++2b
    return std::fabs(n);
#else // backport
    return n < 0 ? -static_cast<double>(n) :
                   static_cast<double>(n);
#endif
}

} // namespace MACE::inline Compatibility::std2b
