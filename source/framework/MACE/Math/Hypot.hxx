#pragma once

#include "MACE/Concept/FundamentalType.hxx"

#include <cmath>
#include <concepts>

namespace MACE::Math {

constexpr auto Hypot2(Concept::Arithmetic auto x, Concept::Arithmetic auto y) {
    return x * x + y * y;
}

constexpr auto Hypot2(Concept::Arithmetic auto x, Concept::Arithmetic auto... y) {
    return x * x + Hypot2(y...);
}

auto Hypot(std::floating_point auto... x) {
    return std::sqrt(Hypot2(x...));
}

} // namespace MACE::Math
