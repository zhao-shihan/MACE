#pragma once

#include <cinttypes>
#include <concepts>

namespace MACE::Utility::Math {

constexpr bool IsOdd(std::integral auto n) {
    return n & 1;
}

constexpr bool IsEven(std::integral auto n) {
    return not IsOdd(n);
}

template<intmax_t N>
consteval bool IsOdd() {
    return N & 1;
}

template<intmax_t N>
consteval bool IsEven() {
    return not IsOdd<N>();
}

} // namespace MACE::Utility::Math
