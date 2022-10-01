#pragma once

#include <concepts>

namespace MACE::Utility::Math {

/// @brief Get 10-based digits of an integer.
/// @param n The integer.
/// @param includeSign Set whether the digits in return includes "-" sign (true means include, false means exclude).
/// @return The 10-based digits.
constexpr int GetDigits10(std::integral auto n, bool includeSign = false) {
    int d = 0;
    if constexpr (std::signed_integral<decltype(n)>) {
        if (n < 0) {
            if (includeSign) { ++d; }
            n = -n;
        }
    }
    do {
        n /= 10;
        ++d;
    } while (n > 0);
    return d;
}

/// @brief Get 10-based digits of an integer.
/// @tparam N The integer.
/// @tparam IncludeSign Set whether the digits in return includes "-" sign (true means include, false means exclude).
/// @return The 10-based digits.
template<std::integral auto N, bool IncludeSign = false>
constexpr auto GetDigits10() {
    return GetDigits10(N, IncludeSign);
}

// Examples:
static_assert(GetDigits10(0) == 1);
static_assert(GetDigits10(1) == 1);
static_assert(GetDigits10(99) == 2);
static_assert(GetDigits10(100) == 3);
static_assert(GetDigits10(114514) == 6);
static_assert(GetDigits10(1919810) == 7);
static_assert(GetDigits10(-114514) == 6);
static_assert(GetDigits10(-114514, true) == 7);
static_assert(GetDigits10<-114514>() == 6);
static_assert(GetDigits10<-114514, true>() == 7);

} // namespace MACE::Utility::Math
