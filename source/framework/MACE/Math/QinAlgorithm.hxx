#pragma once

#include <concepts>
#include <initializer_list>
#include <ranges>

namespace MACE::Math {

template<std::floating_point T, std::ranges::range C = std::initializer_list<T>>
constexpr auto QinPolynomial(T x, C&& coefficientList) {
    auto c = std::ranges::cend(coefficientList);
    const auto first = std::ranges::cbegin(coefficientList);
    if (c == first) { return static_cast<T>(0); }
    auto p = static_cast<T>(*--c);
    if (c != first) {
        do {
            p = p * x + static_cast<T>(*--c);
        } while (c != first);
    }
    return p;
}

template<std::floating_point T, std::ranges::range A = std::initializer_list<T>, std::ranges::range B = std::initializer_list<T>>
constexpr auto QinRational(T x, A&& numerator, B&& denominator) {
    return QinPolynomial(x, std::forward<A>(numerator)) / QinPolynomial(x, std::forward<B>(denominator));
}

template<std::floating_point T = double, std::ranges::range C = std::initializer_list<T>>
constexpr auto QinPolynomial(std::integral auto x, C&& coefficientList) {
    return QinPolynomial<T>(x, std::forward<C>(coefficientList));
}

template<std::floating_point T = double, std::ranges::range A = std::initializer_list<T>, std::ranges::range B = std::initializer_list<T>>
constexpr auto QinRational(std::integral auto x, A&& numerator, B&& denominator) {
    return QinRational<T>(x, std::forward<A>(numerator), std::forward<B>(denominator));
}

} // namespace MACE::Math
