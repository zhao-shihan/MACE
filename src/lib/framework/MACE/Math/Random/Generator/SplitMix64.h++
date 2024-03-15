#pragma once

#include "MACE/Concept/FundamentalType.h++"
#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.h++"
#include "MACE/Utility/InlineMacro.h++"

#include <cstdint>
#include <istream>
#include <limits>
#include <ostream>

namespace MACE::Math::Random::inline Generator {

class SplitMix64 final : public UniformPseudoRandomBitGeneratorBase<SplitMix64,
                                                                    std::uint64_t,
                                                                    std::uint64_t> {
public:
    constexpr SplitMix64();
    constexpr explicit SplitMix64(SeedType seed);

    MACE_ALWAYS_INLINE constexpr auto operator()() -> SplitMix64::ResultType;
    constexpr auto Seed(SeedType seed) -> void;

    static constexpr auto Min() -> auto { return std::numeric_limits<ResultType>::min(); }
    static constexpr auto Max() -> auto { return std::numeric_limits<ResultType>::max(); }

    template<Concept::Character AChar>
    friend auto operator<<(std::basic_ostream<AChar>& os, const SplitMix64& self) -> decltype(auto) { return os << self.fState; }
    template<Concept::Character AChar>
    friend auto operator>>(std::basic_istream<AChar>& is, SplitMix64& self) -> decltype(auto) { return is >> self.fState; }

private:
    ResultType fState;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/SplitMix64.inl"
