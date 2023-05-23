#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.hxx"

#include <cinttypes>
#include <limits>

namespace MACE::Math::Random::inline Generator {

class SplitMix64 final : public UniformPseudoRandomBitGeneratorBase<SplitMix64, std::uint64_t> {
public:
    constexpr SplitMix64();
    constexpr SplitMix64(ResultType seed);

    constexpr SplitMix64::ResultType operator()();
    constexpr void Seed(ResultType seed);

    static constexpr auto Min() { return std::numeric_limits<ResultType>::min(); }
    static constexpr auto Max() { return std::numeric_limits<ResultType>::max(); }

    template<Concept::Character AChar>
    friend auto& operator<<(std::basic_ostream<AChar>& os, const SplitMix64& self) { return os << self.fState; }
    template<Concept::Character AChar>
    friend auto& operator>>(std::basic_istream<AChar>& is, SplitMix64& self) { return is >> self.fState; }

private:
    ResultType fState;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/SplitMix64.inl"
