#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include "gsl/gsl"

#include <algorithm>
#include <cinttypes>
#include <cstddef>
#include <ranges>
#include <string>
#include <string_view>

namespace MACE::Data {

// CEvalNTSTA for 'ConstEval Name/Title String (Template Applicable)'
template<std::size_t N>
    requires(N == 0 or N >= 2)
struct CEvalNTSTA : NonMoveableBase {
private:
    struct FixedString {
        consteval FixedString(const char (&string)[N]);
        char fString[N];
    };

public:
    consteval CEvalNTSTA(const char (&string)[N]);

    constexpr auto CZString() const -> gsl::czstring { return fPrivateStringNotAPI.fString; }
    constexpr auto StringView() const -> std::string_view { return {CZString(), N - 1}; }
    auto String() const -> std::string { return {CZString(), N - 1}; }

    constexpr operator gsl::czstring() const { return CZString(); }
    constexpr operator std::string_view() const { return StringView(); }
    operator std::string() const { return String(); }

    static constexpr auto HasValue() { return true; }

    const FixedString fPrivateStringNotAPI; // semantic private
};

template<>
struct CEvalNTSTA<0> : NonMoveableBase {
    consteval CEvalNTSTA(std::nullptr_t) {}
    static constexpr auto HasValue() { return false; }
};

CEvalNTSTA(std::nullptr_t) -> CEvalNTSTA<0>;
template<std::size_t N>
CEvalNTSTA(const char (&)[N]) -> CEvalNTSTA<N>;

template<std::size_t M, std::size_t N>
constexpr auto operator==(const CEvalNTSTA<M>& lhs, const CEvalNTSTA<N>& rhs) { return lhs.StringView() == rhs.StringView(); }
template<std::size_t M, std::size_t N>
constexpr auto operator<=>(const CEvalNTSTA<M>& lhs, const CEvalNTSTA<N>& rhs) { return lhs.StringView() <=> rhs.StringView(); }

} // namespace MACE::Data

#include "MACE/Data/CEvalNTSTA.inl"
