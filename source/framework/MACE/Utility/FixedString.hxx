#pragma once

#include "gsl/gsl"

#include <algorithm>
#include <compare>
#include <concepts>
#include <cstring>
#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace MACE::Utility {

/// @brief A fixed-capacity string on the stack.
/// As an option for some known-size cases or aggressive SSO (Short String
/// Optimization). Acts like C-style string, but convenient constructors and
/// operators are introduced.
/// @attention The size of incoming string is never checked. Use with caution.
template<std::size_t AMaxSize>
    requires((AMaxSize + 1) % alignof(void*) == 0)
class FixedString final {
public:
    using Pointer = char*;
    using ConstPointer = const char*;
    using Iterator = Pointer;
    using ConstIterator = ConstPointer;
    using Reference = char&;
    using ConstReference = const char&;
    using DataType = char[AMaxSize + 1];
    using pointer = Pointer;
    using const_pointer = ConstPointer;
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using reference = Reference;
    using const_reference = ConstReference;
    using data_type = DataType;

public:
    FixedString() noexcept;
    FixedString(const FixedString& str) noexcept = default;
    FixedString(FixedString&& str) noexcept = default;
    template<std::size_t N>
    FixedString(const char (&str)[N]) noexcept;
    template<std::size_t N>
        requires(N != AMaxSize)
    FixedString(const FixedString<N>& str) noexcept;
    FixedString(std::string_view str) noexcept;
    FixedString(auto&& str) noexcept
        requires(std::same_as<std::remove_cvref_t<decltype(str)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(str)>, gsl::czstring> or
                 (std::convertible_to<decltype(str), gsl::czstring> and
                  not std::convertible_to<decltype(str), std::string_view>));
    FixedString(auto&& str) noexcept
        requires(std::convertible_to<decltype(str), std::string> and
                 not std::convertible_to<decltype(str), std::string_view> and
                 not std::convertible_to<decltype(str), gsl::czstring>);
    FixedString(std::nullptr_t) noexcept = delete;

    operator std::string_view() const& noexcept { return CString(); }
    operator std::string() const& noexcept { return CString(); }

