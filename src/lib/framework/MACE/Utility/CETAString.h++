#pragma once

#include "gsl/gsl"

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string>
#include <string_view>

namespace MACE::inline Utility {

/// @brief CETAString for 'ConstEval, Template Applicable String'
/// @tparam N Size of the string ('\0' included)
template<std::size_t N>
struct CETAString {
private:
    using CharString = const char[N];

    struct Data {
        consteval Data(const CharString& string);
        char fData[N];
    };

public:
    consteval CETAString(const CharString& string);
    constexpr CETAString(const CETAString&) = default;

    constexpr auto CZString() const -> const auto& { return fStringDataImNotPublic.fData; }
    constexpr auto StringView() const -> std::string_view { return {CZString(), N - 1}; }
    auto String() const -> std::string { return {CZString(), N - 1}; }

    constexpr operator const CharString&() const { return CZString(); }
    constexpr operator std::string_view() const { return StringView(); }
    operator std::string() const { return String(); }

    constexpr auto operator==(gsl::czstring rhs) const -> bool { return StringView() == std::string_view{rhs}; }
    constexpr auto operator<=>(gsl::czstring rhs) const -> auto { return StringView() <=> std::string_view{rhs}; }

    static constexpr auto HasValue() -> bool { return true; }

    const Data fStringDataImNotPublic; // semantic private
};

template<>
struct CETAString<0> {
    consteval CETAString(std::nullptr_t) {}
    constexpr CETAString(const CETAString&) = default;

    constexpr auto operator=(const CETAString&) -> CETAString& = delete;

    static constexpr auto HasValue() -> bool { return false; }
};

CETAString(std::nullptr_t) -> CETAString<0>;
template<std::size_t N>
CETAString(const char (&)[N]) -> CETAString<N>;

template<std::size_t M, std::size_t N>
constexpr auto operator==(const CETAString<M>& lhs, const CETAString<N>& rhs) -> bool { return lhs.StringView() == rhs.StringView(); }
template<std::size_t M, std::size_t N>
constexpr auto operator<=>(const CETAString<M>& lhs, const CETAString<N>& rhs) -> auto { return lhs.StringView() <=> rhs.StringView(); }

} // namespace MACE::inline Utility

#include "MACE/Utility/CETAString.inl"
