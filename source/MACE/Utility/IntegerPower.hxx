#pragma once

#include <complex>
#include <concepts>

namespace MACE::Utility {

template<int N, typename T>
constexpr T PowInt(T x) requires(
    N >= 0 and (std::floating_point<T> or
                std::same_as<T, std::complex<float>> or
                std::same_as<T, std::complex<double>> or
                std::same_as<T, std::complex<long double>> or
                (std::integral<T> and not std::same_as<T, bool>))) {
    if constexpr (N == 0) {
        return 1;
    } else if constexpr (N == 1) {
        return x;
    } else {
        return x * PowInt<N - 1>(x);
    }
}

template<int N, std::floating_point T>
constexpr T PowInt(T x) requires(
    N < 0) {
    return 1 / PowInt<-N>(x);
}

template<int N, typename T>
constexpr T PowInt(T x) requires(
    N < 0 and (std::same_as<T, std::complex<float>> or
               std::same_as<T, std::complex<double>> or
               std::same_as<T, std::complex<long double>>)) {
    return T(1, 0) / PowInt<-N>(x);
}

} // namespace MACE::Utility