    FixedString& operator=(const FixedString& rhs) & noexcept = default;
    FixedString& operator=(FixedString&& rhs) & noexcept = default;
    template<std::size_t N>
    FixedString& operator=(const char (&rhs)[N]) noexcept;
    template<std::size_t N>
        requires(N != AMaxSize)
    FixedString& operator=(const FixedString<N>& rhs) noexcept { return *this = rhs.Data(); }
    FixedString& operator=(std::string_view rhs) & noexcept;
    FixedString& operator=(auto&& rhs) & noexcept
        requires(std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(rhs), gsl::czstring> and
                  not std::convertible_to<decltype(rhs), std::string_view>));
    FixedString& operator=(auto&& rhs) & noexcept
        requires(std::convertible_to<decltype(rhs), std::string> and
                 not std::convertible_to<decltype(rhs), std::string_view> and
                 not std::convertible_to<decltype(rhs), gsl::czstring>);
    FixedString& operator=(std::nullptr_t) noexcept = delete;

    std::size_t Length() const noexcept { return std::strlen(fData); }
    std::size_t Size() const noexcept { return Length(); }
    bool Empty() const noexcept { return front() == '\0'; }
    std::size_t length() const noexcept { return Length(); }
    std::size_t size() const noexcept { return Size(); }
    bool empty() const noexcept { return Empty(); }

    Iterator Begin() noexcept { return fData; }
    Iterator End() noexcept { return Begin() + Length(); }
    ConstIterator Begin() const noexcept { return fData; }
    ConstIterator End() const noexcept { return Begin() + Length(); }
    ConstIterator ConstBegin() const noexcept { return Begin(); }
    ConstIterator ConstEnd() const noexcept { return End(); }
    iterator begin() noexcept { return Begin(); }
    iterator end() noexcept { return End(); }
    const_iterator begin() const noexcept { return Begin(); }
    const_iterator end() const noexcept { return End(); }
    const_iterator cbegin() const noexcept { return ConstBegin(); }
    const_iterator cend() const noexcept { return ConstEnd(); }

    Reference Front() noexcept { return *Begin(); }
    Reference Back() noexcept { return *(End() - 1); }
    DataType& Data() noexcept { return fData; }
    ConstReference Front() const noexcept { return *Begin(); }
    ConstReference Back() const noexcept { return *(End() - 1); }
    const DataType& Data() const noexcept { return fData; }
    ConstPointer CString() const noexcept { return fData; }
    reference front() noexcept { return Front(); }
    reference back() noexcept { return Back(); }
    data_type& data() noexcept { return Data(); }
    const_reference front() const noexcept { return Front(); }
    const_reference back() const noexcept { return Back(); }
    const data_type& data() const noexcept { return Data(); }
    const_pointer c_str() const noexcept { return CString(); }

    template<std::size_t N>
    FixedString& Append(const char (&str)[N]) noexcept;
    template<std::size_t N>
    FixedString& Append(const FixedString<N>& str) noexcept { return Append(str.Data()); }
    FixedString& Append(std::string_view str) noexcept;
    FixedString& Append(auto&& str) noexcept
        requires(std::same_as<std::remove_cvref_t<decltype(str)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(str)>, gsl::czstring> or
                 (std::convertible_to<decltype(str), gsl::czstring> and
                  not std::convertible_to<decltype(str), std::string_view>));
    FixedString& Append(auto&& str) noexcept
        requires(std::convertible_to<decltype(str), std::string> and
                 not std::convertible_to<decltype(str), std::string_view> and
                 not std::convertible_to<decltype(str), gsl::czstring>);
    FixedString& Append(std::nullptr_t) noexcept = delete;
    FixedString& append(auto&& str) noexcept
        requires(requires(FixedString self) { self.Append(std::forward<decltype(str)>(str)); })
    { return Append(std::forward<decltype(str)>(str)); }

    FixedString& operator+=(auto&& rhs) noexcept
        requires(requires(FixedString self) { self.Append(std::forward<decltype(rhs)>(rhs)); })
    { return Append(std::forward<decltype(rhs)>(rhs)); }

    template<std::size_t N>
    bool operator==(const char (&rhs)[N]) const noexcept { return std::strncmp(fData, rhs, std::min(N, AMaxSize + 1)) == 0; }
    template<std::size_t N>
    bool operator==(const FixedString<N>& rhs) const noexcept { return *this == rhs.Data(); }
    bool operator==(std::string_view rhs) const noexcept { return std::string_view(*this) == rhs; }
    bool operator==(auto&& rhs) const noexcept
        requires(std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(rhs), gsl::czstring> and
                  not std::convertible_to<decltype(rhs), std::string_view>))
    { return std::strncmp(fData, std::forward<decltype(rhs)>(rhs), AMaxSize + 1) == 0; }
    bool operator==(auto&& rhs) const noexcept
        requires(std::convertible_to<decltype(rhs), std::string> and
                 not std::convertible_to<decltype(rhs), std::string_view> and
                 not std::convertible_to<decltype(rhs), gsl::czstring>)
    { return *this == std::string(std::forward<decltype(rhs)>(rhs)).c_str(); }
    bool operator==(std::nullptr_t) const noexcept = delete;

    template<std::size_t N>
    std::strong_ordering operator<=>(const char (&rhs)[N]) const noexcept;
    template<std::size_t N>
    std::strong_ordering operator<=>(const FixedString<N>& rhs) const noexcept { return *this <=> rhs.Data(); }
    std::strong_ordering operator<=>(std::string_view rhs) const noexcept { return std::string_view(*this) <=> rhs; }
    std::strong_ordering operator<=>(auto&& rhs) const noexcept
        requires(std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(rhs), gsl::czstring> and
                  not std::convertible_to<decltype(rhs), std::string_view>));
    std::strong_ordering operator<=>(auto&& rhs) const noexcept
        requires(std::convertible_to<decltype(rhs), std::string> and
                 not std::convertible_to<decltype(rhs), std::string_view> and
                 not std::convertible_to<decltype(rhs), gsl::czstring>)
    { return *this <=> std::string(std::forward<decltype(rhs)>(rhs)).c_str(); }
    std::strong_ordering operator<=>(std::nullptr_t) const noexcept = delete;

    static constexpr std::size_t Capacity() noexcept { return AMaxSize; }
    static constexpr std::size_t MaxSize() noexcept { return AMaxSize; }
    static constexpr std::size_t capacity() noexcept { return Capacity(); }
    static constexpr std::size_t max_size() noexcept { return MaxSize(); }

    friend FixedString operator+(FixedString lhs, const FixedString& rhs) noexcept { return lhs += rhs; }
    friend FixedString operator+(FixedString lhs, auto&& rhs) noexcept
        requires(requires { lhs += std::forward<decltype(rhs)>(rhs); })
    { return lhs += std::forward<decltype(rhs)>(rhs); }
    friend FixedString operator+(auto&& lhs, const FixedString& rhs) noexcept
        requires(requires { FixedString(std::forward<decltype(lhs)>(lhs)) += rhs; })
    { return FixedString(std::forward<decltype(lhs)>(lhs)) += rhs; }

    /* template<std::size_t N>
    FixedString& operator+=(const char (&rhs)[N]) noexcept { return Append(rhs); }
    template<std::size_t N>
    FixedString& operator+=(const FixedString<N>& rhs) noexcept { return Append(rhs); }
    FixedString& operator+=(std::string_view rhs) noexcept { return Append(rhs); }
    FixedString& operator+=(auto&& rhs) noexcept
        requires(std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(rhs), gsl::czstring> and
                  not std::convertible_to<decltype(rhs), std::string_view>)) { return Append(std::forward<decltype(rhs)>(rhs)); }
    FixedString& operator+=(auto&& rhs) noexcept
        requires(std::convertible_to<decltype(rhs), std::string> and
                 not std::convertible_to<decltype(rhs), std::string_view> and
                 not std::convertible_to<decltype(rhs), gsl::czstring>) { return Append(std::forward<decltype(rhs)>(rhs)); }
    FixedString& operator+=(std::nullptr_t) noexcept = delete; */
    /* template<std::size_t N>
    friend FixedString operator+(FixedString lhs, const char (&rhs)[N]) noexcept { return lhs += rhs; }
    template<std::size_t N>
    friend FixedString operator+(FixedString lhs, const FixedString<N>& rhs) noexcept { return lhs += rhs; }
    friend FixedString operator+(FixedString lhs, std::string_view rhs) noexcept { return lhs += rhs; }
    friend FixedString operator+(FixedString lhs, auto&& rhs) noexcept
        requires(std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(rhs), gsl::czstring> and
                  not std::convertible_to<decltype(rhs), std::string_view>)) { return lhs += std::forward<decltype(rhs)>(rhs); }
    friend FixedString operator+(FixedString lhs, auto&& rhs) noexcept
        requires(std::convertible_to<decltype(rhs), std::string> and
                 not std::convertible_to<decltype(rhs), std::string_view> and
                 not std::convertible_to<decltype(rhs), gsl::czstring>) { return lhs += std::forward<decltype(rhs)>(rhs); }
    template<std::size_t N>
    friend FixedString operator+(const char (&lhs)[N], const FixedString& rhs) noexcept { return FixedString(lhs) += rhs; }
    friend FixedString operator+(std::string_view lhs, const FixedString& rhs) noexcept { return FixedString(lhs) += rhs; }
    friend FixedString operator+(auto&& lhs, const FixedString& rhs) noexcept
        requires(std::same_as<std::remove_cvref_t<decltype(lhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(lhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(lhs), gsl::czstring> and
                  not std::convertible_to<decltype(lhs), std::string_view>)) { return FixedString(lhs) += rhs; }
    friend FixedString operator+(auto&& lhs, const FixedString& rhs) noexcept
        requires(std::convertible_to<decltype(lhs), std::string> and
                 not std::convertible_to<decltype(lhs), std::string_view> and
                 not std::convertible_to<decltype(lhs), gsl::czstring>) { return FixedString(lhs) += rhs; } */

private:
    DataType fData;
};

/// @brief A short string (15 characters) on the stack. Size 16 bytes.
using ShortString = FixedString<15>;

} // namespace MACE::Utility

#include "MACE/Utility/FixedString.inl"
