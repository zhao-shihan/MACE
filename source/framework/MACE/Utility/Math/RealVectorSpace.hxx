#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace MACE::Utility::Math::Concept {

template<class T, typename F, std::size_t S>
concept RealVectorSpace = requires(T&& u, T&& v, const T& w, F&& k, const F& c, std::size_t i) { // clang-format off
    requires S > 0; // clang-format on
    requires std::floating_point<F>;
    { -u } -> std::convertible_to<T>;
    { -w } -> std::convertible_to<T>;
    { u + v } -> std::convertible_to<T>;
    { u + w } -> std::convertible_to<T>;
    { w + u } -> std::convertible_to<T>;
    { u - v } -> std::convertible_to<T>;
    { u - w } -> std::convertible_to<T>;
    { w - u } -> std::convertible_to<T>; // clang-format off
    { k * u } -> std::convertible_to<T>;
    { k * w } -> std::convertible_to<T>;
    { c * u } -> std::convertible_to<T>;
    { c * w } -> std::convertible_to<T>;
    { u * k } -> std::convertible_to<T>;
    { w * k } -> std::convertible_to<T>;
    { u * c } -> std::convertible_to<T>;
    { w * c } -> std::convertible_to<T>; // clang-format on
    { u / k } -> std::convertible_to<T>;
    { w / k } -> std::convertible_to<T>;
    { u / c } -> std::convertible_to<T>;
    { w / c } -> std::convertible_to<T>;
    { u[i] } -> std::convertible_to<F&>;
    { w[i] } -> std::convertible_to<const F&>;
};

template<class T>
concept R2VectorSpace = RealVectorSpace<T, double, 2>;

template<class T>
concept R3VectorSpace = RealVectorSpace<T, double, 3>;

template<class T>
concept R4VectorSpace = RealVectorSpace<T, double, 4>;

} // namespace MACE::Utility::Math::Concept
