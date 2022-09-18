#pragma once

#include <cinttypes>
#include <concepts>

namespace MACE::Math {

constexpr bool IsOdd(std::integral auto n) {
    return n & 1;
}

constexpr bool IsEven(std::integral auto n) {
    return not IsOdd(n);
}

template<intmax_t N>
consteval bool IsOdd() {
    return IsOdd(N);
}

template<intmax_t N>
consteval bool IsEven() {
    return not IsOdd<N>();
}

} // namespace MACE::Math
