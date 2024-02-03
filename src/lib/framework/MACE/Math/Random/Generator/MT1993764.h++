#pragma once

#include "MACE/Concept/FundamentalType.h++"
#include "MACE/Math/Random/UniformPseudoRandomBitGeneratorBase.h++"

#include <random>

namespace MACE::Math::Random::inline Generator {

class MT1993764 final : public UniformPseudoRandomBitGeneratorBase<MT1993764,
                                                                   std::mt19937_64::result_type,
                                                                   std::mt19937_64::result_type> {
public:
    MT1993764() = default;
    explicit MT1993764(SeedType seed);

    auto operator()() -> auto { return fMT(); }
    auto Seed(SeedType seed) -> void { fMT.seed(seed); }

    static constexpr auto Min() -> auto { return std::mt19937_64::min(); }
    static constexpr auto Max() -> auto { return std::mt19937_64::max(); }

    template<Concept::Character AChar>
    friend auto operator<<(std::basic_ostream<AChar>& os, const MT1993764& self) -> decltype(auto) { return os << self.fMT; }
    template<Concept::Character AChar>
    friend auto operator>>(std::basic_istream<AChar>& is, MT1993764& self) -> decltype(auto) { return is >> self.fMT; }

private:
    std::mt19937_64 fMT;
};

} // namespace MACE::Math::Random::inline Generator

#include "MACE/Math/Random/Generator/MT1993764.inl"
