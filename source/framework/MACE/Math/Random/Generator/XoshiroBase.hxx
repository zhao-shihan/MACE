#pragma once

#include "MACE/Math/Random/Generator/SplitMix64.hxx"
#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.hxx"

#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <limits>
#include <utility>

namespace MACE::Math::Random::inline Generator {

template<class ADerived, std::size_t NBit>
    requires(NBit % 64 == 0)
class XoshiroBase : public UniformPseudoRandomBitGeneratorBase<ADerived, std::uint64_t> {
protected:
    constexpr XoshiroBase(std::array<std::uint64_t, NBit / 64> defaultState);
    constexpr XoshiroBase(std::uint64_t seed);
    constexpr ~XoshiroBase() = default;

public:
    constexpr void Seed(std::uint64_t seed);

    static constexpr auto Min() { return std::numeric_limits<std::uint64_t>::min(); }
    static constexpr auto Max() { return std::numeric_limits<std::uint64_t>::max(); }

protected:
    std::array<std::uint64_t, NBit / 64> fState;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/XoshiroBase.inl"
