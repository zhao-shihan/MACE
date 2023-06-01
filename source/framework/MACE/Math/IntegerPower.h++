#pragma once

#include "MACE/Concept/FundamentalType.h++"

#include <concepts>

namespace MACE::Math {

////////////////////////////////////////////////////////////////
// PowZN: {Integral} -> {Integral},
//        PowZN<N>(m)   = m^N  (partial compile-time),
//        PowZN<M, N>() = M^N  (pure compile-time).
////////////////////////////////////////////////////////////////

template<int N>
    requires(N >= 0)
constexpr auto PowZN(std::integral auto m) {
    if constexpr (N == 0) {
        return static_cast<decltype(m)>(1);
    } else if constexpr (N == 1) {
        return m;
    } else {
        if constexpr (N % 2 == 0) {
            const auto k = PowZN<N / 2>(m);
            return k * k;
        } else if constexpr (N % 3 == 0) {
            const auto k = PowZN<N / 3>(m);
            return k * k * k;
        } else {
            const auto k = PowZN<(N - 1) / 2>(m);
            return k * m * k;
        }
    }
}

////////////////////////////////////////////////////////////////
// PowRZ: {FloatingPoint} -> {FloatingPoint},
//        PowRZ<N>(x) = x^N  (partial compile-time).
////////////////////////////////////////////////////////////////

// FP version:

template<int N>
constexpr auto PowRZ(std::floating_point auto x) {
    if constexpr (N < 0) {
        return PowRZ<-N>(1 / x);
    } else if constexpr (N == 0) {
        return static_cast<decltype(x)>(1);
    } else if constexpr (N == 1) {
        return x;
    } else {
        if constexpr (N % 2 == 0) {
            const auto u = PowRZ<N / 2>(x);
            return u * u;
        } else if constexpr (N % 3 == 0) {
            const auto u = PowRZ<N / 3>(x);
            return u * u * u;
        } else {
            const auto u = PowRZ<(N - 1) / 2>(x);
            return u * x * u;
        }
    }
}

// Intergral version:

template<int N, std::floating_point F = double>
constexpr auto PowRZ(std::integral auto x) {
    return PowRZ<N>(static_cast<F>(x));
}

// Useful shorthands:

#define MACE_UTILITY_SMALL_INTEGER_FP_POWER(N)          \
    constexpr auto Pow##N(Concept::Arithmetic auto x) { \
        return PowRZ<N>(x);                             \
    }
MACE_UTILITY_SMALL_INTEGER_FP_POWER(2)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(3)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(4)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(5)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(6)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(7)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(8)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(9)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(10)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(11)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(12)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(13)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(14)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(15)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(16)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(17)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(18)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(19)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(20)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(21)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(22)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(23)
MACE_UTILITY_SMALL_INTEGER_FP_POWER(24)
#undef MACE_UTILITY_SMALL_INTEGER_FP_POWER

} // namespace MACE::Math
