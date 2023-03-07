#pragma once

#include <cmath>
#include <type_traits>

namespace MACE::Math {

constexpr auto Lerp(const auto a, const auto b, const auto t)
    requires std::is_floating_point_v<std::common_type_t<decltype(a), decltype(b), decltype(t)>>
{
    return a + t * (b - a);
}

constexpr auto LerpSafe(const auto a, const auto b, const auto t)
    requires std::is_floating_point_v<std::common_type_t<decltype(a), decltype(b), decltype(t)>>
{
    return std::lerp(a, b, t);
}

} // namespace MACE::Math
