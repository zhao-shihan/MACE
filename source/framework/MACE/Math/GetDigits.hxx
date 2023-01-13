#pragma once

#include <concepts>

namespace MACE::Math {

/// @brief Get n-based digits of an integer.
/// @param m The integer.
/// @param base The base.
/// @param includeSign Set whether the digits in return includes "-" sign (true means include, false means exclude).
/// @return The n-based digits.
constexpr int GetDigits(std::signed_integral auto m, int base, bool includeSign = false) {
    if (base == 0) [[unlikely]] { return 0; }
    if (base < 0) [[unlikely]] { base = -base; }
    int d = 0;
    if (m < 0) {
        if (includeSign) { ++d; }
        m = -m;
    }
    do {
        m /= base;
        ++d;
    } while (m > 0);
    return d;
}

/// @brief Get n-based digits of an integer.
/// @tparam Base The base.
/// @param m The integer.
/// @param includeSign Set whether the digits in return includes "-" sign (true means include, false means exclude).
/// @return The n-based digits.
template<int Base>
constexpr auto GetDigits(std::signed_integral auto m, bool includeSign = false) {
    return GetDigits(m, Base, includeSign);
}

/// @brief Get n-based digits of an integer.
/// @param m The integer.
/// @param base The base.
/// @return The n-based digits.
constexpr int GetDigits(std::unsigned_integral auto m, int base) {
    if (base == 0) [[unlikely]] { return 0; }
    if (base < 0) [[unlikely]] { base = -base; }
    int d = 0;
    do {
        m /= base;
        ++d;
    } while (m > 0);
    return d;
}

/// @brief Get n-based digits of an integer.
/// @tparam Base The base.
/// @param m The integer.
/// @return The n-based digits.
template<int Base>
constexpr auto GetDigits(std::unsigned_integral auto m) {
    return GetDigits(m, Base);
}

// Examples:
static_assert(GetDigits(0, 2) == 1);
static_assert(GetDigits(0u, 2) == 1);
static_assert(GetDigits(0b10100101000, 2) == 11);
static_assert(GetDigits(0b10100101000u, 2) == 11);
static_assert(GetDigits(-0b10100101000, 2) == 11);
static_assert(GetDigits(-0b10100101000, 2, true) == 12);
static_assert(GetDigits<2>(0) == 1);
static_assert(GetDigits<2>(0u) == 1);
static_assert(GetDigits<2>(0b10100101000) == 11);
static_assert(GetDigits<2>(0b10100101000u) == 11);
static_assert(GetDigits<2>(-0b10100101000) == 11);
static_assert(GetDigits<2>(-0b10100101000, true) == 12);
static_assert(GetDigits(0, 8) == 1);
static_assert(GetDigits(0u, 8) == 1);
static_assert(GetDigits(0114514, 8) == 6);
static_assert(GetDigits(0114514u, 8) == 6);
static_assert(GetDigits(-0114514, 8) == 6);
static_assert(GetDigits(-0114514, 8, true) == 7);
static_assert(GetDigits<8>(0) == 1);
static_assert(GetDigits<8>(0u) == 1);
static_assert(GetDigits<8>(0114514) == 6);
static_assert(GetDigits<8>(0114514u) == 6);
static_assert(GetDigits<8>(-0114514) == 6);
static_assert(GetDigits<8>(-0114514, true) == 7);
static_assert(GetDigits(0, 10) == 1);
static_assert(GetDigits(0u, 10) == 1);
static_assert(GetDigits(1, 10) == 1);
static_assert(GetDigits(1u, 10) == 1);
static_assert(GetDigits(99, 10) == 2);
static_assert(GetDigits(99u, 10) == 2);
static_assert(GetDigits(100, 10) == 3);
static_assert(GetDigits(100u, 10) == 3);
static_assert(GetDigits(114514, 10) == 6);
static_assert(GetDigits(114514u, 10) == 6);
static_assert(GetDigits(1919810, 10) == 7);
static_assert(GetDigits(1919810u, 10) == 7);
static_assert(GetDigits(-114514, 10) == 6);
static_assert(GetDigits(-114514, 10, true) == 7);
static_assert(GetDigits<10>(114514) == 6);
static_assert(GetDigits<10>(114514u) == 6);
static_assert(GetDigits<10>(-114514) == 6);
static_assert(GetDigits<10>(-114514, true) == 7);
static_assert(GetDigits(0, 16) == 1);
static_assert(GetDigits(0u, 16) == 1);
static_assert(GetDigits(0x114514, 16) == 6);
static_assert(GetDigits(0x114514u, 16) == 6);
static_assert(GetDigits(-0x114514, 16) == 6);
static_assert(GetDigits(-0x114514, 16, true) == 7);
static_assert(GetDigits<16>(0) == 1);
static_assert(GetDigits<16>(0u) == 1);
static_assert(GetDigits<16>(0x114514) == 6);
static_assert(GetDigits<16>(0x114514u) == 6);
static_assert(GetDigits<16>(-0x114514) == 6);
static_assert(GetDigits<16>(-0x114514, true) == 7);

} // namespace MACE::Utility::Math
