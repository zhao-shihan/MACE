#pragma once

#include <compare>
#include <concepts>
#include <cstring>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>

namespace MACE::Utility {

/// @brief A fixed-capacity string on the stack.
/// As an option for some known-size cases or aggressive SSO (Short String
/// Optimization). Acts like C-style string, but convenient constructors and
/// operators are introduced.
/// @attention The size of incoming string is never checked. Use with caution.
template<std::size_t AMaxSize> // clang-format off
    requires (AMaxSize >= 1)
class FixedString final { // clang-format on
public:
    using Pointer = char*;
    using ConstPointer = const char*;
    using Iterator = Pointer;
    using ConstIterator = ConstPointer;
    using Reference = char&;
    using ConstReference = const char&;
    using pointer = Pointer;
    using const_pointer = ConstPointer;
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using reference = Reference;
    using const_reference = ConstReference;

public:
    FixedString() noexcept;
    FixedString(char ch) noexcept;
    FixedString(ConstPointer str) noexcept;
    FixedString(const FixedString& str) noexcept = default;
    FixedString(FixedString&& str) noexcept = default;
    FixedString(const std::derived_from<std::string> auto& str) noexcept;
    explicit FixedString(const auto& str) noexcept
        requires(std::convertible_to<decltype(str), std::string_view> and not std::convertible_to<decltype(str), ConstPointer>);
    FixedString(std::nullptr_t) noexcept = delete;

    operator std::string() & noexcept { return fString; }
    operator std::string_view() & noexcept { return fString; }

    FixedString& operator=(char ch) & noexcept;
    FixedString& operator=(ConstPointer rhs) & noexcept;
    FixedString& operator=(const FixedString& rhs) & noexcept = default;
    FixedString& operator=(FixedString&& rhs) & noexcept = default;
    FixedString& operator=(const std::derived_from<std::string> auto& rhs) & noexcept;
    FixedString& operator=(const auto& rhs) & noexcept
        requires(std::convertible_to<decltype(rhs), std::string_view> and not std::convertible_to<decltype(rhs), ConstPointer>);
    FixedString& operator=(std::nullptr_t) & noexcept = delete;

    std::size_t Length() const noexcept { return std::strlen(fString); }
    std::size_t Size() const noexcept { return Length(); }
    bool Empty() const noexcept { return front() == '\0'; }
    std::size_t length() const noexcept { return Length(); }
    std::size_t size() const noexcept { return Size(); }
    bool empty() const noexcept { return Empty(); }

    Iterator Begin() noexcept { return fString; }
    Iterator End() noexcept { return Begin() + Length(); }
    ConstIterator Begin() const noexcept { return fString; }
    ConstIterator End() const noexcept { return Begin() + Length(); }
    ConstIterator CBegin() const noexcept { return Begin(); }
    ConstIterator CEnd() const noexcept { return End(); }
    iterator begin() noexcept { return Begin(); }
    iterator end() noexcept { return End(); }
    const_iterator begin() const noexcept { return Begin(); }
    const_iterator end() const noexcept { return End(); }
    const_iterator cbegin() const noexcept { return CBegin(); }
    const_iterator cend() const noexcept { return CEnd(); }

    Reference Front() noexcept { return *Begin(); }
    Reference Back() noexcept { return *(End() - 1); }
    Pointer Data() noexcept { return fString; }
    ConstReference Front() const noexcept { return *Begin(); }
    ConstReference Back() const noexcept { return *(End() - 1); }
    ConstPointer Data() const noexcept { return fString; }
    ConstPointer CString() const noexcept { return Data(); }
    reference front() noexcept { return Front(); }
    reference back() noexcept { return Back(); }
    pointer data() noexcept { return Data(); }
    const_reference front() const noexcept { return Front(); }
    const_reference back() const noexcept { return Back(); }
    const_pointer data() const noexcept { return Data(); }
    const_pointer c_str() const noexcept { return CString(); }

