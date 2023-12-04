#pragma once

#include "MACE/Compatibility/std2b/constexpr_cmath.h++"
#include "MACE/Math/IntegerPower.h++"

#include <cmath>
#include <concepts>
#include <limits>
#include <optional>
#include <utility>

namespace MACE::Math::FindRoot {

namespace internal {

template<std::floating_point T>
inline constexpr auto defaultTolerance = Math::Pow<std::numeric_limits<T>::digits / 2, T>(2) *
                                         std::numeric_limits<T>::epsilon();

} // namespace internal

template<std::floating_point T = double>
auto NewtonRaphson(const std::regular_invocable<T> auto& f,
                   const std::regular_invocable<T> auto& df,
                   T x0,
                   const int maxIterations = 1000,
                   const T tolerance = internal::defaultTolerance<T>) -> std::pair<T, bool>;

template<std::floating_point T = double>
auto Secant(const std::regular_invocable<T> auto& f,
            T x0,
            const std::optional<T> x1O = {},
            const int maxIterations = 1000,
            const T tolerance = internal::defaultTolerance<T>) -> std::pair<T, bool>;

} // namespace MACE::Math::FindRoot

#include "MACE/Math/FindRoot.inl"
