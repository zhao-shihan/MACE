#pragma once

#include <concepts>
#include <cstdint>
#include <utility>

namespace MACE::Utility {

// VSCode C++ extension bound clang-format does not new enough to support C++20. (Last check: 2022/5)
// clang-format off

template<typename T>
concept Multipliable = requires(T x, T y) {
    { x * y } -> std::same_as<T>;
    { T(1) };
};

template<typename T>
concept NoexceptMultipliable = requires(T x, T y) {
    { x * y } noexcept -> std::same_as<T>;
    { T(1) };
};

template<uintmax_t N, Multipliable T>
struct PowIntNonNegFunctor {
    T operator()(T x) noexcept(NoexceptMultipliable<T>) {
        return x * PowIntNonNegFunctor<N - 1, T>()(x);
    }
};

template<Multipliable T>
struct PowIntNonNegFunctor<1, T> {
    T operator()(T x) noexcept {
        return x;
    }
};

template<Multipliable T>
struct PowIntNonNegFunctor<0, T> {
    T operator()(T) noexcept {
        return 1;
    }
};

template<uintmax_t N, Multipliable T>
constexpr T PowInt(T x) noexcept(NoexceptMultipliable<T>) {
    return PowIntNonNegFunctor<N, T>()(x);
}

template<intmax_t N, std::floating_point FP>
    requires (N < 0)
constexpr FP PowInt(FP x) noexcept {
    return 1 / PowInt<-N, FP>(x);
}

// clang-format on

} // namespace MACE::Utility
