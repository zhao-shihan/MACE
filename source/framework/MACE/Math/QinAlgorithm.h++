#pragma once

#include <concepts>
#include <initializer_list>
#include <ranges>

namespace MACE::Math {

template<std::floating_point T,
         std::ranges::range C = std::initializer_list<T>>
constexpr auto QinPolynomial(const T x,
                             const C& coefficientList) {
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

template<std::floating_point T,
         std::ranges::range A = std::initializer_list<T>,
         std::ranges::range B = std::initializer_list<T>>
constexpr auto QinRational(const T x,
                           const A& numerator,
                           const B& denominator) {
    return QinPolynomial(x, numerator) / QinPolynomial(x, denominator);
}

template<std::floating_point T = double,
         std::ranges::range C = std::initializer_list<T>>
constexpr auto QinPolynomial(const std::integral auto x,
                             const C& coefficientList) {
    return QinPolynomial<T>(x, coefficientList);
}

template<std::floating_point T = double,
         std::ranges::range A = std::initializer_list<T>,
         std::ranges::range B = std::initializer_list<T>>
constexpr auto QinRational(const std::integral auto x,
                           const A& numerator,
                           const B& denominator) {
    return QinRational<T>(x, numerator, denominator);
}

} // namespace MACE::Math
