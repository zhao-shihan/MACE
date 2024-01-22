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

namespace MACE::inline Utility {

/// @brief A fixed-capacity string on the stack.
/// As an option for some known-size cases or aggressive SSO (Short String
/// Optimization). Acts like C-style string, but convenient constructors and
/// operators are introduced.
/// @attention The size of incoming string is never checked. Use with caution.
template<std::size_t AMaxSize>
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
    template<std::size_t N>
    FixedString(const char (&str)[N]) noexcept;
    template<std::size_t N>
    FixedString(const FixedString<N>& str) noexcept;
    FixedString(std::string_view str) noexcept;
    FixedString(auto&& str) noexcept
        requires std::same_as<std::remove_cvref_t<decltype(str)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(str)>, gsl::czstring> or
                 (std::convertible_to<decltype(str), gsl::czstring> and
                  not std::convertible_to<decltype(str), std::string_view>);
    FixedString(auto&& str) noexcept
        requires std::convertible_to<decltype(str), std::string> and
                 (not std::convertible_to<decltype(str), std::string_view>) and
                 (not std::convertible_to<decltype(str), gsl::czstring>);
    FixedString(std::nullptr_t) noexcept = delete;

    operator std::string_view() const noexcept { return CString(); }
    operator std::string() const noexcept { return CString(); }

