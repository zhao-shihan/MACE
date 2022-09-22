#pragma once

#include "MACE/Concept/NumericVector.hxx"

#include <concepts>
#include <cstddef>

namespace MACE::Concept {

template<class T, typename F, std::size_t N>
concept MathVector = requires(const T& u, const T& v, const F& c) {
    requires NumericVector<T, F, N>;
    { -u } -> std::convertible_to<T>;
    { u + v } -> std::convertible_to<T>;
    { u - v } -> std::convertible_to<T>; // clang-format off
    { c * u } -> std::convertible_to<T>;
    { u * c } -> std::convertible_to<T>; // clang-format on
    { u / c } -> std::convertible_to<T>;
};

template<class T>
concept MathVector2D = MathVector<T, double, 2>;
template<class T>
concept MathVector3D = MathVector<T, double, 3>;
template<class T>
concept MathVector4D = MathVector<T, double, 4>;
template<class T>
concept MathVector2F = MathVector<T, float, 2>;
template<class T>
concept MathVector3F = MathVector<T, float, 3>;
template<class T>
concept MathVector4F = MathVector<T, float, 4>;

} // namespace MACE::Concept
