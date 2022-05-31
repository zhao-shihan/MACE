#pragma once

#include <complex>
#include <concepts>

namespace MACE::Utility {

// clang-format off

template<int N, typename T>
    requires (N >= 0 and (std::floating_point<T> or (std::integral<T> and not std::same_as<T, bool>)))
constexpr T PowZ(T x) {
    if constexpr (N == 0) {
        return 1;
    } else if constexpr (N == 1) {
        return x;
    } else {
        return x * PowZ<N - 1>(x);
    }
}

template<int N, std::floating_point T>
    requires (N < 0)
constexpr T PowZ(T x) {
    return 1 / PowZ<-N>(x);
}

// clang-format on

} // namespace MACE::Utility
