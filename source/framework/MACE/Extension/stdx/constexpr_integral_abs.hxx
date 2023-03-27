#pragma once

#include <cinttypes>

namespace MACE::inline Extension::stdx {

constexpr int abs(int n) {
    return n < 0 ? -n : n;
}

constexpr long abs(long n) {
    return n < 0 ? -n : n;
}

constexpr long long abs(long long n) {
    return n < 0 ? -n : n;
}

constexpr long labs(long n) {
    return n < 0 ? -n : n;
}

constexpr long long llabs(long long n) {
    return n < 0 ? -n : n;
}

constexpr std::intmax_t abs(std::intmax_t n) {
    return n < 0 ? -n : n;
}

constexpr std::intmax_t imaxabs(std::intmax_t n) {
    return n < 0 ? -n : n;
}

} // namespace MACE::inline Extension::stdx
