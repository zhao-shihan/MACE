#pragma once

#include "MACE/Utility/Math/Parity.hxx"

#include <cmath>
#include <concepts>

namespace MACE::Utility::Math {

// FP version:

#define MACE_UTILITY_FLOATING_POINT_POWZ(FPType, FPSuffix, PowZAdvantageousLowerLimit, PowZAdvantageousUpperLimit) \
    template<int N>                                                                                                \
    constexpr FPType PowZ(FPType x) {                                                                              \
        if constexpr (PowZAdvantageousLowerLimit <= N and N <= PowZAdvantageousUpperLimit) {                       \
            if constexpr (N < 0) {                                                                                 \
                return 1.0##FPSuffix / PowZ<-N>(x);                                                                \
            } else if constexpr (N == 0) {                                                                         \
                return 1.0##FPSuffix;                                                                              \
            } else if constexpr (N == 1) {                                                                         \
                return x;                                                                                          \
            } else {                                                                                               \
                if constexpr (IsEven<N>()) {                                                                       \
                    const auto y = PowZ<N / 2>(x);                                                                 \
                    return y * y;                                                                                  \
                } else {                                                                                           \
                    const auto y = PowZ<(N - 1) / 2>(x);                                                           \
                    return y * x * y;                                                                              \
                }                                                                                                  \
            }                                                                                                      \
        } else {                                                                                                   \
            return std::pow(x, (FPType)N);                                                                         \
        }                                                                                                          \
    }

MACE_UTILITY_FLOATING_POINT_POWZ(float, F, std::numeric_limits<int>::min() / 2, std::numeric_limits<int>::max() / 2)
MACE_UTILITY_FLOATING_POINT_POWZ(double, , std::numeric_limits<int>::min() / 2, std::numeric_limits<int>::max() / 2)
MACE_UTILITY_FLOATING_POINT_POWZ(long double, L, -8192, 8192)

#undef MACE_UTILITY_FLOATING_POINT_POWZ

// Intergral version:

template<int N, std::floating_point FP = double>
constexpr FP PowZ(std::integral auto x) {
    return PowZ<N>((FP)x);
}

// Integral power returns integral:

// clang-format off
template<int N, std::integral I>
    requires (N >= 0)
constexpr I PowI(I x) {
    if constexpr (N == 0) {
        return 1;
    } else if constexpr (N == 1) {
        return x;
    } else {
        if constexpr (IsEven<N>()) {
            const auto y = PowI<N / 2>(x);
            return y * y;
        } else {
            const auto y = PowI<(N - 1) / 2>(x);
            return y * x * y;
        }
    }
}
// clang-format on

} // namespace MACE::Utility::Math
