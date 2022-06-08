#pragma once

#include <compare>
#include <cstring>
#include <sstream>

namespace MACE::Utility {

/// @brief A short string (15 characters) on the stack. Size 16 bytes.
/// As an option for some known-size cases or aggressive SSO (Short String Optimization).
/// Compatible with C-style string, but more convenient copy constructor and operators are introduced.
/// @warning The size of incoming string is never checked. Use with caution.
class ShortString final {
public:
    operator char*() noexcept { return fString; }
    operator const char*() const noexcept { return fString; }

    ShortString() noexcept;
    ShortString(const ShortString& rhs) noexcept;
    ShortString(ShortString&& rhs) noexcept = default;
    ShortString(const char* rhs) noexcept { std::strncpy(fString, rhs, fgkMaxLength); }
    ShortString(char ch) noexcept;

    ~ShortString() noexcept = default;

    ShortString& operator=(const ShortString& rhs) noexcept { return operator=(rhs.fString); }
    ShortString& operator=(ShortString&& rhs) noexcept = default;
    ShortString& operator=(const char* rhs) noexcept;
    ShortString& operator=(char rhs) noexcept;

    char& front() noexcept { return *begin(); }
    char& back() noexcept { return *(end() - 1); }
    char* data() noexcept { return fString; }
    const char& front() const noexcept { return *cbegin(); }
    const char& back() const noexcept { return *(cend() - 1); }
    const char* data() const noexcept { return fString; }
    const char* c_str() const noexcept { return data(); }

    char* begin() noexcept { return fString; }
    char* end() noexcept { return fString + length(); }
    const char* cbegin() const noexcept { return fString; }
    const char* cend() const noexcept { return fString + length(); }
    // std::reverse_iterator<char*> rbegin() noexcept { return end(); }
    // std::reverse_iterator<char*> rend() noexcept { return begin(); }
    // std::reverse_iterator<const char*> crbegin() noexcept { return cend(); }
    // std::reverse_iterator<const char*> crend() noexcept { return cbegin(); }

    size_t length() const noexcept { return std::strlen(fString); }
    size_t size() const noexcept { return length(); }
    size_t capacity() const noexcept { return fgkCapacity; }
    size_t max_size() const noexcept { return fgkMaxLength; }
    bool empty() const noexcept { return front() == '\0'; }

    ShortString& operator+=(const ShortString& rhs) noexcept { return operator+=(rhs.fString); }
    ShortString& operator+=(const char* rhs) noexcept;
    ShortString& operator+=(char rhs) noexcept;

    bool operator==(const char* rhs) const noexcept { return std::strncmp(fString, rhs, fgkMaxLength) == 0; }
    bool operator!=(const char* rhs) const noexcept { return std::strncmp(fString, rhs, fgkMaxLength) != 0; }
    bool operator<(const char* rhs) const noexcept { return std::strncmp(fString, rhs, fgkMaxLength) < 0; }
    bool operator<=(const char* rhs) const noexcept { return std::strncmp(fString, rhs, fgkMaxLength) <= 0; }
    bool operator>(const char* rhs) const noexcept { return std::strncmp(fString, rhs, fgkMaxLength) > 0; }
    bool operator>=(const char* rhs) const noexcept { return std::strncmp(fString, rhs, fgkMaxLength) >= 0; }
    std::weak_ordering operator<=>(const char* rhs) const noexcept;

    friend ShortString operator+(ShortString lhs, const ShortString& rhs) noexcept { return lhs += rhs; }
    friend ShortString operator+(ShortString lhs, const char* rhs) noexcept { return lhs += rhs; }
    friend ShortString operator+(const char* lhs, const ShortString& rhs) noexcept { return ShortString(lhs) += rhs; }
    friend ShortString operator+(ShortString lhs, char rhs) noexcept { return lhs += rhs; }
    friend ShortString operator+(char lhs, const ShortString& rhs) noexcept { return ShortString(lhs) += rhs; }

private:
    static constexpr size_t fgkCapacity = 16;
    static constexpr size_t fgkMaxLength = fgkCapacity - 1;

    char fString[fgkCapacity];
};

} // namespace MACE::Utility
