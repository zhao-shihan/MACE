#pragma once

#include "MACE/Utility/Math/Parity.hxx"

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
        if constexpr (IsEven<N>()) {
            const auto k = PowI<N / 2>(m);
            return k * k;
        } else {
            const auto k = PowI<(N - 1) / 2>(m);
            return k * m * k;
        }
    }
}

// Pure compile-time version:

template<intmax_t M, unsigned N>
consteval intmax_t PowI() {
    if constexpr (N == 0) {
        return (intmax_t)1;
    } else if constexpr (N == 1) {
        return M;
    } else {
        if constexpr (IsEven<N>()) {
            constexpr auto k = PowI<M, N / 2>();
            return k * k;
        } else {
            constexpr auto k = PowI<M, (N - 1) / 2>();
            return k * M * k;
        }
    }
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
        if constexpr (IsEven<N>()) {
            const auto u = PowZ<N / 2>(x);
            return u * u;
        } else {
            const auto u = PowZ<(N - 1) / 2>(x);
            return u * x * u;
        }
    }
}

// Intergral version:

template<int N, std::floating_point F = double>
constexpr F PowZ(std::integral auto x) {
    return PowZ<N>(F(x));
}

} // namespace MACE::Utility::Math