    template<std::size_t N>
    auto operator=(const char (&rhs)[N]) & noexcept -> FixedString&;
    template<std::size_t N>
    auto operator=(const FixedString<N>& rhs) & noexcept -> FixedString& { return *this = rhs.Data(); }
    auto operator=(std::string_view rhs) & noexcept -> FixedString&;
    auto operator=(auto&& rhs) & noexcept -> FixedString&
        requires std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(rhs), gsl::czstring> and
                  not std::convertible_to<decltype(rhs), std::string_view>);
    auto operator=(auto&& rhs) & noexcept -> FixedString&
        requires std::convertible_to<decltype(rhs), std::string> and
                 (not std::convertible_to<decltype(rhs), std::string_view>) and
                 (not std::convertible_to<decltype(rhs), gsl::czstring>);
    auto operator=(std::nullptr_t) noexcept -> FixedString& = delete;

    auto Length() const noexcept -> std::size_t { return std::strlen(fData); }
    auto Size() const noexcept -> std::size_t { return Length(); }
    auto Empty() const noexcept -> bool { return front() == '\0'; }
    auto length() const noexcept -> std::size_t { return Length(); }
    auto size() const noexcept -> std::size_t { return Size(); }
    auto empty() const noexcept -> bool { return Empty(); }

    auto Begin() noexcept -> Iterator { return fData; }
    auto End() noexcept -> Iterator { return Begin() + Length(); }
    auto begin() noexcept -> iterator { return Begin(); }
    auto end() noexcept -> iterator { return End(); }
    auto Begin() const noexcept -> ConstIterator { return fData; }
    auto End() const noexcept -> ConstIterator { return Begin() + Length(); }
    auto ConstBegin() const noexcept -> ConstIterator { return Begin(); }
    auto ConstEnd() const noexcept -> ConstIterator { return End(); }
    auto begin() const noexcept -> const_iterator { return Begin(); }
    auto end() const noexcept -> const_iterator { return End(); }
    auto cbegin() const noexcept -> const_iterator { return ConstBegin(); }
    auto cend() const noexcept -> const_iterator { return ConstEnd(); }

    auto Front() noexcept -> Reference { return *Begin(); }
    auto Back() noexcept -> Reference { return *(End() - 1); }
    auto Data() noexcept -> DataType& { return fData; }
    auto CString() noexcept -> gsl::zstring { return fData; }
    auto front() noexcept -> reference { return Front(); }
    auto back() noexcept -> reference { return Back(); }
    auto data() noexcept -> data_type& { return Data(); }
    auto c_str() noexcept -> gsl::zstring { return CString(); }
    auto Front() const noexcept -> ConstReference { return *Begin(); }
    auto Back() const noexcept -> ConstReference { return *(End() - 1); }
    auto Data() const noexcept -> const DataType& { return fData; }
    auto CString() const noexcept -> gsl::czstring { return fData; }
    auto front() const noexcept -> const_reference { return Front(); }
    auto back() const noexcept -> const_reference { return Back(); }
    auto data() const noexcept -> const data_type& { return Data(); }
    auto c_str() const noexcept -> gsl::czstring { return CString(); }

    template<std::size_t N>
    auto Append(const char (&str)[N]) noexcept -> FixedString&;
    template<std::size_t N>
    auto Append(const FixedString<N>& str) noexcept -> FixedString& { return Append(str.Data()); }
    auto Append(std::string_view str) noexcept -> FixedString&;
    auto Append(auto&& str) noexcept -> FixedString&
        requires std::same_as<std::remove_cvref_t<decltype(str)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(str)>, gsl::czstring> or
                 (std::convertible_to<decltype(str), gsl::czstring> and
                  not std::convertible_to<decltype(str), std::string_view>);
    auto Append(auto&& str) noexcept -> FixedString&
        requires std::convertible_to<decltype(str), std::string> and
                 (not std::convertible_to<decltype(str), std::string_view>) and
                 (not std::convertible_to<decltype(str), gsl::czstring>);
    auto Append(std::nullptr_t) noexcept -> FixedString& = delete;
    auto append(auto&& str) noexcept -> FixedString&
        requires requires(FixedString self) { self.Append(std::forward<decltype(str)>(str)); }
    { return Append(std::forward<decltype(str)>(str)); }

    auto operator+=(auto&& rhs) noexcept -> FixedString&
        requires requires(FixedString self) { self.Append(std::forward<decltype(rhs)>(rhs)); }
    { return Append(std::forward<decltype(rhs)>(rhs)); }

    template<std::size_t N>
    auto operator==(const char (&rhs)[N]) const noexcept -> bool { return std::strncmp(fData, rhs, std::min(N, AMaxSize + 1)) == 0; }
    template<std::size_t N>
    auto operator==(const FixedString<N>& rhs) const noexcept -> bool { return *this == rhs.Data(); }
    auto operator==(std::string_view rhs) const noexcept -> bool { return std::string_view(*this) == rhs; }
    auto operator==(auto&& rhs) const noexcept -> bool
        requires std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(rhs), gsl::czstring> and
                  not std::convertible_to<decltype(rhs), std::string_view>)
    { return std::strncmp(fData, std::forward<decltype(rhs)>(rhs), AMaxSize + 1) == 0; }
    auto operator==(auto&& rhs) const noexcept -> bool
        requires std::convertible_to<decltype(rhs), std::string> and
                 (not std::convertible_to<decltype(rhs), std::string_view>) and
                 (not std::convertible_to<decltype(rhs), gsl::czstring>)
    { return *this == std::string(std::forward<decltype(rhs)>(rhs)).c_str(); }
    auto operator==(std::nullptr_t) const noexcept -> bool = delete;

    template<std::size_t N>
    auto operator<=>(const char (&rhs)[N]) const noexcept -> std::strong_ordering;
    template<std::size_t N>
    auto operator<=>(const FixedString<N>& rhs) const noexcept -> std::strong_ordering { return *this <=> rhs.Data(); }
    auto operator<=>(std::string_view rhs) const noexcept -> std::strong_ordering { return std::string_view(*this) <=> rhs; }
    auto operator<=>(auto&& rhs) const noexcept -> std::strong_ordering
        requires std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::zstring> or
                 std::same_as<std::remove_cvref_t<decltype(rhs)>, gsl::czstring> or
                 (std::convertible_to<decltype(rhs), gsl::czstring> and
                  not std::convertible_to<decltype(rhs), std::string_view>);
    auto operator<=>(auto&& rhs) const noexcept -> std::strong_ordering
        requires std::convertible_to<decltype(rhs), std::string> and
                 (not std::convertible_to<decltype(rhs), std::string_view>) and
                 (not std::convertible_to<decltype(rhs), gsl::czstring>)
    { return *this <=> std::string(std::forward<decltype(rhs)>(rhs)).c_str(); }
    auto operator<=>(std::nullptr_t) const noexcept -> std::strong_ordering = delete;

    static constexpr auto Capacity() noexcept -> std::size_t { return AMaxSize; }
    static constexpr auto MaxSize() noexcept -> std::size_t { return AMaxSize; }
    static constexpr auto capacity() noexcept -> std::size_t { return Capacity(); }
    static constexpr auto max_size() noexcept -> std::size_t { return MaxSize(); }

    static constexpr auto Occupation() noexcept -> std::size_t { return AMaxSize + 1; }

    friend auto operator+(FixedString lhs, const FixedString& rhs) noexcept -> FixedString { return lhs += rhs; }
    friend auto operator+(FixedString lhs, auto&& rhs) noexcept -> FixedString
        requires requires { lhs += std::forward<decltype(rhs)>(rhs); }
    { return lhs += std::forward<decltype(rhs)>(rhs); }
    friend auto operator+(auto&& lhs, const FixedString& rhs) noexcept -> FixedString
        requires requires { FixedString(std::forward<decltype(lhs)>(lhs)) += rhs; }
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
using String15 = FixedString<15>;
/// @brief A short string (31 characters) on the stack. Size 32 bytes.
using String31 = FixedString<31>;
/// @brief A short string (63 characters) on the stack. Size 64 bytes.
using String63 = FixedString<63>;

} // namespace MACE::inline Utility

#include "MACE/Utility/FixedString.inl"
