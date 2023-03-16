#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>

namespace MACE::Math {

constexpr auto Hypot2(const std::floating_point auto... x)
    requires(sizeof...(x) >= 2)
{
    return (... + (x * x));
}

auto Hypot(const std::floating_point auto... x)
    requires(sizeof...(x) >= 2)
{
    return std::sqrt(Hypot2(x...));
}

template<std::floating_point T = double>
constexpr auto Hypot2(const auto... x)
    requires(sizeof...(x) >= 2 and not(... and std::floating_point<decltype(x)>))
{
    return Hypot2<std::common_type_t<T, decltype(x)...>>(x...);
}

template<std::floating_point T = double>
auto Hypot(const auto... x)
    requires(sizeof...(x) >= 2 and not(... and std::floating_point<decltype(x)>))
{
    return Hypot<std::common_type_t<T, decltype(x)...>>(x...);
}

} // namespace MACE::Math
