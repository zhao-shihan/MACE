#pragma once

#include <compare>
#include <cstring>
#include <sstream>

namespace MACE::Utility {

/// @brief A short string (15 characters) on the stack. Size 16 bytes.
/// As an option for some known-size cases or aggressive SSO (Short String Optimization). (The latter is not recommended, just use TString.)
/// Compatible with C-style string, but more convenient copy constructor and operators are introduced.
/// @warning The size of incoming string is never checked. Please use with EXTREME caution.
class ShortString final {
public:
    constexpr operator char*() noexcept { return fString; }
    constexpr operator const char*() const noexcept { return fString; }

    constexpr ShortString() noexcept;
    constexpr ShortString(const ShortString& rhs) noexcept;
    constexpr ShortString(ShortString&& rhs) noexcept = default;
    constexpr ShortString(const char* rhs) noexcept { std::strcpy(fString, rhs); }
    constexpr ShortString(char ch) noexcept;

    constexpr ~ShortString() noexcept = default;

    constexpr ShortString& operator=(const ShortString& rhs) noexcept { return operator=(rhs.fString); }
    constexpr ShortString& operator=(ShortString&& rhs) noexcept = default;
    constexpr ShortString& operator=(const char* rhs) noexcept;
    constexpr ShortString& operator=(char rhs) noexcept;

    constexpr char& front() noexcept { return *begin(); }
    constexpr char& back() noexcept { return *(end() - 1); }
    constexpr char* data() noexcept { return fString; }
    constexpr const char& front() const noexcept { return *cbegin(); }
    constexpr const char& back() const noexcept { return *(cend() - 1); }
    constexpr const char* data() const noexcept { return fString; }
    constexpr const char* c_str() const noexcept { return data(); }

    constexpr char* begin() noexcept { return fString; }
    constexpr char* end() noexcept { return fString + length(); }
    constexpr const char* cbegin() const noexcept { return fString; }
    constexpr const char* cend() const noexcept { return fString + length(); }
    // constexpr std::reverse_iterator<char*> rbegin() noexcept { return end(); }
    // constexpr std::reverse_iterator<char*> rend() noexcept { return begin(); }
    // constexpr std::reverse_iterator<const char*> crbegin() noexcept { return cend(); }
    // constexpr std::reverse_iterator<const char*> crend() noexcept { return cbegin(); }

    constexpr size_t length() const noexcept { return std::strlen(fString); }
    constexpr size_t size() const noexcept { return length(); }
    constexpr size_t capacity() const noexcept { return 16; }
    constexpr size_t max_size() const noexcept { return capacity() - 1; }
    constexpr bool empty() const noexcept { return front() == '\0'; }

    constexpr ShortString& operator+=(const ShortString& rhs) noexcept { return operator+=(rhs.fString); }
    constexpr ShortString& operator+=(const char* rhs) noexcept;
    constexpr ShortString& operator+=(char rhs) noexcept;
    template<typename T>
    constexpr ShortString& operator+=(T rhs) noexcept requires(std::is_arithmetic_v<T> and not std::same_as<T, char>);

    constexpr bool operator==(const char* rhs) const noexcept { return std::strcmp(fString, rhs) == 0; }
    constexpr bool operator!=(const char* rhs) const noexcept { return std::strcmp(fString, rhs) != 0; }
    constexpr bool operator<(const char* rhs) const noexcept { return std::strcmp(fString, rhs) < 0; }
    constexpr bool operator<=(const char* rhs) const noexcept { return std::strcmp(fString, rhs) <= 0; }
    constexpr bool operator>(const char* rhs) const noexcept { return std::strcmp(fString, rhs) > 0; }
    constexpr bool operator>=(const char* rhs) const noexcept { return std::strcmp(fString, rhs) >= 0; }
    constexpr std::weak_ordering operator<=>(const char* rhs) const noexcept;

    constexpr friend ShortString operator+(ShortString lhs, const ShortString& rhs) { return lhs += rhs; }
    constexpr friend ShortString operator+(ShortString lhs, const char* rhs) { return lhs += rhs; }
    constexpr friend ShortString operator+(const char* lhs, const ShortString& rhs) { return ShortString(lhs) += rhs; }
    constexpr friend ShortString operator+(ShortString lhs, char rhs) { return lhs += rhs; }
    constexpr friend ShortString operator+(char lhs, const ShortString& rhs) { return ShortString(lhs) += rhs; }
    template<typename T>
    constexpr friend ShortString operator+(ShortString lhs, T rhs) noexcept requires(std::is_arithmetic_v<T> and not std::same_as<T, char>) { return lhs += rhs; }
    template<typename T>
    constexpr friend ShortString operator+(T lhs, ShortString rhs) noexcept requires(std::is_arithmetic_v<T> and not std::same_as<T, char>);

private:
    char fString[16];

    inline static std::stringstream fgSS = std::stringstream();
};

} // namespace MACE::Utility

#include "Utility/ShortString.ixx"
