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

} // namespace MACE::Math
