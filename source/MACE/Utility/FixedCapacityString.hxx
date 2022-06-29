#pragma once

#include <compare>
#include <cstring>

namespace MACE::Utility {

/// @brief A fixed-capacity string on the stack.
/// As an option for some known-size cases or aggressive SSO (Short String Optimization).
/// Compatible with C-style string, but more convenient copy constructor and operators are introduced.
/// @attention The size of incoming string is never checked. Use with caution.
template<size_t CapacityV> // clang-format off
    requires (CapacityV >= 2)
class FixedCapacityString final { // clang-format on
public:
    operator char*() & noexcept { return fString; }
    operator const char*() const& noexcept { return fString; }

    FixedCapacityString() noexcept;
    FixedCapacityString(char ch) noexcept;
    FixedCapacityString(const char* rhs) noexcept;
    FixedCapacityString(const FixedCapacityString& rhs) noexcept = default;
    FixedCapacityString(FixedCapacityString&& rhs) noexcept = default;

    ~FixedCapacityString() noexcept = default;

    FixedCapacityString& operator=(char rhs) & noexcept;
    FixedCapacityString& operator=(const char* rhs) & noexcept;
    FixedCapacityString& operator=(const FixedCapacityString& rhs) & noexcept = default;
    FixedCapacityString& operator=(FixedCapacityString&& rhs) & noexcept = default;

    size_t length() const noexcept { return std::strlen(fString); }
    size_t size() const noexcept { return length(); }
    bool empty() const noexcept { return front() == '\0'; }

    char* begin() noexcept { return fString; }
    char* end() noexcept { return begin() + length(); }
    const char* begin() const noexcept { return fString; }
    const char* end() const noexcept { return begin() + length(); }
    const char* cbegin() const noexcept { return begin(); }
    const char* cend() const noexcept { return end(); }
    // std::reverse_iterator<char*> rbegin() noexcept { return end(); }
    // std::reverse_iterator<char*> rend() noexcept { return begin(); }
    // std::reverse_iterator<const char*> crbegin() noexcept { return cend(); }
    // std::reverse_iterator<const char*> crend() noexcept { return cbegin(); }

    char& front() noexcept { return *begin(); }
    char& back() noexcept { return *(end() - 1); }
    char* data() noexcept { return fString; }
    const char& front() const noexcept { return *begin(); }
    const char& back() const noexcept { return *(end() - 1); }
    const char* data() const noexcept { return fString; }
    const char* c_str() const noexcept { return fString; }

    FixedCapacityString& operator+=(char rhs) noexcept;
    FixedCapacityString& operator+=(const char* rhs) noexcept;
    FixedCapacityString& operator+=(const FixedCapacityString& rhs) noexcept { return operator+=(rhs.fString); }

    bool operator==(const char* rhs) const noexcept { return std::strncmp(fString, rhs, max_size()) == 0; }
    bool operator!=(const char* rhs) const noexcept { return std::strncmp(fString, rhs, max_size()) != 0; }
    bool operator<(const char* rhs) const noexcept { return std::strncmp(fString, rhs, max_size()) < 0; }
    bool operator<=(const char* rhs) const noexcept { return std::strncmp(fString, rhs, max_size()) <= 0; }
    bool operator>(const char* rhs) const noexcept { return std::strncmp(fString, rhs, max_size()) > 0; }
    bool operator>=(const char* rhs) const noexcept { return std::strncmp(fString, rhs, max_size()) >= 0; }
    std::weak_ordering operator<=>(const char* rhs) const noexcept;

    static constexpr size_t capacity() noexcept { return CapacityV; }
    static constexpr size_t max_size() noexcept { return CapacityV - 1; }

    friend FixedCapacityString operator+(const FixedCapacityString& lhs, const FixedCapacityString& rhs) noexcept { return FixedCapacityString(lhs) += rhs; }
    friend FixedCapacityString operator+(const FixedCapacityString& lhs, const char* rhs) noexcept { return FixedCapacityString(lhs) += rhs; }
    friend FixedCapacityString operator+(const FixedCapacityString& lhs, char rhs) noexcept { return FixedCapacityString(lhs) += rhs; }
    friend FixedCapacityString operator+(const char* lhs, const FixedCapacityString& rhs) noexcept { return FixedCapacityString(lhs) += rhs; }
    friend FixedCapacityString operator+(char lhs, const FixedCapacityString& rhs) noexcept { return FixedCapacityString(lhs) += rhs; }

private:
    char fString[CapacityV];
};

/// @brief A short string (15 characters) on the stack. Size 16 bytes.
using ShortString = FixedCapacityString<16>;

} // namespace MACE::Utility

#include "MACE/Utility/FixedCapacityString.inl"
