#pragma once

#include "MACE/Compatibility/std2b/constexpr_cmath.hxx"
#include "MACE/Math/IntegerPower.hxx"

#include <cmath>
#include <concepts>
#include <limits>
#include <utility>

namespace MACE::Math {

namespace internal {

template<std::floating_point T>
constexpr auto defaultTolerance = Math::PowRZ<std::numeric_limits<T>::digits / 2, T>(2) *
                                  std::numeric_limits<T>::epsilon();

} // namespace internal

template<std::floating_point T = double>
constexpr std::pair<T, bool> FindRoot(const std::regular_invocable<T> auto& F,
                                      const std::regular_invocable<T> auto& DF,
                                      T x0,
                                      const T tolerance = internal::defaultTolerance<T>,
                                      const int maxIterations = 1000);

template<std::floating_point T = double>
constexpr std::pair<T, bool> FindRoot(const std::regular_invocable<T> auto& F,
                                      const T x0,
                                      const T tolerance = internal::defaultTolerance<T>,
                                      const int maxIterations = 1000);

} // namespace MACE::Math

#include "MACE/Math/FindRoot.inl"
