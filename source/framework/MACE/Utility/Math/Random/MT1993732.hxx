#pragma once

#include <array>
#include <cstdint>
#include <limits>

namespace MACE::Utility::Math::Random {

class MT1993732 {
public:
    using ResultType = std::uint32_t;

public:
    constexpr MT1993732();
    constexpr MT1993732(ResultType seed);

    constexpr void Seed(ResultType seed);
    constexpr ResultType operator()();

    constexpr bool operator==(const MT1993732&) const = default;

    static constexpr auto Min() { return std::numeric_limits<ResultType>::min(); }
    static constexpr auto Max() { return std::numeric_limits<ResultType>::max() - 1; }

private:
    constexpr void Regenerate();

private:
    std::array<ResultType, 624U> fMT;
    std::array<ResultType, 624U> fTempered;
    const decltype(fTempered)::const_iterator fTemperedEnd;
    decltype(fTempered)::const_iterator fTemperedIterator;
};

} // namespace MACE::Utility::Math::Random

#include "MT1993732.inl"
