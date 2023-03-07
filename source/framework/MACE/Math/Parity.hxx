#pragma once

#include <cinttypes>
#include <concepts>

namespace MACE::Math {

constexpr bool IsOdd(std::integral auto n) {
    return n & static_cast<decltype(n)>(1);
}

constexpr bool IsEven(std::integral auto n) {
    return not IsOdd(n);
}

} // namespace MACE::Math
