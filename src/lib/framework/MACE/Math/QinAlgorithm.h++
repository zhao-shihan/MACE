#pragma once

#include <concepts>
#include <limits>
#include <initializer_list>
#include <ranges>

namespace MACE::Math {

template<std::floating_point T,
         std::ranges::range C = std::initializer_list<T>>
constexpr auto QinPolynomial(const T x,
                             const C& coefficientList) -> T {
    using nl = std::numeric_limits<T>;
    auto c = std::ranges::crbegin(coefficientList);
    const auto end = std::ranges::crend(coefficientList);
    if (c == end) { return nl::has_quiet_NaN ? nl::quiet_NaN() : 0; }
    T p = *c++;
    do {
        p = p * x + *c++;
    } while (c != end);
    return p;
}

template<std::floating_point T,
         std::ranges::range A = std::initializer_list<T>,
         std::ranges::range B = std::initializer_list<T>>
constexpr auto QinRational(const T x,
                           const A& numerator,
                           const B& denominator) -> T {
    return QinPolynomial(x, numerator) / QinPolynomial(x, denominator);
}

template<std::floating_point T = double,
         std::ranges::range C = std::initializer_list<T>>
constexpr auto QinPolynomial(const std::integral auto x,
                             const C& coefficientList) -> T {
    return QinPolynomial<T>(x, coefficientList);
}

template<std::floating_point T = double,
         std::ranges::range A = std::initializer_list<T>,
         std::ranges::range B = std::initializer_list<T>>
constexpr auto QinRational(const std::integral auto x,
                           const A& numerator,
                           const B& denominator) -> T {
    return QinRational<T>(x, numerator, denominator);
}

} // namespace MACE::Math
