#pragma once

#include "MACE/Math/RALog.h++"

#include <cmath>
#include <concepts>

namespace MACE::Math {

template<std::floating_point T>
constexpr T Log(T x) noexcept;
template<std::floating_point T = double>
constexpr auto Log(std::integral auto x) noexcept { return Log(static_cast<T>(x)); }

template<std::floating_point T>
constexpr T Log2(T x) noexcept;
template<std::floating_point T = double>
constexpr auto Log2(std::integral auto x) noexcept { return Log2(static_cast<T>(x)); }

template<std::floating_point T>
constexpr T Log10(T x) noexcept;
template<std::floating_point T = double>
constexpr auto Log10(std::integral auto x) noexcept { return Log10(static_cast<T>(x)); }

} // namespace MACE::Math

#include "MACE/Math/Log.inl"
