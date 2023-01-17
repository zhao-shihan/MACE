#pragma once

#include "MACE/Math/Parity.hxx"
#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.hxx"

#include <bit>
#include <cstdint>
#include <limits>

namespace MACE::Math::Random::Generator {

class PCGXSHRR6432 final : public UniformPseudoRandomBitGeneratorBase<PCGXSHRR6432, std::uint32_t> {
public:
    using StateType = std::uint64_t;

public:
    constexpr PCGXSHRR6432();
    constexpr PCGXSHRR6432(StateType seed);

    constexpr void Step() { fState = Multipiler() * fState + Increment(); }
    constexpr ResultType operator()();
    constexpr void Seed(StateType seed);
    constexpr void Discard(StateType n);

    static constexpr auto Min() { return std::numeric_limits<ResultType>::min(); }
    static constexpr auto Max() { return std::numeric_limits<ResultType>::max(); }

    static constexpr StateType Multipiler() { return 6364136223846793005ull; }
    static constexpr StateType Increment() { return 0xDA3E39CB94B95BDBull; }

    template<Concept::Character AChar>
    friend auto& operator<<(std::basic_ostream<AChar>& os, const PCGXSHRR6432& self) { return os << self.fState; }
    template<Concept::Character AChar>
    friend auto& operator>>(std::basic_istream<AChar>& is, PCGXSHRR6432& self) { return is >> self.fState; }

private:
    StateType fState;
};

} // namespace MACE::Math::Random::Generator

#include "MACE/Math/Random/Generator/PCGXSHRR6432.inl"
