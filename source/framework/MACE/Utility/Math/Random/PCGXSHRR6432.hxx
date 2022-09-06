#pragma once

#include <bit>
#include <cstdint>
#include <limits>

namespace MACE::Utility::Math::Random {

class PCGXSHRR6432 {
public:
    using StateType = std::uint64_t;
    using ResultType = std::uint32_t;

public:
    constexpr PCGXSHRR6432();
    constexpr PCGXSHRR6432(StateType seed);

    constexpr void Step() { fState = fgMultipiler * fState + fgIncrement; }
    constexpr void Seed(StateType seed);
    constexpr ResultType operator()();
    constexpr void Discard(StateType n);

    constexpr bool operator==(const PCGXSHRR6432&) const = default;

    static constexpr auto Min() { return std::numeric_limits<ResultType>::min(); }
    static constexpr auto Max() { return std::numeric_limits<ResultType>::max(); }

private:
    StateType fState;

    static constexpr StateType fgMultipiler = 6364136223846793005ULL;
    static constexpr StateType fgIncrement = 0xda3e39cb94b95bdbULL;
};

} // namespace MACE::Utility::Math::Random

#include "PCGXSHRR6432.inl"
