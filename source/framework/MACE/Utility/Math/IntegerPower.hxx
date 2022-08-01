#pragma once

#include <cinttypes>
#include <cmath>
#include <concepts>

namespace MACE::Utility::Math {

////////////////////////////////////////////////////////////////
// PowI: {Integral} -> {Integral},
//        PowI<N>(m)   = m^N  (partial compile-time),
//        PowI<M, N>() = M^N  (pure compile-time).
////////////////////////////////////////////////////////////////

// Partial compile-time version:

template<unsigned N>
constexpr auto PowI(std::integral auto m) {
    if constexpr (N == 0) {
        return decltype(m)(1);
    } else if constexpr (N == 1) {
        return m;
    } else {
        if constexpr (N % 2 == 0) {
            const auto k = PowI<N / 2>(m);
            return k * k;
        } else if constexpr (N % 3 == 0) {
            const auto k = PowI<N / 3>(m);
            return k * k * k;
        } else {
            const auto k = PowI<(N - 1) / 2>(m);
            return k * m * k;
        }
    }
}

// Pure compile-time version:

template<intmax_t M, unsigned N>
consteval auto PowI() {
    return PowI<N>(M);
}

////////////////////////////////////////////////////////////////
// PowZ: {FloatingPoint} -> {FloatingPoint},
//        PowZ<N>(x) = x^N  (partial compile-time).
////////////////////////////////////////////////////////////////

// FP version:

template<int N>
constexpr auto PowZ(std::floating_point auto x) {
    if constexpr (N < 0) {
        return PowZ<-N>(1 / x);
    } else if constexpr (N == 0) {
        return decltype(x)(1);
    } else if constexpr (N == 1) {
        return x;
    } else {
        if constexpr (N % 2 == 0) {
            const auto u = PowZ<N / 2>(x);
            return u * u;
        } else if constexpr (N % 3 == 0) {
            const auto u = PowZ<N / 3>(x);
            return u * u * u;
        } else {
            const auto u = PowZ<(N - 1) / 2>(x);
            return u * x * u;
        }
    }
}

// Intergral version:

template<int N, std::floating_point FloatT = double>
constexpr auto PowZ(std::integral auto x) {
    return PowZ<N>(FloatT(x));
}

// Useful shorthands:

#define MACE_UTILITY_SMALL_INTEGER_FP_POWER(N) \
    template<typename T>                       \
    constexpr auto Pow##N(T&& x) {             \
        return PowZ<N>(std::forward<T>(x));    \
    }
MACE_UTILITY_SMALL_INTEGER_FP_POWER(2)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(3)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(4)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(5)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(6)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(7)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(8)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(9)
#undef MACE_UTILITY_SMALL_INTEGER_FP_POWER

} // namespace MACE::Utility::Math