    FixedString& Append(char ch) noexcept;
    FixedString& Append(ConstPointer str) noexcept;
    FixedString& Append(const FixedString& str) noexcept { return Append(str.fString); }
    FixedString& Append(const std::derived_from<std::string> auto& str) noexcept;
    FixedString& Append(const auto& str) noexcept
        requires(std::convertible_to<decltype(str), std::string_view> and not std::convertible_to<decltype(str), ConstPointer>);
    FixedString& append(char ch) noexcept { return Append(ch); }
    FixedString& append(const_pointer str) noexcept { return Append(str); }
    FixedString& append(const FixedString& str) noexcept { return Append(str); }
    FixedString& append(const std::derived_from<std::string> auto& str) noexcept { return Append(str); }
    FixedString& append(const auto& str) noexcept
        requires(std::convertible_to<decltype(str), std::string_view> and not std::convertible_to<decltype(str), ConstPointer>) { return Append(str); }

    FixedString& operator+=(char rhs) noexcept { return Append(rhs); }
    FixedString& operator+=(ConstPointer rhs) noexcept { return Append(rhs); }
    FixedString& operator+=(const FixedString& rhs) noexcept { return Append(rhs); }
    FixedString& operator+=(const std::derived_from<std::string> auto& rhs) noexcept { return Append(rhs); }
    FixedString& operator+=(const auto& rhs) noexcept
        requires(std::convertible_to<decltype(rhs), std::string_view> and not std::convertible_to<decltype(rhs), ConstPointer>) { return Append(rhs); }

    bool operator==(ConstPointer rhs) const noexcept { return std::strncmp(fString, rhs, AMaxSize) == 0; }
    bool operator==(const FixedString& rhs) const noexcept { return operator==(rhs.fString); }
    bool operator==(const std::derived_from<std::string> auto& rhs) const noexcept { return operator==(rhs.std::string::c_str()); }
    bool operator==(const auto& rhs) const noexcept
        requires(std::convertible_to<decltype(rhs), std::string_view> and not std::convertible_to<decltype(rhs), ConstPointer>);
    std::strong_ordering operator<=>(ConstPointer rhs) const noexcept;
    std::strong_ordering operator<=>(const FixedString& rhs) const noexcept { return operator<=>(rhs.fString); }
    std::strong_ordering operator<=>(const std::derived_from<std::string> auto& rhs) const noexcept { return operator<=>(rhs.std::string::c_str()); }
    std::strong_ordering operator<=>(const auto& rhs) const noexcept
        requires(std::convertible_to<decltype(rhs), std::string_view> and not std::convertible_to<decltype(rhs), ConstPointer>);

    static constexpr std::size_t Capacity() noexcept { return AMaxSize + 1; }
    static constexpr std::size_t MaxSize() noexcept { return AMaxSize; }
    static constexpr std::size_t capacity() noexcept { return Capacity(); }
    static constexpr std::size_t max_size() noexcept { return MaxSize(); }

    friend FixedString operator+(const FixedString& lhs, const FixedString& rhs) noexcept { return FixedString(lhs) += rhs; }
    friend FixedString operator+(const FixedString& lhs, ConstPointer rhs) noexcept { return FixedString(lhs) += rhs; }
    friend FixedString operator+(const FixedString& lhs, char rhs) noexcept { return FixedString(lhs) += rhs; }
    friend FixedString operator+(ConstPointer lhs, const FixedString& rhs) noexcept { return FixedString(lhs) += rhs; }
    friend FixedString operator+(char lhs, const FixedString& rhs) noexcept { return FixedString(lhs) += rhs; }

private:
    char fString[AMaxSize + 1];
};

/// @brief A short string (15 characters) on the stack. Size 16 bytes.
using ShortString = FixedString<15>;

} // namespace MACE::Utility

#include "MACE/Utility/FixedString.inl"
