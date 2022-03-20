#pragma once

#include <compare>
#include <cstring>

#include "UtilityForwardDeclaration.hxx"

/// @brief A short string (15 characters) on the stack. Size 16 bytes.
/// As an option for some known-size cases or aggressive SSO (Short String Optimization). (The latter is not recommended, just use TString.)
/// Compatible with C-style string, but more convenient copy constructor and operator= are introduced.
/// @warning The size of incoming string is never checked. Please use with EXTREME caution.
class MACE::ShortString final {
public:
    constexpr operator char*() noexcept { return fString; }
    constexpr operator const char*() const noexcept { return fString; }

    inline constexpr ShortString() noexcept;
    inline constexpr ShortString(const ShortString& rhs) noexcept;
    constexpr ShortString(ShortString&& rhs) noexcept = default;
    constexpr ShortString(const char* rhs) noexcept { std::strcpy(fString, rhs); }
    inline constexpr ShortString(char ch) noexcept;

    constexpr ~ShortString() noexcept = default;

    constexpr ShortString& operator=(const ShortString& rhs) noexcept { return operator=(rhs.fString); }
    constexpr ShortString& operator=(ShortString&& rhs) noexcept = default;
    inline constexpr ShortString& operator=(const char* rhs) noexcept;
    inline constexpr ShortString& operator=(char rhs) noexcept;

    constexpr ShortString& operator+=(const ShortString& rhs) noexcept { return operator+=(rhs.fString); }
    inline constexpr ShortString& operator+=(const char* rhs) noexcept;
    inline constexpr ShortString& operator+=(char rhs) noexcept;

    constexpr bool operator==(const char* rhs) const noexcept { return std::strcmp(fString, rhs) == 0; }
    constexpr bool operator!=(const char* rhs) const noexcept { return std::strcmp(fString, rhs) != 0; }
    constexpr bool operator<(const char* rhs) const noexcept { return std::strcmp(fString, rhs) < 0; }
    constexpr bool operator<=(const char* rhs) const noexcept { return std::strcmp(fString, rhs) <= 0; }
    constexpr bool operator>(const char* rhs) const noexcept { return std::strcmp(fString, rhs) > 0; }
    constexpr bool operator>=(const char* rhs) const noexcept { return std::strcmp(fString, rhs) >= 0; }
    inline constexpr std::weak_ordering operator<=>(const char* rhs) const noexcept;

private:
    char fString[16];
};

namespace MACE {

constexpr ShortString operator+(ShortString lhs, const ShortString& rhs) { return lhs += rhs; }
constexpr ShortString operator+(ShortString lhs, const char* rhs) { return lhs += rhs; }
constexpr ShortString operator+(const char* lhs, const ShortString& rhs) { return ShortString(lhs) += rhs; }
constexpr ShortString operator+(ShortString lhs, char rhs) { return lhs += rhs; }
constexpr ShortString operator+(char lhs, const ShortString& rhs) { return ShortString(lhs) += rhs; }

}

#include "ShortString.ixx"
