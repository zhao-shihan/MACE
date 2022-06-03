#pragma once

#include <cmath>
#include <concepts>

namespace MACE::Utility::Math {

auto Hypot(std::floating_point auto x, std::floating_point auto y) {
    return std::sqrt(x * x + y * y);
}

auto Hypot(std::floating_point auto x, std::floating_point auto y, std::floating_point auto z) {
    return std::sqrt(x * x + y * y + z * z);
}

} // namespace MACE::Utility::Math
