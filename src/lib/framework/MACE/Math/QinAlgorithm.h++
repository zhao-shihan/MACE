#pragma once

#include <concepts>
#include <initializer_list>
#include <limits>
#include <ranges>

namespace MACE::Math {

template<std::floating_point T,
         std::ranges::range C = std::initializer_list<T>>
constexpr auto QinPolynomial(const C& coefficientList,
                             T x) -> T {
    auto c{std::ranges::crbegin(coefficientList)};
    const auto end{std::ranges::crend(coefficientList)};
    if (c == end) {
        using nl = std::numeric_limits<T>;
        return nl::has_quiet_NaN ? nl::quiet_NaN() : 0;
    }
    T p{*c++};
    while (c != end) {
        p = p * x + *c++;
    }
    return p;
}

template<std::floating_point T = double,
         std::ranges::range C = std::initializer_list<T>>
constexpr auto QinPolynomial(const C& coefficientList,
                             std::integral auto x) -> T {
    return QinPolynomial<T>(coefficientList, x);
}

template<std::floating_point T,
         std::ranges::range A = std::initializer_list<T>,
         std::ranges::range B = std::initializer_list<T>>
constexpr auto QinRational(const A& numerator,
                           const B& denominator,
                           T x) -> T {
    return QinPolynomial(numerator, x) / QinPolynomial(denominator, x);
}

template<std::floating_point T = double,
         std::ranges::range A = std::initializer_list<T>,
         std::ranges::range B = std::initializer_list<T>>
constexpr auto QinRational(const A& numerator,
                           const B& denominator,
                           std::integral auto x) -> T {
    return QinRational<T>(numerator, denominator, x);
}

} // namespace MACE::Math
