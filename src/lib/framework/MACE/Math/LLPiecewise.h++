#pragma once

#include <cassert>
#include <concepts>
#include <limits>

namespace MACE::Math {

constexpr auto LLTrunc(std::floating_point auto x) -> long long {
    assert(std::numeric_limits<long long>::min() <= x and x <= std::numeric_limits<long long>::max());
    return x;
}

constexpr auto LLRound(std::floating_point auto x) -> long long {
    assert(std::numeric_limits<long long>::min() <= x and x <= std::numeric_limits<long long>::max());
    return x + (x >= 0 ? 0.5 : -0.5);
}

} // namespace MACE::Math
