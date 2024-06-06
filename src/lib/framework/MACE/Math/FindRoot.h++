#pragma once

#include "MACE/Math/MidPoint.h++"

#include "muc/math"

#include <cmath>
#include <concepts>
#include <limits>
#include <optional>
#include <utility>

namespace MACE::Math::FindRoot {

namespace internal {

template<std::floating_point T>
inline constexpr auto defaultTolerance{muc::pow<std::numeric_limits<T>::digits / 2, T>(2) *
                                       std::numeric_limits<T>::epsilon()};

} // namespace internal

template<std::floating_point T>
auto NewtonRaphson(const std::regular_invocable<T> auto& f,
                   const std::regular_invocable<T> auto& df,
                   T x0,
                   int maxIterations = 1000,
                   T tolerance = internal::defaultTolerance<T>) -> std::pair<T, bool>;

template<std::floating_point T>
auto Secant(const std::regular_invocable<T> auto& f,
            T x0,
            std::optional<T> x1O = {},
            int maxIterations = 1000,
            T tolerance = internal::defaultTolerance<T>) -> std::pair<T, bool>;

} // namespace MACE::Math::FindRoot

#include "MACE/Math/FindRoot.inl"
