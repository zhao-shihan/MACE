#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>

namespace MACE::Math {

constexpr auto Hypot2(std::floating_point auto... x)
    requires(sizeof...(x) >= 2)
{
    return (... + (x * x));
}

auto Hypot(std::floating_point auto... x)
    requires(sizeof...(x) >= 2)
{
    return std::sqrt(Hypot2(x...));
}

template<std::floating_point T = double>
constexpr auto Hypot2(auto... x)
    requires(sizeof...(x) >= 2 and not(... and std::floating_point<decltype(x)>))
{
    return Hypot2<std::common_type_t<T, decltype(x)...>>(x...);
}

template<std::floating_point T = double>
auto Hypot(auto... x)
    requires(sizeof...(x) >= 2 and not(... and std::floating_point<decltype(x)>))
{
    return Hypot<std::common_type_t<T, decltype(x)...>>(x...);
}

} // namespace MACE::Math
