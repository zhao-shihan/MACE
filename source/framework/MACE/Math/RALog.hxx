#pragma once

#include "MACE/Compatibility/std2b/assume.hxx"
#include "MACE/Math/QinAlgorithm.hxx"

#include <bit>
#include <cfenv>
#include <climits>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <numbers>
#include <type_traits>

namespace MACE::Math {

#define MACE_MATH_RA_N_LOG_FAMILY_DECLARE(N)                \
    template<std::floating_point T>                         \
    constexpr T RA##N##Log(T x) noexcept;                   \
    constexpr auto RA##N##Log(long double x) = delete;      \
    template<std::floating_point T = double>                \
    constexpr T RA##N##Log(std::integral auto x) noexcept;  \
                                                            \
    template<std::floating_point T>                         \
    constexpr T RA##N##Log2(T x) noexcept;                  \
    constexpr auto RA##N##Log2(long double x) = delete;     \
    template<std::floating_point T = double>                \
    constexpr T RA##N##Log2(std::integral auto x) noexcept; \
                                                            \
    template<std::floating_point T>                         \
    constexpr T RA##N##Log10(T x) noexcept;                 \
    constexpr auto RA##N##Log10(long double x) = delete;    \
    template<std::floating_point T = double>                \
    constexpr T RA##N##Log10(std::integral auto x) noexcept;

#define MACE_MATH_RA_N_LOG_FAMILY_DELETE(N, T) \
    constexpr auto RA##N##Log(T x) = delete;   \
    constexpr auto RA##N##Log2(T x) = delete;  \
    constexpr auto RA##N##Log10(T x) = delete;

MACE_MATH_RA_N_LOG_FAMILY_DECLARE(2)

MACE_MATH_RA_N_LOG_FAMILY_DECLARE(3)

MACE_MATH_RA_N_LOG_FAMILY_DECLARE(4)
MACE_MATH_RA_N_LOG_FAMILY_DELETE(4, float)

MACE_MATH_RA_N_LOG_FAMILY_DECLARE(5)
MACE_MATH_RA_N_LOG_FAMILY_DELETE(5, float)

MACE_MATH_RA_N_LOG_FAMILY_DECLARE(6)
MACE_MATH_RA_N_LOG_FAMILY_DELETE(6, float)

#undef MACE_MATH_RA_N_LOG_FAMILY_DELETE
#undef MACE_MATH_RA_N_LOG_FAMILY_DECLARE

} // namespace MACE::Math

#include "RALog.inl"
