#pragma once

#include "MACE/Math/Parity.hxx"
#include "MACE/Math/Random/UniformRandomBitGeneratorBase.hxx"

#include <bit>
#include <cstdint>
#include <limits>

namespace MACE::Math::Random::Generator {

class PCGXSHRR6432 final : public UniformRandomBitGeneratorBase<PCGXSHRR6432, std::uint32_t> {
public:
    using StateType = std::uint64_t;

public:
    constexpr PCGXSHRR6432();
    constexpr PCGXSHRR6432(StateType seed);

    constexpr ResultType operator()();
    constexpr bool operator==(const PCGXSHRR6432&) const = default;

    constexpr void Step() { fState = Multipiler() * fState + Increment(); }
    constexpr void Seed(StateType seed);
    constexpr void Discard(StateType n);

    static constexpr auto Min() { return std::numeric_limits<ResultType>::min(); }
    static constexpr auto Max() { return std::numeric_limits<ResultType>::max(); }

    static constexpr StateType Multipiler() { return 6364136223846793005ULL; }
    static constexpr StateType Increment() { return 0xda3e39cb94b95bdbULL; }

private:
    StateType fState;
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/PCGXSHRR6432.inl"
